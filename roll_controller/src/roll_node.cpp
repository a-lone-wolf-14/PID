#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/imu.hpp"
#include "std_msgs/msg/float64_multi_array.hpp"
#include <vector>
#include <algorithm>
#include <signal.h>
#include <yaml-cpp/yaml.h>
#include <set>

#include "roll.h"

using std::placeholders::_1;

std::shared_ptr<class RollNode> global_node = nullptr;

class ThrustMapper
{
public:
    std::vector<double> PWM;
    std::vector<double> voltages;
    std::vector<std::vector<double>> thrust_matrix;

    double PWM_MIN = 1100;
    double PWM_MAX = 1900;

    // Linear interpolation helper
    double interp(double x, double x0, double x1, double y0, double y1)
    {
        if (x1 == x0) return y0;
        return y0 + (x - x0) * (y1 - y0) / (x1 - x0);
    }

    // -------- voltage interpolation --------
    void load_from_yaml(const std::string &file)
    {
        YAML::Node data = YAML::LoadFile(file);

        std::set<double> voltage_set;

        // Extract voltages
        for (auto row : data)
        {
            for (auto it : row)
            {
                std::string key = it.first.as<std::string>();
                if (key.find("Thrust_") != std::string::npos)
                {
                    double v = std::stod(key.substr(7, key.size()-8));
                    voltage_set.insert(v);
                }
            }
        }

        voltages.assign(voltage_set.begin(), voltage_set.end());

        // Build data
        for (auto row : data)
        {
            PWM.push_back(row["PWM"].as<double>());

            std::vector<double> thrust_row;

            for (double v : voltages)
            {
                std::string key = "Thrust_" + std::to_string((int)v) + "V";
                thrust_row.push_back(row[key].as<double>());
            }

            thrust_matrix.push_back(thrust_row);
        }

        RCLCPP_INFO(rclcpp::get_logger("mapper"),
            "Loaded %ld PWM entries and %ld voltages",
            PWM.size(), voltages.size());
    }

    std::vector<double> thrust_at_voltage(double voltage)
    {
        std::vector<double> result(PWM.size());

        for (size_t i = 0; i < PWM.size(); i++)
        {
            for (size_t j = 0; j < voltages.size() - 1; j++)
            {
                if (voltage >= voltages[j] && voltage <= voltages[j+1])
                {
                    result[i] = interp(
                        voltage,
                        voltages[j], voltages[j+1],
                        thrust_matrix[i][j], thrust_matrix[i][j+1]
                    );
                    break;
                }
            }
        }
        return result;
    }

    double thrust_to_pwm(double thrust, double voltage)
    {
        auto curve = thrust_at_voltage(voltage);

        double min_t = *std::min_element(curve.begin(), curve.end());
        double max_t = *std::max_element(curve.begin(), curve.end());

        thrust = std::clamp(thrust, min_t, max_t);

        for (size_t i = 0; i < curve.size() - 1; i++)
        {
            double t0 = curve[i];
            double t1 = curve[i+1];

            if ((thrust >= t0 && thrust <= t1) ||
                (thrust <= t0 && thrust >= t1))
            {
                double pwm = interp(thrust, t0, t1, PWM[i], PWM[i+1]);
                return std::clamp(pwm, PWM_MIN, PWM_MAX);
            }
        }

        return PWM_MIN;
    }
};

class RollNode : public rclcpp::Node
{
public:
    RollNode() : Node("roll_node")
    {
        // Subscriber: IMU
        imu_sub_ = create_subscription<sensor_msgs::msg::Imu>(
            "/imu/data", 10,
            std::bind(&RollNode::imu_callback, this, _1));

        //Subscriber: PI gains
        pi_kp_sub_ = create_subscription<std_msgs::msg::Float64>(
            "/roll/pi/kp",10,
            [this](std_msgs::msg::Float64::SharedPtr msg)
            {
                pi_kp_ = msg->data;
            }
        );

        pi_ki_sub_ = create_subscription<std_msgs::msg::Float64>(
            "/roll/pi/ki",10,
            [this](std_msgs::msg::Float64::SharedPtr msg)
            {
                pi_ki_ = msg->data;
            }
        );

        pid_kp_sub_ = create_subscription<std_msgs::msg::Float64>(
            "/roll/pid/kp",10,
            [this](std_msgs::msg::Float64::SharedPtr msg)
            {
                pid_kp_ = msg->data;
            }
        );

        pid_ki_sub_ = create_subscription<std_msgs::msg::Float64>(
            "/roll/pid/ki",10,
            [this](std_msgs::msg::Float64::SharedPtr msg)
            {
                pid_ki_ = msg->data;
            }
        );

        pid_kd_sub_ = create_subscription<std_msgs::msg::Float64>(
            "/roll/pid/kd",10,
            [this](std_msgs::msg::Float64::SharedPtr msg)
            {
                pid_kd_ = msg->data;
            }
        );

        pid_kn_sub_ = create_subscription<std_msgs::msg::Float64>(
            "/roll/pid/kn",10,
            [this](std_msgs::msg::Float64::SharedPtr msg)
            {
                pid_kn_ = msg->data;
            }
        );

        // Publisher: thrusters
        thruster_pub_ = create_publisher<std_msgs::msg::Float64MultiArray>(
            "/thruster_cmd", 10);

        pwm_pub_ = create_publisher<std_msgs::msg::Float64MultiArray>(
            "/pwm_cmd", 10);

        // Timer (100 Hz)
        timer_ = create_wall_timer(
            std::chrono::milliseconds(10),
            std::bind(&RollNode::control_loop, this));

        model_.initialize();

        mapper_.load_from_yaml("/config/T200.yaml");

        battery_voltage_ = 14.8;
        roll_goal_ = 0.0;
    }

    void publish_neutral_pwm()
    {
        std_msgs::msg::Float64MultiArray pwm_msg;

        pwm_msg.data = {1500, 1500, 1500, 1500};

        pwm_pub_->publish(pwm_msg);

        RCLCPP_WARN(this->get_logger(), "Publishing NEUTRAL PWM (1500) before shutdown");

        // Give time to actually send
        rclcpp::sleep_for(std::chrono::milliseconds(200));
    }

private:

    // ===== IMU CALLBACK =====
    void imu_callback(const sensor_msgs::msg::Imu::SharedPtr msg)
    {
        double qw = msg->orientation.w;
        double qx = msg->orientation.x;
        double qy = msg->orientation.y;
        double qz = msg->orientation.z;

        // Roll extraction
        roll_ = atan2(
            2.0 * (qw*qx + qy*qz),
            1.0 - 2.0 * (qx*qx + qy*qy)
        );

        omega_x_ = msg->angular_velocity.x;
    }

    // ===== CONTROL LOOP =====
    void control_loop()
    {
        // Set inputs
        model_.rtU.roll_goal = roll_goal_;
        model_.rtU.roll_p    = roll_;
        model_.rtU.omega_x   = omega_x_;
        model_.rtU.pi_kp = pi_kp_;
        model_.rtU.pi_ki = pi_ki_;
        model_.rtU.pid_kp = pid_kp_;
        model_.rtU.pid_ki = pid_ki_;
        model_.rtU.pid_kd = pid_kd_;
        model_.rtU.pid_kn = pid_kn_;

        // Run controller
        model_.step();

        // Get outputs
        auto fl = (1)*model_.rtY.fl;
        auto fr = (1)*model_.rtY.fr;
        auto bl = (1)*model_.rtY.bl;
        auto br = (1)*model_.rtY.br;

        auto fl_pwm = mapper_.thrust_to_pwm(fl, battery_voltage_);
        auto fr_pwm = mapper_.thrust_to_pwm(fr, battery_voltage_);
        auto bl_pwm = mapper_.thrust_to_pwm(bl, battery_voltage_);
        auto br_pwm = mapper_.thrust_to_pwm(br, battery_voltage_);

        // Publish
        std_msgs::msg::Float64MultiArray thrust_msg, pwm_msg;
        thrust_msg.data = {fl, fr, bl, br};
        pwm_msg.data = {fl_pwm, fr_pwm, bl_pwm, br_pwm};

        thruster_pub_->publish(thrust_msg);
        pwm_pub_->publish(pwm_msg);

        RCLCPP_INFO_THROTTLE(get_logger(), *get_clock(), 1000,
            "FL: %.2f FR: %.2f BL: %.2f BR: %.2f",
            fl, fr, bl, br);
    }

    // ===== MEMBERS =====
    roll model_;
    ThrustMapper mapper_;

    double roll_ = 0.0;
    double omega_x_ = 0.0;
    double roll_goal_;
    double battery_voltage_;
    double pi_kp_ = 0.5;
    double pi_ki_ = 0.1;
    double pid_kp_ = 1.0;
    double pid_ki_ = 0.0;
    double pid_kd_ = 0.05;
    double pid_kn_ = 10.0;

    rclcpp::Subscription<sensor_msgs::msg::Imu>::SharedPtr imu_sub_;
    rclcpp::Subscription<std_msgs::msg::Float64>::SharedPtr pi_kp_sub_,pi_ki_sub_,pid_kp_sub_,pid_ki_sub_,pid_kd_sub_,pid_kn_sub_;
    rclcpp::Publisher<std_msgs::msg::Float64MultiArray>::SharedPtr thruster_pub_,pwm_pub_;
    rclcpp::TimerBase::SharedPtr timer_;
};

void signal_handler(int signum)
{
    if (global_node)
    {
        global_node->publish_neutral_pwm();
    }

    rclcpp::shutdown();
}

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);

    global_node = std::make_shared<RollNode>();

    signal(SIGINT, signal_handler);

    rclcpp::spin(global_node);

    rclcpp::shutdown();
    return 0;
}