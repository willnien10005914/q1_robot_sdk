from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        DeclareLaunchArgument("robot_iface", default_value="eth0"),
        Node(
            package="q1_driver",
            executable="q1_driver_node",
            name="q1_driver",
            output="screen",
            parameters=[{"iface": LaunchConfiguration("robot_iface")}],
        ),
    ])
