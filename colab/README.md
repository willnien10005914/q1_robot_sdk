# Colab — Q1 MuJoCo Playground

## Notebook

[`q1_mujoco_playground_wheel_train.ipynb`](q1_mujoco_playground_wheel_train.ipynb)

| Resource | Link |
|----------|------|
| Structure (Drive PNG) | https://drive.google.com/file/d/1zvOkdKf6-PuOZwCbwdphMXJbkcC-hq13/view |
| Target Colab | https://colab.research.google.com/drive/150OF9mOt5Q_caVPJZgDtuR1g7YIjX9b3?hl=zh-tw |
| Repo assets | `../assets/q1_structure/` (URDF + MJCF) |

## Update the linked Colab

This agent cannot write your private Colab Drive file without Google OAuth. To refresh that notebook:

1. Download [`q1_mujoco_playground_wheel_train.ipynb`](q1_mujoco_playground_wheel_train.ipynb) from this repo (`main`).
2. Open https://colab.research.google.com/drive/150OF9mOt5Q_caVPJZgDtuR1g7YIjX9b3?hl=zh-tw
3. **File → Upload notebook** (replace), then **Runtime → Run all**.

Or open from GitHub after clone:

```text
https://colab.research.google.com/github/willnien10005914/q1_robot_sdk/blob/main/colab/q1_mujoco_playground_wheel_train.ipynb
```

## What the notebook does

1. `gdown` the structure PNG  
2. Write structure-matched **URDF** + **MuJoCo MJCF** (dual-wheel feet)  
3. MuJoCo playground open-loop **forward / backward** MP4  
4. **PPO** train to track `vx` commands (+ forward / − reverse)
