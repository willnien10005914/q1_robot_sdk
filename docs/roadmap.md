# Roadmap & Milestones

Q1 ships as a **dual-wheel** companion first (CES 2027), then expands to **biped + dexterous hand** manipulation.

## North star

| Year | Platform | SDK goal | Public moment |
|------|----------|----------|---------------|
| **2026** | Dual-wheel Q1 | Pre-SDK: API architecture + interactive use cases | GitHub pre-releases from **October 2026** |
| **2027 H1** | Dual-wheel Q1 Education | Official SDK 1.0 — deploy to physical Education units | **CES 2027** showcase |
| **2027+** | Biped Q1 + dexterous hand | Manipulation SDK track | Manipulation demos / Education expand |

## GitHub milestones

Tracked on: https://github.com/willnien10005914/q1_robot_sdk/milestones

| Milestone | Target | Exit criteria |
|-----------|--------|---------------|
| **M0 — Pre-SDK Bootstrap** | 2026-10 | Repo public, Develop Guide live, C++/Python API stubs, mock channel CI |
| **M1 — Wheeled Loco API** | 2026-11 | `LocoClient` velocity/FSM, DDS `rt/lowcmd|lowstate|odom`, ROS 2 driver skeleton |
| **M2 — Interaction Packs** | 2026-12 | Piano / calligraphy / soft-baseball action demos (sim + mock) |
| **M3 — CES 2027 Wheeled** | 2027-01 | CES demo branch frozen; safety clamps; show-floor runbook |
| **M4 — Official SDK 1.0** | 2027 | Physical deploy path documented; Education partners run PPO / VLA Sim2Real on Q1 |
| **M5 — Biped Preview** | 2027 H2 | Biped URDF + loco research API (preview) |
| **M6 — Dexterous Hand** | 2028 | Hand IDL + grasp primitives + manipulation examples |

## Release cadence (Pre-SDK)

Starting **October 2026**, tagged pre-releases:

```text
v0.1.0-pre  API + DDS topic map + Hello World
v0.2.0-pre  Basic motion + ROS 2 bridge
v0.3.0-pre  Interaction use-case packs
v0.4.0-pre  RL gym Train/Play + Sim2Sim
v0.5.0-pre  Sim2Real dry-run tooling (CES candidate)
v1.0.0      Official Education SDK (physical robot)
```

## Why wheeled first

- Faster safe interaction loop (piano / writing / soft toss) without full biped balance stack.
- Clear Education on-ramp: DDS → API → ROS → PPO → VLA.
- CES 2027 focuses the story: companion mobility + expressive upper body.

## Next generation (biped + hand)

Documented early so Education partners know the multi-year path:

1. Keep the **same DDS client pattern** (`LocoClient` / `ArmClient` / lease model).
2. Add biped FSM modes (`Walk`, `Stand`, `Recover`) without breaking wheeled APIs (`SetVelocity` remains).
3. Dexterous hand as a new `HandClient` service for grasp / brush / key primitives.
