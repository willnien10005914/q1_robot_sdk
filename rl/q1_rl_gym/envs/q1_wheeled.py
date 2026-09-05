"""Minimal wheeled velocity-tracking env stub (replace with Isaac/Gym backend)."""

class Q1WheeledEnv:
    task_id = "q1_wheeled"

    def __init__(self, num_envs: int = 1):
        self.num_envs = num_envs
        self.obs_dim = 16
        self.act_dim = 2  # vx_cmd residual / wheel rates

    def reset(self):
        return [0.0] * self.obs_dim

    def step(self, action):
        obs = [0.0] * self.obs_dim
        reward = 0.0
        done = False
        info = {"task": self.task_id}
        return obs, reward, done, info
