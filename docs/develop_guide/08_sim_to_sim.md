# 08 — Sim-to-Sim

Sim2Sim checks that a policy is not overfit to one simulator’s quirks (e.g. validate Isaac/Gym policies in MuJoCo before Sim2Real).

## Flow

```text
Isaac / Gym train  →  export policy_1.pt  →  MuJoCo deploy_mujoco.py
```

## Run

```bash
python rl/deploy/sim2sim/deploy_mujoco.py q1_wheeled.yaml
```

Edit `policy_path` inside `rl/deploy/configs/q1_wheeled.yaml` to point at your exported Actor.

## Pass / fail checklist

- [ ] Tracks step velocity commands without sustained oscillation
- [ ] Survives friction ±20% randomization
- [ ] No NaNs for 60 s continuous run
- [ ] Arm residual (if any) stays within joint limits

## Next

→ [09 Sim-to-Real](09_sim_to_real.md)
