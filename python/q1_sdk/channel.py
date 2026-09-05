class ChannelFactory:
    _inst = None

    def __init__(self):
        self.domain_id = 0
        self.iface = "mock"
        self.inited = False

    @classmethod
    def instance(cls):
        if cls._inst is None:
            cls._inst = ChannelFactory()
        return cls._inst

    def init(self, domain_id: int = 0, iface: str = "mock"):
        self.domain_id = domain_id
        self.iface = iface
        self.inited = True

    @property
    def is_mock(self) -> bool:
        return self.iface in ("mock", "lo")
