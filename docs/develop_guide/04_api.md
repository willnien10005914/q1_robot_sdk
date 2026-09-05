# 04 — API

High-level clients talk to onboard services with versioned API IDs (JSON request/response over DDS).

## Clients

| Client | Service name | Purpose |
|--------|--------------|---------|
| `q1::robot::LocoClient` | `sport` | Wheeled locomotion FSM + velocity |
| `q1::robot::ArmClient` | `arm` | Dual-arm joint / Cartesian helpers |
| `q1::robot::InteractionClient` | `interaction` | Named action packs (predefined on Standard; extensible on Education) |
| `q1::robot::AudioClient` | `audio` | TTS / beep (optional) |

## Loco API IDs (excerpt)

| ID | Symbol | Method |
|----|--------|--------|
| 7001 | `GET_FSM_ID` | `GetFsmId` |
| 7101 | `SET_FSM_ID` | `SetFsmId` |
| 7105 | `SET_VELOCITY` | `SetVelocity(vx, vy, vyaw, duration)` |
| 7110 | `SWITCH_TO_USER_CTRL` | `SwitchToUserCtrl` |
| 7111 | `SWITCH_TO_INTERNAL_CTRL` | `SwitchToInternalCtrl` |

Full list: [`include/q1/robot/loco/loco_api.hpp`](../../include/q1/robot/loco/loco_api.hpp)

## FSM (wheeled)

| ID | Name | Notes |
|----|------|-------|
| 0 | `DAMP` | Safe passive |
| 1 | `STANDBY` | Soft hold, brakes lightly |
| 2 | `MOVE` | Accepts velocity commands |
| 3 | `RECOVERY` | Clear fault → standby |
| 10 | `USER_CTRL` | Low-level lease active |

## Sugar API

```cpp
loco.Damp();
loco.Standby();
loco.Move(0.2f, 0.f, 0.0f);   // vx, vy, vyaw
loco.StopMove();
loco.SwitchToUserCtrl();
loco.SwitchToInternalCtrl();
```

## Arm + interaction

```cpp
arm.SetJointTargets(q_left, q_right, /*kp*/{}, /*kd*/{});
arm.PlayPreset("home");
ix.PlayAction("piano_c_major_scale");
ix.PlayAction("calligraphy_stroke_heng");
ix.PlayAction("soft_baseball_toss");
```

## Error handling

All `Call` paths return `int32_t` (`0` = OK). See `loco_error.hpp` for codes (`TIMEOUT`, `FSM_REJECT`, `LEASE_HELD`, …).

## Next

→ [05 Basic motion](05_basic_motion.md)
