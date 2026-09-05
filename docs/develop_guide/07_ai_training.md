# 07 — AI Training & VLA

Education-edition tips for training **new** skills (not limited to factory packs).

## PPO / RL tips

1. **Start simple** — `q1_wheeled` velocity tracking before arm tasks.
2. **Domain randomize** — friction, mass, latency (±10 ms) early.
3. **Reward shaping** — prefer smooth torque penalties; avoid sparse-only rewards for wheel tracking.
4. **Export often** — Play every N iterations; catch sim hacks before Sim2Sim.

## Reward terms (wheeled defaults)

| Term | Intent |
|------|--------|
| `track_lin_vel` | Match `vx` |
| `track_ang_vel` | Match `vyaw` |
| `alive` | Stay upright / not tipped |
| `smoothness` | Penalize Δaction |
| `torque` | Energy / heat proxy |

## Logging

TensorBoard under `rl/logs/<experiment>/`.

```bash
tensorboard --logdir rl/logs
```

## Policy formats

| Format | Use |
|--------|-----|
| `policy_1.pt` | TorchScript MLP |
| `policy_lstm_1.pt` | Recurrent policies |
| ONNX (optional) | Embedded / C++ runtime later |

## Interaction policies

For piano / calligraphy, treat them as **trajectory priors + residual RL** rather than pure end-to-end from scratch. Pre-SDK provides scripted packs; Official Education SDK adds residual fine-tune configs.

## VLA (Vision–Language–Action)

Education edition supports a VLA path for secondary development:

```text
Camera / proprio  +  language goal
        ↓
  VLA encoder / policy head
        ↓
  Robot actions (high-level skills or lowcmd via UserCtrl)
```

| Piece | Role on Q1 Education |
|-------|----------------------|
| Vision | Head dual-cam / optional depth streams |
| Language | Task prompts (“roll to the box”, “pick the brush”) |
| Action | `InteractionClient` skills, loco setpoints, or leased `rt/lowcmd` |
| Train | Imitation / RL fine-tune on logged episodes (host GPU) |
| Deploy | ONNX / TorchScript on PC or onboard NPU roadmap |

Standard edition may play factory VLA demos if offered, but **cannot** retrain or retarget motor-level actions.

Pre-SDK: interfaces and mock adapters under `rl/` / examples. Official SDK: documented dataset schema + deploy checklist.

## Next

→ [08 Sim-to-Sim](08_sim_to_sim.md)
