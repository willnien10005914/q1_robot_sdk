# 10 — Use Cases (Home Interaction)

Pre-SDK showcases three **family-safe** actions for CES storytelling and Education-edition bring-up. Packs are named skills on `InteractionClient` (runnable as predefined packs on Standard; retrainable on Education).

## 1) Piano

**Goal:** Play a short scale / nursery phrase on a MIDI or toy keyboard.

```bash
./bin/q1_usecase_piano --mock --phrase c_major_scale
```

```python
from q1_sdk import InteractionClient
InteractionClient(mock=True).play_action("piano_c_major_scale")
```

Design notes:

- Base locks in `Standby`
- Finger / end-effector taps from a timed joint trajectory
- Velocity clamp for kid-safe demos

## 2) Calligraphy

**Goal:** Brush a basic stroke (`heng` / `shu`) on a whiteboard or paper pad.

```bash
./bin/q1_usecase_calligraphy --mock --stroke heng
```

Design notes:

- Cartesian stroke library in `example/use_cases/calligraphy/strokes.yaml`
- Constant contact force estimate via residual PD (sim)

## 3) Soft baseball (play with kids)

**Goal:** Underarm toss / roll a **soft** foam ball for backyard play.

```bash
./bin/q1_usecase_soft_baseball --mock --action toss
```

Hard rules:

- Foam / soft ball only — enforced in docs & CES runbook
- No overhand pitch mode in Pre-SDK
- Exclusion zone: stop if person detector (optional) flags &lt; 0.8 m (Official)

## Adding your own pack

1. Record or keyframe a trajectory in sim
2. Save under `example/use_cases/<name>/`
3. Register string id in `interaction_api.hpp`
4. Submit a PR — Pre-SDK welcomes community packs tagged `usecase`

## CES 2027 booth flow (draft)

1. Soft baseball toss (crowd energy)
2. Piano phrase (precision)
3. Calligraphy stroke (culture / calm)
4. Free teleop for press (deadman on)
