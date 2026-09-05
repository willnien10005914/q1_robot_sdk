# Q1 editions: Standard vs Education

Q1 ships in two software/hardware unlock tiers. **Education** means the **developer / secondary-development** edition of the robot and SDK (tunable motors, custom skills, PPO, VLA) — not a classroom curriculum product.

| | **Standard** | **Education** (this SDK targets) |
|--|--------------|----------------------------------|
| Motor / servo parameters | Locked — OEM defaults only | Open — tune gains, limits, torque/current clamps |
| Motion | Run **predefined** actions / motions only | Custom controllers + new skills |
| Low-level bus | High-level clients only (no `rt/lowcmd` lease) | High-level **and** low-level (`UserCtrl` lease → `rt/lowcmd` / `rt/lowstate`) |
| RL | Playback of factory policies | **PPO** (and related) Train → Play → Sim2Sim → Sim2Real |
| VLA | Optional cloud demos if offered | On-device / on-host **Vision–Language–Action** fine-tune & deploy |
| Secondary development | App-level scripting of named packs | Full SDK: DDS, ROS 2, RL gym, VLA adapters |
| Simulation training | Playback / limited demos | **MuJoCo** · **Isaac Sim** · **Isaac Lab** |
| Onboard SoC | OEM compute (locked skill runtime) | **2026:** Jetson AGX Orin EVK · **2027:** Qualcomm IQ9 low-cost EVK |

## Why Education exists

Partners and labs need to:

1. Change motor-side behavior safely under documented limits.
2. Train **new locomotion / manipulation** with PPO (and imitation).
3. Connect cameras + language goals through a **VLA** stack that outputs robot actions.

Standard units stay locked for end users who only need reliable predefined skills (home clean, logistics demos, entertainment packs).

## Related docs

- [Develop Guide](develop_guide/index.md) — Education edition on-ramp
- [RL](develop_guide/06_rl.md) — PPO Train / Play
- [AI training & VLA](develop_guide/07_ai_training.md) — rewards, export, VLA notes
- [Architecture](architecture.md) — Internal vs UserCtrl leases
