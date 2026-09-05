# Q1 Playground

Keyboard-driven demo of the Quanta Computer Q1 transformable wheel-foot humanoid.

## Browser

Open `web/index.html` in a browser (or via GitHub Pages).

| Key | Action |
|-----|--------|
| W / S | Forward / backward |
| A / D | Turn |
| T | Toggle wheel ↔ biped |
| 1 / 2 | Wheel / biped mode |
| R | Reset |

## MuJoCo (local)

```bash
cd ..
python3 -m venv .venv && source .venv/bin/activate
pip install -r playground/requirements.txt
python playground/mujoco_keyboard_demo.py
```

## Models

- `../models/q1/q1_wheel_foot.xml` — MuJoCo MJCF
- `../models/q1/q1_wheel_foot.urdf` — URDF
