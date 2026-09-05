# Architecture

## Design principles (G1-inspired, Q1-native)

Q1 follows the same developer-facing split that Unitree G1 Edu users learn:

1. **High-level service clients** — JSON request/response over DDS (`sport` / `arm` / `interaction` services).
2. **Low-level realtime topics** — `rt/lowcmd`, `rt/lowstate` for joint/wheel setpoints when a lease is held.
3. **ROS 2 as a peer** — optional bridge; keep robot DDS domain isolated from the ROS graph when needed.
4. **RL deploy chain** — Train → Play → Sim2Sim → Sim2Real.

## Process view

```text
┌──────────────────────────── PC / Dev Host ────────────────────────────┐
│  User App (C++/Python)                                                 │
│    └─ q1::LocoClient / ArmClient / InteractionClient                   │
│  ROS 2 nodes (q1_driver, teleop) ──optional──┐                         │
│  RL deploy_real.py                            │                        │
└─────────────────────── DDS / CycloneDDS ──────┼────────────────────────┘
                                                │ domain 0 (robot bus)
┌──────────────────────────── Q1 Onboard ───────┼────────────────────────┐
│  Motion Manager (sport service)               │                        │
│  Arm Manager                                   │                        │
│  Safety Supervisor (estop, torque limits)      │                        │
│  Wheel MCU + Arm MCUs ◄── rt/lowcmd / lowstate ┘                       │
└────────────────────────────────────────────────────────────────────────┘
```

## Control modes

| Mode | How to enter | Topics / APIs | Typical use |
|------|--------------|---------------|-------------|
| **Internal** | Boot / `SwitchToInternalCtrl` | High-level `SetVelocity`, actions | Default EDU demos |
| **UserCtrl** | `SwitchToUserCtrl` (lease) | Publish `rt/lowcmd`, read `rt/lowstate` | Custom RL / teleop |
| **Passive / Damp** | `Damp()` | Motors impedance hold | Safe idle |

This mirrors G1’s Internal / UserCtrl / Low-level split, with wheeled kinematics instead of biped balance as the internal controller core for 2026–2027.

## Topic map (DDS)

| Topic | Direction | Payload (conceptual) |
|-------|-----------|----------------------|
| `rt/lowstate` | Robot → App | IMU, wheel encoders, joint q/dq, battery, FSM |
| `rt/lowcmd` | App → Robot | Wheel τ/ω targets + arm PD targets (UserCtrl) |
| `rt/odom` | Robot → App | Planar odometry (x, y, yaw) |
| `rt/sport/request` / `rt/sport/response` | Bidirectional | High-level loco API |
| `rt/arm/request` / `rt/arm/response` | Bidirectional | Arm action API |
| `rt/interaction/request` | Bidirectional | Named action packs |
| `rt/wireless_controller` | Robot → App | Gamepad / deadman |

## Coordinate frames

| Frame | Convention |
|-------|------------|
| `base_link` | FLU (forward-left-up), origin at wheel axle midpoint |
| `odom` | Planar world, z-up |
| Arm joints | Right-handed, URDF order in `assets/urdf/q1.urdf` |

## Safety supervisor

- Heartbeat: client must refresh lease ≤ 500 ms in UserCtrl.
- Velocity clamps: `vx ∈ [-1.2, 1.2] m/s`, `|vyaw| ≤ 2.0 rad/s` (pre-SDK defaults).
- Interaction packs: end-effector Cartesian speed ≤ 0.35 m/s; soft-toy baseball mode disables hard contacts.

## Simulation parity

| Sim | Role |
|-----|------|
| Isaac Gym / Isaac Lab | Parallel RL training |
| MuJoCo | Sim2Sim validation |
| Mock DDS (`q1::mock`) | CI without hardware |
