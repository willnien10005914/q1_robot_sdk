#!/usr/bin/env python3
import argparse
from q1_rl_gym.envs.q1_wheeled import Q1WheeledEnv

def main():
    p = argparse.ArgumentParser()
    p.add_argument("--task", required=True)
    args = p.parse_args()
    env = Q1WheeledEnv()
    obs = env.reset()
    for i in range(20):
        obs, reward, done, info = env.step([0.0, 0.0])
    print(f"[play:{args.task}] ok — would export Actor to logs/{args.task}/exported/policies/")

if __name__ == "__main__":
    main()
