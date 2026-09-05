# 09 — Sim-to-Real

Physical deploy becomes available with **Official SDK 1.0** (and CES bring-up branches). Pre-SDK provides the dry-run path against mock DDS.

## Dry-run (today)

```bash
python rl/deploy/sim2real/deploy_real.py mock q1_wheeled.yaml
```

## Physical (Official)

```bash
# 1) Robot in debug / UserCtrl-ready mode (see EDU quickstart card)
# 2) PC NIC on robot LAN
python rl/deploy/sim2real/deploy_real.py eth0 q1_wheeled.yaml
```

## Checklist before enabling torque

1. E-stop reachable (hardware + wireless deadman)
2. FSM → `Standby`, battery > 30%
3. `SwitchToUserCtrl` lease acquired
4. Policy obs scaling matches Play config
5. Start with 30–50% action scale gain
6. Watch temperature / fault bits on `rt/lowstate`

## C++ deploy (planned)

```text
rl/deploy/sim2real/cpp_q1/
```

LibTorch runtime example will land with Official SDK — same idea as third-party’s `cpp_q1` deploy sample.

## Next

→ [10 Use cases](10_use_cases.md)
