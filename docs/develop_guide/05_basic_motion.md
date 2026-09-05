# 05 — Basic Motion

## Differential drive model

Q1’s base is a **two-wheel differential drive** (optional casters for stability).

```text
v_left  = vx - (track_width/2) * vyaw
v_right = vx + (track_width/2) * vyaw
```

High-level apps should prefer `SetVelocity` and let the onboard controller handle wheel tracking.

## Recommended first sequence

1. `Standby()` — confirm FSM
2. Small `SetVelocity(0.1, 0, 0, 2.0)` — forward creep
3. `StopMove()` then yaw in place
4. `Damp()` on exit

```bash
./bin/q1_loco_example --mock --set_velocity="0.1 0 0.2 2.0"
```

## Arm basics

- Use presets (`home`, `ready`, `tuck`) before free joint motion.
- Interpolate in joint space at ≤ 60 Hz for demos; RL policies may run 50–200 Hz.
- Keep wrists away from wheel wells (URDF collision geoms provided in Official SDK).

## Deadman rule

For teleop and kid-facing packs: **both grips / hold-to-run** must be asserted or velocity is forced to zero. Same safety idea as Edu “squeeze grips for IK”.

## Next

→ [06 Reinforcement learning](06_rl.md)
