# 03 — ROS 2

ROS 2 is an optional **application layer** for navigation, visualization, and tooling. Q1 exposes a thin bridge; the robot’s native bus remains DDS.

## Packages

| Package | Role |
|---------|------|
| `q1_msgs` | Messages & services |
| `q1_driver` | DDS ↔ ROS bridge |
| `q1_bringup` | Launch files |
| `q1_teleop` | Keyboard / joy teleop |

## Build

```bash
mkdir -p ~/q1_ws/src
ln -s $(pwd)/ros2/* ~/q1_ws/src/
cd ~/q1_ws
source /opt/ros/humble/setup.bash
colcon build --symlink-install
source install/setup.bash
```

## Bringup (mock)

```bash
ros2 launch q1_bringup mock.launch.py
ros2 topic echo /q1/odom
ros2 run q1_teleop teleop_keyboard
```

## Key topics

| ROS topic | Maps from DDS |
|-----------|---------------|
| `/q1/low_state` | `rt/lowstate` |
| `/q1/odom` | `rt/odom` |
| `/q1/cmd_vel` | High-level `SetVelocity` |
| `/joint_states` | Arm + wheel joints |

## Services

| Service | Effect |
|---------|--------|
| `/q1/standby` | Soft hold |
| `/q1/estop` | Immediate damp |
| `/q1/play_action` | Named interaction pack |

## Domain isolation recipe

```bash
# Robot bus stays on domain 0 (SDK default)
# ROS uses Cyclone with a separate domain via CYCLONEDDS_URI
export ROS_DOMAIN_ID=42
ros2 launch q1_bringup driver.launch.py robot_iface:=eth0
```

`q1_driver` is the only process that should speak both graphs.

## Next

→ [04 API](04_api.md)
