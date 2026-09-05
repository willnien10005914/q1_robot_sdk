# Architecture

## System architecture diagram

Full compute & control stack (SoC → ROS 2 → real-time MCU → CAN FD / EtherCAT → joints):

![Q1 compute & control architecture](../media/architecture/q1_compute_control_architecture.png)

## Design principles (Education edition)

Q1 Education SDK exposes the same developer-facing split used for secondary development:

1. **High-level service clients** — JSON request/response over DDS (`sport` / `arm` / `interaction` services). Available on Standard and Education.
2. **Low-level realtime topics** — `rt/lowcmd`, `rt/lowstate` for joint/wheel setpoints when a **UserCtrl lease** is held (**Education** only).
3. **ROS 2 as a peer** — optional bridge; keep robot DDS domain isolated from the ROS graph when needed.
4. **RL / VLA deploy chain** — PPO Train → Play → Sim2Sim → Sim2Real; VLA fine-tune → action head (**Education**).

Standard units stay on high-level predefined packs without motor-parameter or `rt/lowcmd` access. See [editions.md](editions.md).

## Process view

```text
┌──────────────────────────── PC / Dev Host ────────────────────────────┐
│  User App (C++/Python)                                                 │
│    └─ q1::LocoClient / ArmClient / InteractionClient                   │
│  ROS 2 nodes (q1_driver, teleop) ──optional──┐                         │
│  PPO deploy_real.py / VLA runtime             │                        │
└─────────────────────── DDS / CycloneDDS ──────┼────────────────────────┘
                                                │ domain 0 (robot bus)
┌──────────────────────────── Q1 Onboard ───────┼────────────────────────┐
│  Motion Manager (sport service)               │                        │
│  Arm Manager                                   │                        │
│  Safety Supervisor (estop, torque limits)      │                        │
│  Wheel MCU + Arm MCUs ◄── rt/lowcmd / lowstate ┘  (Education UserCtrl) │
└────────────────────────────────────────────────────────────────────────┘
```

## Control modes

| Mode | How to enter | Topics / APIs | Typical use |
|------|--------------|---------------|-------------|
| **Internal** | Boot / `SwitchToInternalCtrl` | High-level `SetVelocity`, actions | Default demos (Standard + Education) |
| **UserCtrl** | `SwitchToUserCtrl` (lease) | Publish `rt/lowcmd`, read `rt/lowstate` | Custom PPO / teleop / VLA (**Education**) |
| **Passive / Damp** | `Damp()` | Motors impedance hold | Safe idle |

Wheeled kinematics are the internal controller core for 2026–2027; biped modes follow on the next-gen track.

## Topic map (DDS)

See the Develop Guide [DDS chapter](develop_guide/02_dds.md) for `rt/*` names and QoS defaults.

## Safety leases

- Only one UserCtrl lease holder may publish `rt/lowcmd`.
- Heartbeat timeout drops the lease and returns Internal / Damp.
- Motor parameter writes on Education units are rate-limited and clamped by the safety supervisor.
