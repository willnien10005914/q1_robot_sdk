#include <iostream>
#include <string>
#include <q1/channel/channel_factory.hpp>
#include <q1/common/version.hpp>
#include <q1/robot/loco/loco_client.hpp>

int main(int argc, char** argv) {
  std::string iface = "mock";
  for (int i = 1; i < argc; ++i) {
    std::string a = argv[i];
    if (a == "--mock") iface = "mock";
    if (a.rfind("--iface=", 0) == 0) iface = a.substr(8);
  }

  q1::ChannelFactory::Instance()->Init(0, iface);
  std::cout << "[q1] ChannelFactory Init domain=0 iface=" << iface << "\n";
  std::cout << "[q1] SDK " << Q1_SDK_VERSION_STRING << "\n";

  q1::robot::LocoClient loco;
  loco.Init();
  loco.SetTimeout(5.f);
  std::cout << "[q1] LocoClient connected"
            << (q1::ChannelFactory::Instance()->IsMock() ? " (mock)" : "")
            << "\n";

  int fsm = 0;
  loco.GetFsmId(fsm);
  std::cout << "[q1] fsm=STANDBY battery=100%\n";
  std::cout << "[q1] Hello, Q1!\n";
  return 0;
}
