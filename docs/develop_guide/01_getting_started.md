# 01 — Getting Started

## Goals

- Install toolchain
- Build the SDK examples
- Run Hello World against the **mock DDS channel** (no robot required)

## Prerequisites

- Ubuntu 22.04 (or 20.04)
- CMake ≥ 3.16, g++ ≥ 9, Python ≥ 3.10
- Optional: ROS 2 Humble for chapter 3

```bash
sudo apt-get update
sudo apt-get install -y cmake g++ build-essential libeigen3-dev \
  libyaml-cpp-dev git python3-pip python3-venv
```

## Clone & build

```bash
git clone https://github.com/willnien10005914/q1_robot_sdk.git
cd q1_robot_sdk
mkdir build && cd build
cmake .. -DBUILD_EXAMPLES=ON -DQ1_ENABLE_MOCK=ON
make -j$(nproc)
```

## Hello World

```bash
# From build/
./bin/q1_helloworld --mock
```

Expected output:

```text
[q1] ChannelFactory Init domain=0 iface=mock
[q1] LocoClient connected (mock)
[q1] fsm=STANDBY battery=100%
[q1] Hello, Q1!
```

## Connect to a real robot (Official SDK / CES bring-up)

```bash
# Replace eth0 with the NIC facing the robot LAN
./bin/q1_helloworld --iface eth0
```

Network tips:

1. PC and robot on the same L2 segment / VLAN.
2. Disable VPN / unexpected firewall on DDS multicast ports.
3. Use a dedicated NIC when possible; pass its name to `ChannelFactory::Init`.

## Python

```bash
cd ../python
python3 -m venv .venv && source .venv/bin/activate
pip install -e .
python ../example/helloworld/helloworld.py --mock
```

## Next

→ [02 DDS](02_dds.md)
