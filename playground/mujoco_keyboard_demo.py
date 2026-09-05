#!/usr/bin/env python3
"""Q1 MuJoCo keyboard playground — Quanta Computer MIT Taiwan.

Controls
--------
  W / S       Drive forward / backward (wheel mode)
  A / D       Turn left / right
  T           Toggle wheel ↔ biped transform
  1           Force WHEEL mode
  2           Force BIPED mode
  R           Reset pose
  SPACE       Emergency stop (zero wheel torques)
  ESC / Q     Quit

Requires: mujoco, a display (or MUJOCO_GL=egl for offscreen)
"""

from __future__ import annotations

import argparse
import math
import time
from pathlib import Path

import mujoco
import mujoco.viewer
import numpy as np

ROOT = Path(__file__).resolve().parents[1]
DEFAULT_XML = ROOT / "models" / "q1" / "q1_wheel_foot.xml"

# actuator indices (must match XML order)
A_L_DRIVE, A_R_DRIVE = 0, 1
A_L_TF, A_R_TF = 2, 3
A_L_HIP, A_R_HIP = 4, 5
A_L_KNEE, A_R_KNEE = 6, 7
A_L_ANKLE, A_R_ANKLE = 8, 9

WHEEL_TF = 0.0
BIPED_TF = math.pi / 2


class Q1Playground:
    def __init__(self, xml_path: Path):
        self.model = mujoco.MjModel.from_xml_path(str(xml_path))
        self.data = mujoco.MjData(self.model)
        self.mode = "wheel"  # or biped
        self.drive = 0.0
        self.turn = 0.0
        self.transform_target = WHEEL_TF
        self._apply_stance()

    def _apply_stance(self) -> None:
        d = self.data
        # standing posture targets
        if self.mode == "wheel":
            d.ctrl[A_L_HIP] = d.ctrl[A_R_HIP] = 0.05
            d.ctrl[A_L_KNEE] = d.ctrl[A_R_KNEE] = 0.12
            d.ctrl[A_L_ANKLE] = d.ctrl[A_R_ANKLE] = -0.05
            self.transform_target = WHEEL_TF
        else:
            d.ctrl[A_L_HIP] = d.ctrl[A_R_HIP] = 0.15
            d.ctrl[A_L_KNEE] = d.ctrl[A_R_KNEE] = 0.35
            d.ctrl[A_L_ANKLE] = d.ctrl[A_R_ANKLE] = -0.15
            self.transform_target = BIPED_TF
        d.ctrl[A_L_TF] = d.ctrl[A_R_TF] = self.transform_target

    def reset(self) -> None:
        mujoco.mj_resetData(self.model, self.data)
        self.data.qpos[2] = 0.78
        self.data.qpos[3:7] = np.array([1, 0, 0, 0])
        self.mode = "wheel"
        self.drive = 0.0
        self.turn = 0.0
        self._apply_stance()
        mujoco.mj_forward(self.model, self.data)

    def set_mode(self, mode: str) -> None:
        self.mode = mode
        self._apply_stance()
        print(f"[Q1] mode -> {mode.upper()}")

    def toggle_mode(self) -> None:
        self.set_mode("biped" if self.mode == "wheel" else "wheel")

    def step(self) -> None:
        d = self.data
        d.ctrl[A_L_TF] = self.transform_target
        d.ctrl[A_R_TF] = self.transform_target
        if self.mode == "wheel":
            left = self.drive - self.turn
            right = self.drive + self.turn
            d.ctrl[A_L_DRIVE] = left
            d.ctrl[A_R_DRIVE] = right
        else:
            # biped: hold stance, small hip lean for "walk intent"
            d.ctrl[A_L_DRIVE] = 0.0
            d.ctrl[A_R_DRIVE] = 0.0
            d.ctrl[A_L_HIP] = 0.15 + 0.05 * self.drive
            d.ctrl[A_R_HIP] = 0.15 + 0.05 * self.drive
        mujoco.mj_step(self.model, self.data)


def run_interactive(xml: Path) -> None:
    app = Q1Playground(xml)
    app.reset()
    print(__doc__)
    print(f"Loaded: {xml}")

    with mujoco.viewer.launch_passive(app.model, app.data) as viewer:
        viewer.cam.distance = 3.2
        viewer.cam.elevation = -15
        viewer.cam.azimuth = 135
        while viewer.is_running():
            step_start = time.time()
            # Poll keys via viewer (MuJoCo 3 passive viewer)
            # Fallback: use held-key state through glfw if available
            keys = getattr(viewer, "key", None)
            # Use mjpython-style: read from last key callbacks via custom map
            # The passive viewer exposes .cam but not easy keys on all builds;
            # use a simple stdin-nonblocking pattern + on_key if present.
            app.step()
            viewer.sync()
            # Real-time pacing
            dt = app.model.opt.timestep - (time.time() - step_start)
            if dt > 0:
                time.sleep(dt)


def run_with_glfw_keys(xml: Path) -> None:
    """Interactive loop with explicit GLFW key polling."""
    import glfw

    app = Q1Playground(xml)
    app.reset()

    if not glfw.init():
        raise RuntimeError("GLFW init failed")
    glfw.window_hint(glfw.VISIBLE, glfw.TRUE)
    window = glfw.create_window(1280, 720, "Q1 MuJoCo Playground — Quanta Computer", None, None)
    glfw.make_context_current(window)

    cam = mujoco.MjvCamera()
    opt = mujoco.MjvOption()
    pert = mujoco.MjvPerturb()
    con = mujoco.MjrContext(app.model, mujoco.mjtFontScale.mjFONTSCALE_150)
    scn = mujoco.MjvScene(app.model, maxgeom=10000)
    mujoco.mjv_defaultCamera(cam)
    cam.distance = 3.2
    cam.elevation = -15
    cam.azimuth = 135

    print(__doc__)

    def on_key(win, key, scancode, action, mods):
        if action not in (glfw.PRESS, glfw.REPEAT):
            return
        if key in (glfw.KEY_ESCAPE, glfw.KEY_Q):
            glfw.set_window_should_close(win, True)
        elif key == glfw.KEY_T and action == glfw.PRESS:
            app.toggle_mode()
        elif key == glfw.KEY_1:
            app.set_mode("wheel")
        elif key == glfw.KEY_2:
            app.set_mode("biped")
        elif key == glfw.KEY_R:
            app.reset()
            print("[Q1] reset")
        elif key == glfw.KEY_SPACE:
            app.drive = 0.0
            app.turn = 0.0

    glfw.set_key_callback(window, on_key)

    while not glfw.window_should_close(window):
        # continuous drive from key state
        app.drive = 0.0
        app.turn = 0.0
        if glfw.get_key(window, glfw.KEY_W) == glfw.PRESS:
            app.drive += 18.0
        if glfw.get_key(window, glfw.KEY_S) == glfw.PRESS:
            app.drive -= 18.0
        if glfw.get_key(window, glfw.KEY_A) == glfw.PRESS:
            app.turn -= 10.0
        if glfw.get_key(window, glfw.KEY_D) == glfw.PRESS:
            app.turn += 10.0

        app.step()

        viewport = mujoco.MjrRect(0, 0, *glfw.get_framebuffer_size(window))
        mujoco.mjv_updateScene(
            app.model, app.data, opt, pert, cam, mujoco.mjtCatBit.mjCAT_ALL, scn
        )
        mujoco.mjr_render(viewport, scn, con)
        # HUD
        mode = app.mode.upper()
        mujoco.mjr_overlay(
            mujoco.mjtFontScale.mjFONTSCALE_150,
            mujoco.mjtGridPos.mjGRID_TOPLEFT,
            viewport,
            f"Q1 Playground | Mode: {mode}",
            "W/S drive  A/D turn  T transform  1 wheel  2 biped  R reset",
            con,
        )
        glfw.swap_buffers(window)
        glfw.poll_events()

    glfw.terminate()


def run_headless_demo(xml: Path, out_mp4: Path, seconds: float = 8.0) -> None:
    """Record a short offscreen demo (CI / no display)."""
    import imageio.v2 as imageio

    app = Q1Playground(xml)
    app.reset()
    renderer = mujoco.Renderer(app.model, height=480, width=640)
    frames = []
    fps = 30
    n = int(seconds * fps)
    print(f"Recording headless demo -> {out_mp4}")
    for i in range(n):
        t = i / fps
        if t < 2.0:
            app.set_mode("wheel") if i == 0 else None
            app.drive = 16.0
        elif t < 4.0:
            if abs(t - 2.0) < 1e-6 or (i == int(2 * fps)):
                app.set_mode("biped")
            app.drive = 0.0
        elif t < 6.0:
            if i == int(4 * fps):
                app.set_mode("wheel")
            app.drive = -14.0
        else:
            app.drive = 12.0
            app.turn = 4.0
        # avoid spam
        if i in (0, int(2 * fps), int(4 * fps)):
            pass
        for _ in range(int(1 / (fps * app.model.opt.timestep))):
            app.step()
        renderer.update_scene(app.data)
        frames.append(renderer.render().copy())
    out_mp4.parent.mkdir(parents=True, exist_ok=True)
    imageio.mimsave(out_mp4, frames, fps=fps)
    print(f"Wrote {out_mp4} ({len(frames)} frames)")


def main() -> None:
    p = argparse.ArgumentParser(description="Q1 MuJoCo keyboard playground")
    p.add_argument("--xml", type=Path, default=DEFAULT_XML)
    p.add_argument("--headless-demo", type=Path, default=None, help="Record MP4 and exit")
    p.add_argument("--passive", action="store_true", help="Use mujoco.viewer.launch_passive")
    args = p.parse_args()

    if args.headless_demo is not None:
        run_headless_demo(args.xml, args.headless_demo)
        return
    if args.passive:
        run_interactive(args.xml)
        return
    try:
        run_with_glfw_keys(args.xml)
    except Exception as exc:
        print(f"GLFW viewer unavailable ({exc}); try --passive or --headless-demo out.mp4")
        raise


if __name__ == "__main__":
    main()
