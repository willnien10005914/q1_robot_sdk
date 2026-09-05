#!/usr/bin/env python3
"""Train entrypoint — Pre-SDK stub that exercises the env API."""
from __future__ import annotations
import argparse
from q1_rl_gym.envs.q1_wheeled import Q1WheeledEnv

TASKS = {"q1_wheeled": Q1WheeledEnv}

def main():
    p = argparse.ArgumentParser()
    p.add_argument("--task", required=True, choices=sorted(TASKS))
    p.add_argument("--headless", action="store_true")
    p.add_argument("--max_iterations", type=int, default=10)
    args = p.parse_args()
    env = TASKS[args.task]()
    obs = env.reset()
    for i in range(args.max_iterations):
        action = [0.0] * env.act_dim
        obs, reward, done, info = env.step(action)
        if i % 5 == 0:
            print(f"[train:{args.task}] iter={i} reward={reward}")
    print(f"[train] done — export path placeholder: logs/{args.task}/exported/policies/policy_1.pt")

if __name__ == "__main__":
    main()
