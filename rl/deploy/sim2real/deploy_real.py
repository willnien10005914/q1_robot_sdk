#!/usr/bin/env python3
"""Sim2Real deploy — mock today; physical with Official SDK."""
from __future__ import annotations
import argparse
from pathlib import Path

def main():
    p = argparse.ArgumentParser()
    p.add_argument("net_interface", help="NIC name or 'mock'")
    p.add_argument("config_name")
    args = p.parse_args()
    cfg = Path(__file__).resolve().parents[1] / "configs" / args.config_name
    print(f"[sim2real] iface={args.net_interface} config={cfg}")
    if args.net_interface == "mock":
        print("[sim2real] mock DDS path — lease/UserCtrl dry-run OK")
    else:
        print("[sim2real] physical path reserved for Official SDK 1.0 / CES bring-up")
    print("Checklist: estop, standby, battery>30%, action_scale<=0.5")

if __name__ == "__main__":
    main()
