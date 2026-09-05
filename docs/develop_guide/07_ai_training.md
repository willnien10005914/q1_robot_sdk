# 07 — AI Training

## Curriculum tips for Edu users

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

For piano / calligraphy, treat them as **trajectory priors + residual RL** rather than pure end-to-end from scratch. Pre-SDK provides scripted packs; Official SDK adds residual fine-tune configs.

## Next

→ [08 Sim-to-Sim](08_sim_to_sim.md)
