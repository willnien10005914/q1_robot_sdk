from ..channel import ChannelFactory

class LocoClient:
    """High-level wheeled locomotion client (sport service)."""

    def __init__(self, iface: str = "mock", domain_id: int = 0):
        ChannelFactory.instance().init(domain_id, iface)
        self._fsm = 1

    def get_fsm_id(self) -> int:
        return self._fsm

    def standby(self) -> int:
        self._fsm = 1
        return 0

    def damp(self) -> int:
        self._fsm = 0
        return 0

    def set_velocity(self, vx: float, vy: float = 0.0, vyaw: float = 0.0, duration: float = 1.0) -> int:
        self._fsm = 2
        self._last = (vx, vy, vyaw, duration)
        return 0

    def stop_move(self) -> int:
        self._fsm = 1
        return 0

    def switch_to_user_ctrl(self) -> int:
        self._fsm = 10
        return 0

    def switch_to_internal_ctrl(self) -> int:
        self._fsm = 1
        return 0
