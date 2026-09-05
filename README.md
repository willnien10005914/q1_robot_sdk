# Q1 Robot SDK

**Q1** is a transformable wheel-foot education humanoid platform designed and manufactured with **Quanta Computer (廣達電腦)** under Taiwan **MIT** (Made in Taiwan). This repository is the public SDK for developers — DDS realtime bus, high-level clients, ROS 2, and RL Train→Play→Sim2Sim→Sim2Real — purpose-built for Q1.


> **Status:** Pre-SDK architecture (v0.x) — API surface, docs, examples, and CES 2027 wheeled roadmap.  
> **Target:** Official SDK + physical deploy when EDU units ship.  
> **CES goal:** Dual-wheel Q1 demo track for **CES 2027**.

## Concept demo (Edu wheel-foot Q1)

Consistent **Quanta MIT native** design: matte **black dual-camera head**, soft fabric skinsuit, **QDD series** actuators, **3-finger dexterous hand**, and **wheel ↔ biped** transformable feet. Education-first: schools train once; customers fine-tune for home clean/organize, logistics, sports, calligraphy, and piano.


<p align="center">
  <img src="media/q1_edu_wheel_demo.gif" alt="Q1 Edu wheel-foot humanoid concept demo" width="960" />
</p>

<p align="center">
  <a href="https://github.com/willnien10005914/q1_robot_sdk/releases/download/v0.1.0-pre/q1_edu_wheel_demo.mp4"><strong>▶ Play / download full MP4 (~30s)</strong></a>
  ·
  <a href="media/q1_edu_wheel_demo.mp4">MP4 in repo</a>
  ·
  <a href="docs/develop_guide/10_use_cases.md">Use-case guide</a>
</p>

<details>
<summary>HTML5 video player (click to expand)</summary>

<video src="media/q1_edu_wheel_demo.mp4" controls muted loop playsinline width="960" poster="media/q1_edu_wheel_demo_poster.png">
  <a href="media/q1_edu_wheel_demo.mp4">Download the Q1 Edu concept demo (MP4)</a>
</video>

</details>

| Scene | Skill path |
|-------|------------|
| Wheel ↔ Biped transform | Native wheel-foot reconfiguration |
| Wheel-foot mobility | `LocoClient` + **QDD** joint torque / wheel roll |
| Education lab | Classroom bring-up + teleop |
| Customer fine-tune | RL / imitation train → deploy |
| Home clean & organize | Customer-trained household pack |
| Logistics & cargo | Carry / last-meter transport pack |
| Performance sports | **3-finger** soft-ball toss / play demos |
| Calligraphy | **3-finger** brush cultural pack |
| Piano | **3-finger** music classroom pack |

| Layer | What you get |
|-------|----------------|
| **DDS** | Real-time `rt/*` topics for lowcmd / lowstate / wheel odom |
| **High-level API** | `LocoClient`, `ArmClient`, `InteractionClient` (JSON request/response over DDS) |
| **ROS 2** | `q1_msgs`, `q1_driver`, `q1_bringup`, teleop nodes |
| **Basic motion** | Wheel-foot loco + **QDD** joint control, soft-stop, arm trajectories |
| **Dexterous hand** | 3-finger end-effector API (grasp / brush / key press) |
| **Manufacture** | Taiwan **MIT** · Quanta Computer (廣達電腦) collaboration concept |
| **RL / AI** | `q1_rl_gym` — Train → Play → Sim2Sim → Sim2Real |
| **Use cases** | Edu train → home clean / logistics / sports / calligraphy / piano |

---

## Quick links

- **[SDK Develop Guide](docs/develop_guide/index.md)** — start here (ROS · DDS · API · motion · RL · AI · Sim2Sim · Sim2Real)
- **[Roadmap & Milestones](docs/roadmap.md)** — wheeled (this year) → biped + dexterous hand (next year)
- **[Architecture](docs/architecture.md)** — process layout, domains, safety
- **[GitHub Milestones](https://github.com/willnien10005914/q1_robot_sdk/milestones)** — tracked release gates

---

## Product timeline

```text
2026-10  Pre-SDK releases begin (API skeleton + use-case demos)
2026-Q4  Wheeled locomotion + interaction action packs (piano / calligraphy / soft baseball)
2027-01  CES 2027 dual-wheel showcase
2027     Official SDK 1.0 — deploy to physical Q1 EDU
2027+    Biped platform + dexterous hand manipulation SDK track
```

---

## Repository layout

```text
q1_robot_sdk/
├── include/q1/          # C++ headers (channel, clients, IDL stubs)
├── python/q1_sdk/       # Python client (pre-SDK)
├── example/             # Hello world, high/low level, use cases
├── ros2/                # ROS 2 packages
├── rl/                  # RL gym + deploy (sim2sim / sim2real)
├── sim/                 # MuJoCo / Isaac assets
├── docs/develop_guide/  # Full developer curriculum
├── media/               # Concept demo GIF / MP4 preview
└── assets/              # URDF / meshes (placeholder)
```

---

## Environment

| Item | Recommendation |
|------|----------------|
| OS | Ubuntu 22.04 LTS (20.04 compatible for DDS examples) |
| Arch | x86_64, aarch64 |
| C++ | C++17, CMake ≥ 3.16, gcc ≥ 9 |
| Python | 3.10+ |
| ROS 2 | Humble (primary), Jazzy optional |
| DDS | CycloneDDS (default domain `0` for robot bus) |

```bash
# System deps (Ubuntu)
sudo apt-get update
sudo apt-get install -y cmake g++ build-essential \
  libeigen3-dev libyaml-cpp-dev python3-pip python3-venv
```

---

## Build (C++ examples)

```bash
git clone https://github.com/willnien10005914/q1_robot_sdk.git
cd q1_robot_sdk
mkdir build && cd build
cmake .. -DBUILD_EXAMPLES=ON
make -j$(nproc)
```

Pre-SDK note: the shared library is header-first / stub-backed until hardware bring-up. Examples compile against the public API and a local mock channel for CI.

---

## Python quickstart

```bash
cd python
python3 -m venv .venv && source .venv/bin/activate
pip install -e .
python -c "from q1_sdk import LocoClient; print(LocoClient.__doc__)"
```

---

## Hello motion (high-level)

```cpp
#include <q1/robot/loco/loco_client.hpp>

int main() {
  q1::ChannelFactory::Instance()->Init(/*domain*/0, "eth0");
  q1::robot::LocoClient loco;
  loco.Init();
  loco.SetTimeout(5.f);
  loco.Standby();                 // soft hold
  loco.SetVelocity(0.2f, 0.f, 0.3f, /*duration*/2.f);  // vx, vy, yaw
  loco.StopMove();
  return 0;
}
```

```python
from q1_sdk import LocoClient, InteractionClient

loco = LocoClient(iface="eth0")
loco.standby()
loco.set_velocity(vx=0.15, vy=0.0, vyaw=0.0, duration=1.5)

ix = InteractionClient(iface="eth0")
ix.play_action("soft_baseball_toss")  # home kid-safe pack
```

---

## Develop Guide map (Edu path)

Q1 Edu learning path:

| Chapter | Topic |
|---------|-------|
| 1 | [Getting started](docs/develop_guide/01_getting_started.md) |
| 2 | [DDS bus & topics](docs/develop_guide/02_dds.md) |
| 3 | [ROS 2 integration](docs/develop_guide/03_ros.md) |
| 4 | [High / low-level API](docs/develop_guide/04_api.md) |
| 5 | [Basic motion](docs/develop_guide/05_basic_motion.md) |
| 6 | [Reinforcement learning](docs/develop_guide/06_rl.md) |
| 7 | [AI training workflow](docs/develop_guide/07_ai_training.md) |
| 8 | [Sim-to-Sim](docs/develop_guide/08_sim_to_sim.md) |
| 9 | [Sim-to-Real](docs/develop_guide/09_sim_to_real.md) |
| 10 | [Use cases](docs/develop_guide/10_use_cases.md) (piano · calligraphy · soft baseball) |

---

## Safety (always on)

- Deadman / soft-estop on wireless + DDS heartbeat timeout (default 500 ms).
- Kid-interaction packs clamp end-effector speed and contact force estimates.
- Low-level `rt/lowcmd` requires explicit `SwitchToUserCtrl` lease (requires an explicit user-control lease).

---

## License

Apache-2.0 — see [LICENSE](LICENSE).

