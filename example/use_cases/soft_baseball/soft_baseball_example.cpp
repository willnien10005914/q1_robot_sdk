#include <iostream>
#include <string>
#include <q1/channel/channel_factory.hpp>
#include <q1/robot/loco/loco_client.hpp>
#include <q1/robot/interaction/interaction_client.hpp>

int main(int argc, char** argv) {
  std::string iface = "mock";
  std::string pack = "soft_baseball_toss";
  for (int i = 1; i < argc; ++i) {
    std::string a = argv[i];
    if (a == "--mock") iface = "mock";
    if (a.rfind("--action=", 0) == 0) {
      // keep default pack mapping for Pre-SDK demos
    }
  }
  q1::ChannelFactory::Instance()->Init(0, iface);
  q1::robot::LocoClient loco;
  loco.Init();
  loco.Standby();
  q1::robot::InteractionClient ix;
  ix.Init();
  std::cout << "[usecase:soft_baseball] play " << pack << "\n";
  ix.PlayAction(pack);
  ix.Stop();
  return 0;
}
