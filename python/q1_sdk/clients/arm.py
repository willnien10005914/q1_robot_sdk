from ..channel import ChannelFactory

class ArmClient:
    def __init__(self, iface: str = "mock", domain_id: int = 0):
        ChannelFactory.instance().init(domain_id, iface)

    def play_preset(self, name: str) -> int:
        self._preset = name
        return 0

    def stop(self) -> int:
        return 0
