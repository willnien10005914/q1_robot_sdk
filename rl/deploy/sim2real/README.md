# Physical Deployment Guide

1. Place robot in debug / UserCtrl-ready mode.
2. Connect PC NIC to robot LAN.
3. `python deploy_real.py eth0 q1_wheeled.yaml`
4. Start with reduced `action_scale` in the YAML.

Pre-SDK: use `mock` as the interface name for CI dry-runs.
