"""Pre-SDK ROS 2 driver stub — publishes mock odom / forwards cmd_vel."""

def main():
    try:
        import rclpy
        from rclpy.node import Node
        from geometry_msgs.msg import Twist
        from nav_msgs.msg import Odometry
    except ImportError:
        print("rclpy not available — install ROS 2 Humble to run q1_driver")
        return

    class Driver(Node):
        def __init__(self):
            super().__init__("q1_driver")
            self.pub = self.create_publisher(Odometry, "/q1/odom", 10)
            self.create_subscription(Twist, "/q1/cmd_vel", self.on_cmd, 10)
            self.create_timer(0.05, self.tick)
            self._vx = 0.0
            self._vyaw = 0.0
            self.get_logger().info("q1_driver mock bridge up")

        def on_cmd(self, msg: Twist):
            self._vx = msg.linear.x
            self._vyaw = msg.angular.z

        def tick(self):
            odom = Odometry()
            odom.header.stamp = self.get_clock().now().to_msg()
            odom.header.frame_id = "odom"
            odom.child_frame_id = "base_link"
            odom.twist.twist.linear.x = self._vx
            odom.twist.twist.angular.z = self._vyaw
            self.pub.publish(odom)

    rclpy.init()
    node = Driver()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == "__main__":
    main()
