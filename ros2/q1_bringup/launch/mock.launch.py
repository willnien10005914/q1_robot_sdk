from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(package="q1_driver", executable="q1_driver_node", name="q1_driver", output="screen"),
        Node(package="q1_teleop", executable="teleop_keyboard", name="q1_teleop", output="screen"),
    ])
