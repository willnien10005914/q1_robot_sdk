# Q1 SDK Develop Guide

Welcome. This guide is the on-ramp for the **Q1 Education edition** — the developer / secondary-development track (tunable motors, low-level DDS, **PPO** RL, **VLA**). “Education” names the unlock tier versus **Standard** (predefined motions only), not a classroom curriculum.

See [Standard vs Education](../editions.md).

## Learning path

```text
Network + DDS  →  High-level API  →  Basic motion
        ↓                ↓
      ROS 2         Low-level joints / wheels (Education)
        ↓
   PPO Train → Play → Sim2Sim → Sim2Real
        ↓
   VLA fine-tune (vision + language → action)
        ↓
   Interaction packs (piano / calligraphy / soft baseball)
```

## Chapters

| # | Document | You will learn |
|---|----------|----------------|
| 0 | [Architecture overview](../architecture.md) | Processes, domains, safety leases |
| — | [Standard vs Education](../editions.md) | Motor unlock, PPO, VLA matrix |
| 1 | [Getting started](01_getting_started.md) | Install, build, mock channel, first Hello |
| 2 | [DDS](02_dds.md) | CycloneDDS, `rt/*` topics, QoS, domains |
| 3 | [ROS 2](03_ros.md) | `q1_msgs`, driver bridge, teleop |
| 4 | [API](04_api.md) | Loco / Arm / Interaction clients, FSM |
| 5 | [Basic motion](05_basic_motion.md) | Diff-drive, soft-stop, arm trajectories |
| 6 | [Reinforcement learning](06_rl.md) | `q1_rl_gym` PPO task API |
| 7 | [AI training & VLA](07_ai_training.md) | Rewards, export, Vision–Language–Action |
| 8 | [Sim-to-Sim](08_sim_to_sim.md) | Isaac/Gym → MuJoCo validation |
| 9 | [Sim-to-Real](09_sim_to_real.md) | Deploy checklist for physical Q1 |
| 10 | [Use cases](10_use_cases.md) | Piano, calligraphy, soft baseball |

## Pre-SDK vs Official

| | Pre-SDK (from 2026-10) | Official (2027) |
|--|------------------------|-----------------|
| Headers / Python stubs | ✅ | ✅ |
| Mock DDS channel | ✅ | ✅ |
| Real robot firmware bridge | 🔜 CES bring-up | ✅ |
| Signed action packs | Demo packs | Education catalog |
| PPO / VLA toolchains | Gym stubs + Colab | Full train → deploy |
| Biped + dexterous hand | Roadmap only | Next-gen track |

## Related

- [Roadmap & milestones](../roadmap.md)
- [References](../REFERENCES.md)
