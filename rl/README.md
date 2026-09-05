# Q1 RL Gym

Train → Play → Sim2Sim → Sim2Real for the dual-wheel Q1.

```bash
python -m q1_rl_gym.scripts.train --task q1_wheeled --headless
python -m q1_rl_gym.scripts.play --task q1_wheeled
python deploy/sim2sim/deploy_mujoco.py q1_wheeled.yaml
python deploy/sim2real/deploy_real.py mock q1_wheeled.yaml
```

See [Develop Guide — RL](../docs/develop_guide/06_rl.md).
