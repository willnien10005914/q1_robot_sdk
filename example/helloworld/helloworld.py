#!/usr/bin/env python3
import argparse
from q1_sdk import LocoClient

def main():
    p = argparse.ArgumentParser()
    p.add_argument("--mock", action="store_true", default=True)
    p.add_argument("--iface", default="mock")
    args = p.parse_args()
    iface = "mock" if args.mock else args.iface
    loco = LocoClient(iface=iface)
    print(f"[q1] LocoClient connected iface={iface}")
    print(f"[q1] fsm={loco.get_fsm_id()} Hello, Q1!")

if __name__ == "__main__":
    main()
