# Q1 SDK Develop Guide

Welcome. This guide is the Edu curriculum for Q1 — the same topics Edu-class developers typically learn (DDS, ROS, API, motion, RL, Sim2Sim, Sim2Real), rewritten for a **dual-wheel** robot with interactive arms.

## Learning path

```text
Network + DDS  →  High-level API  →  Basic motion
        ↓                ↓
      ROS 2         Low-level joints / wheels
        ↓
   RL Train → Play → Sim2Sim → Sim2Real
        ↓
   Interaction use cases (piano / calligraphy / soft baseball)
```

## Chapters

| # | Document | You will learn |
|---|----------|----------------|
| 0 | [Architecture overview](../architecture.md) | Processes, domains, safety leases |
| 1 | [Getting started](01_getting_started.md) | Install, build, mock channel, first Hello |
| 2 | [DDS](02_dds.md) | CycloneDDS, `rt/*` topics, QoS, domains |
| 3 | [ROS 2](03_ros.md) | `q1_msgs`, driver bridge, teleop |
| 4 | [API](04_api.md) | Loco / Arm / Interaction clients, FSM |
| 5 | [Basic motion](05_basic_motion.md) | Diff-drive, soft-stop, arm trajectories |
| 6 | [Reinforcement learning](06_rl.md) | `q1_rl_gym` task API |
| 7 | [AI training](07_ai_training.md) | Rewards, observation, export policy |
| 8 | [Sim-to-Sim](08_sim_to_sim.md) | Isaac/Gym → MuJoCo validation |
| 9 | [Sim-to-Real](09_sim_to_real.md) | Deploy checklist for physical Q1 |
| 10 | [Use cases](10_use_cases.md) | Piano, calligraphy, soft baseball |

## Pre-SDK vs Official

| | Pre-SDK (from 2026-10) | Official (2027) |
|--|------------------------|-----------------|
| Headers / Python stubs | ✅ | ✅ |
| Mock DDS channel | ✅ | ✅ |
| Real robot firmware bridge | 🔜 CES bring-up | ✅ |
| Signed action packs | Demo packs | EDU catalog |
| Biped + dexterous hand | Roadmap only | Next-gen track |

## Related

- [Roadmap & milestones](../roadmap.md)
- Upstream study references: [Edu-class Developer Center](https://support.third-party.com/home/en/G1_developer), [third-party_sdk2](https://github.com/third-partyrobotics/third-party_sdk2), [third-party_rl_gym](https://github.com/third-partyrobotics/third-party_rl_gym)
