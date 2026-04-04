import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Imu

from vectornav import Sensor, Registers
import math
import time


class VN100Node(Node):

    def __init__(self):
        super().__init__('vn100_node')

        # Parameters
        self.declare_parameter('port', '/dev/ttyUSB0')   # change to 'COMX' on Windows
        self.declare_parameter('baud', 115200)
        self.declare_parameter('rate_hz', 50.0)

        port = self.get_parameter('port').value
        baud = self.get_parameter('baud').value
        rate_hz = self.get_parameter('rate_hz').value

        self.dt = 1.0 / rate_hz

        # ROS publisher
        self.pub = self.create_publisher(Imu, '/imu/data', 10)

        # VN100 setup
        self.sensor = Sensor()
        self.sensor.connect(port, baud)

        self.get_logger().info(f"Connected to VN100 on {port} @ {baud}")

        # Timer loop
        self.timer = self.create_timer(self.dt, self.loop)

    def fuse_quaternion(self, roll, pitch, yaw, qx_vn, qy_vn, qz_vn, qs_vn):

        # ===== 1. Euler → quaternion =====
        cr = math.cos(roll / 2)
        sr = math.sin(roll / 2)
        cp = math.cos(pitch / 2)
        sp = math.sin(pitch / 2)
        cy = math.cos(yaw / 2)
        sy = math.sin(yaw / 2)

        qs_e = cr * cp * cy + sr * sp * sy
        qx_e = sr * cp * cy - cr * sp * sy
        qy_e = cr * sp * cy + sr * cp * sy
        qz_e = cr * cp * sy - sr * sp * cy

        # ===== 2. Normalize both =====
        def normalize(q):
            norm = math.sqrt(sum([x*x for x in q]))
            return [x / norm for x in q]

        q_e = normalize([qs_e, qx_e, qy_e, qz_e])
        q_vn = normalize([qs_vn, qx_vn, qy_vn, qz_vn])

        # ===== 3. Compute dot product =====
        dot = sum([a*b for a, b in zip(q_e, q_vn)])

        # Handle quaternion double-cover issue
        if dot < 0.0:
            q_vn = [-x for x in q_vn]
            dot = -dot

        # ===== 4. SLERP (fusion) =====
        alpha = 0.8   # weight → trust VN100 more

        if dot > 0.9995:
            # Linear interpolation (very close)
            q_fused = [(1-alpha)*a + alpha*b for a, b in zip(q_e, q_vn)]
        else:
            theta_0 = math.acos(dot)
            sin_theta_0 = math.sin(theta_0)

            theta = theta_0 * alpha
            sin_theta = math.sin(theta)

            s0 = math.cos(theta) - dot * sin_theta / sin_theta_0
            s1 = sin_theta / sin_theta_0

            q_fused = [s0*a + s1*b for a, b in zip(q_e, q_vn)]

        # ===== 5. Normalize result =====
        q_fused = normalize(q_fused)

        # Return in ROS format
        return q_fused[0],q_fused[1],q_fused[2],q_fused[3]

    def loop(self):
        try:
            # Read registers
            ypr_reg = Registers.Attitude.YawPitchRoll()
            quat_reg = Registers.Attitude.Quaternion()
            accel_reg = Registers.IMU.Accel()
            gyro_reg = Registers.IMU.Gyro()
            
            self.sensor.readRegister(ypr_reg)
            self.sensor.readRegister(quat_reg)
            self.sensor.readRegister(accel_reg)
            self.sensor.readRegister(gyro_reg)

            # Convert degrees → radians
            yaw = math.radians(self.ypr_reg.yaw)
            pitch = math.radians(self.ypr_reg.pitch)
            roll = math.radians(self.ypr_reg.roll)
            
            #quat
            quatx = self.quat_reg.quatX
            quaty = self.quat_reg.quatY
            quatz = self.quat_reg.quatZ
            quatw = self.quat_reg.quatS

            # Convert to quaternion and normalised
            qw, qx, qy, qz = self.fuse_quaternion(roll, pitch, yaw, quatx, quaty, quatz, quatw)

            # Create message
            msg = Imu()

            msg.header.stamp = self.get_clock().now().to_msg()
            msg.header.frame_id = "imu_link"

            # Orientation
            msg.orientation.w = qw
            msg.orientation.x = qx
            msg.orientation.y = qy
            msg.orientation.z = qz

            # (Optional: if you later add gyro/accel)
            msg.angular_velocity.x = self.gyro_reg.gyroX
            msg.angular_velocity.y = self.gyro_reg.gyroY
            msg.angular_velocity.z = self.gyro_reg.gyroZ

            msg.linear_acceleration.x = self.accel_reg.accelX
            msg.linear_acceleration.y = self.accel_reg.accelY
            msg.linear_acceleration.z = self.accel_reg.accelZ

            self.pub.publish(msg)

        except Exception as e:
            self.get_logger().error(f"VN100 read error: {e}")


def main(args=None):
    rclpy.init(args=args)
    node = VN100Node()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()
