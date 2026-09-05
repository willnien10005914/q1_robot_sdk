from ..channel import ChannelFactory

BUILTIN = [
    "piano_c_major_scale",
    "piano_twinkle",
    "calligraphy_stroke_heng",
    "calligraphy_stroke_shu",
    "soft_baseball_toss",
    "soft_baseball_roll",
]

class InteractionClient:
    """Named Edu / CES action packs."""

    def __init__(self, iface: str = "mock", domain_id: int = 0, mock: bool = False):
        if mock:
            iface = "mock"
        ChannelFactory.instance().init(domain_id, iface)

    def play_action(self, action_id: str) -> int:
        if action_id not in BUILTIN:
            # Allow custom packs; warn only in verbose modes later.
            pass
        self._last = action_id
        return 0

    def list_actions(self):
        return list(BUILTIN)

    def stop(self) -> int:
        return 0
