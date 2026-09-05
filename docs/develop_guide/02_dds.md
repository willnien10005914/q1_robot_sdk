# 02 — DDS

Q1’s realtime bus is **DDS** (CycloneDDS), matching the typical Edu humanoid low-level communication model.

## Why DDS?

- Decoupled publishers/subscribers (no central broker)
- Hard realtime-friendly QoS (best-effort or reliable per topic)
- Same mental model as Edu-class `rt/lowcmd` / `rt/lowstate`

## Domain & interface

```cpp
q1::ChannelFactory::Instance()->Init(/*domain_id=*/0, "eth0");
```

| Parameter | Meaning |
|-----------|---------|
| `domain_id` | Isolates robots on a shared LAN (default `0`) |
| `iface` | NIC name; use `"mock"` for CI |

**ROS tip:** Run ROS 2 on a different DDS domain (or Cyclone config) than the robot bus to avoid discovery storms — a common Edu gotcha.

## Core topics

| Topic | Type (IDL name) | Rate (typ.) |
|-------|-----------------|-------------|
| `rt/lowstate` | `q1::msg::LowState` | 500 Hz |
| `rt/lowcmd` | `q1::msg::LowCmd` | 250–500 Hz (UserCtrl) |
| `rt/odom` | `q1::msg::Odom` | 100 Hz |
| `rt/wireless_controller` | `q1::msg::WirelessController` | 50 Hz |

## Publisher / subscriber pattern

```cpp
#include <q1/channel/channel_publisher.hpp>
#include <q1/channel/channel_subscriber.hpp>
#include <q1/idl/low_cmd.hpp>
#include <q1/idl/low_state.hpp>

using q1::channel::ChannelPublisher;
using q1::channel::ChannelSubscriber;

ChannelSubscriber<q1::msg::LowState> sub("rt/lowstate");
sub.InitChannel([](const void* msg) {
  auto* s = static_cast<const q1::msg::LowState*>(msg);
  // read s->imu, s->wheel, s->joint ...
});

ChannelPublisher<q1::msg::LowCmd> pub("rt/lowcmd");
pub.InitChannel();
q1::msg::LowCmd cmd{};
// fill wheel + arm fields
pub.Write(&cmd);
```

## QoS defaults (pre-SDK)

| Topic | Reliability | History |
|-------|-------------|---------|
| `rt/lowcmd` | Best effort | Keep last 1 |
| `rt/lowstate` | Best effort | Keep last 1 |
| Service req/resp | Reliable | Keep last 10 |

## Debugging

```bash
# Mock introspection
./bin/q1_topic_echo --topic rt/lowstate --mock

# When Cyclone tools are installed on the host:
# cyclonedds topic list   # environment-dependent
```

## Next

→ [03 ROS 2](03_ros.md)
