#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/imu.hpp"
#include "std_msgs/msg/float64_multi_array.hpp"

#include "roll.h"

using std::placeholders::_1;

class RollNode : public rclcpp::Node
{
public:
    RollNode() : Node("roll_node")
    {
        // Subscriber: IMU
        imu_sub_ = create_subscription<sensor_msgs::msg::Imu>(
            "/imu/data", 10,
            std::bind(&RollNode::imu_callback, this, _1));

        // Publisher: thrusters
        thruster_pub_ = create_publisher<std_msgs::msg::Float64MultiArray>(
            "/thruster_cmd", 10);

        // Timer (100 Hz)
        timer_ = create_wall_timer(
            std::chrono::milliseconds(10),
            std::bind(&RollNode::control_loop, this));

        // Initialize model
        model_.initialize();

        // Default setpoint
        roll_goal_ = 0.0;
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

        // Run controller
        model_.step();

        // Get outputs
        auto fl = model_.rtY.fl;
        auto fr = model_.rtY.fr;
        auto bl = model_.rtY.bl;
        auto br = model_.rtY.br;

        // Publish
        std_msgs::msg::Float64MultiArray msg;
        msg.data = {fl, fr, bl, br};

        thruster_pub_->publish(msg);

        RCLCPP_INFO_THROTTLE(get_logger(), *get_clock(), 1000,
            "FL: %.2f FR: %.2f BL: %.2f BR: %.2f",
            fl, fr, bl, br);
    }

    // ===== MEMBERS =====
    roll model_;

    double roll_ = 0.0;
    double omega_x_ = 0.0;
    double roll_goal_;

    rclcpp::Subscription<sensor_msgs::msg::Imu>::SharedPtr imu_sub_;
    rclcpp::Publisher<std_msgs::msg::Float64MultiArray>::SharedPtr thruster_pub_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<RollNode>());
    rclcpp::shutdown();
    return 0;
}
