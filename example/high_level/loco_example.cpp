#include <iostream>
#include <string>
#include <q1/channel/channel_factory.hpp>
#include <q1/robot/loco/loco_client.hpp>
#include <q1/robot/safety/limits.hpp>

int main(int argc, char** argv) {
  std::string iface = "mock";
  float vx = 0.1f, vy = 0.f, vyaw = 0.f, dur = 2.f;
  for (int i = 1; i < argc; ++i) {
    std::string a = argv[i];
    if (a == "--mock") iface = "mock";
    if (a.rfind("--iface=", 0) == 0) iface = a.substr(8);
    if (a.rfind("--set_velocity=", 0) == 0) {
      sscanf(a.c_str() + 15, "%f %f %f %f", &vx, &vy, &vyaw, &dur);
    }
  }

  q1::ChannelFactory::Instance()->Init(0, iface);
  q1::robot::LocoClient loco;
  loco.Init();
  loco.Standby();
  vx = q1::safety::ClampVx(vx);
  vyaw = q1::safety::ClampVyaw(vyaw);
  std::cout << "SetVelocity " << vx << " " << vy << " " << vyaw << " " << dur << "\n";
  loco.SetVelocity(vx, vy, vyaw, dur);
  loco.StopMove();
  loco.Damp();
  return 0;
}
