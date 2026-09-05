#include <iostream>
#include <thread>
#include <chrono>
#include <q1/channel/channel_factory.hpp>
#include <q1/channel/channel_publisher.hpp>
#include <q1/channel/channel_subscriber.hpp>
#include <q1/idl/low_cmd.hpp>
#include <q1/idl/low_state.hpp>
#include <q1/robot/loco/loco_client.hpp>

int main(int argc, char** argv) {
  std::string iface = "mock";
  for (int i = 1; i < argc; ++i) {
    if (std::string(argv[i]) == "--mock") iface = "mock";
  }
  q1::ChannelFactory::Instance()->Init(0, iface);

  q1::robot::LocoClient loco;
  loco.Init();
  loco.SwitchToUserCtrl();

  q1::channel::ChannelSubscriber<q1::msg::LowState> sub("rt/lowstate");
  sub.InitChannel([](const void* msg) {
    auto* s = static_cast<const q1::msg::LowState*>(msg);
    static int n = 0;
    if ((n++ % 50) == 0) {
      std::cout << "lowstate tick=" << s->tick << " fsm=" << int(s->fsm_id) << "\n";
    }
  });

  q1::channel::ChannelPublisher<q1::msg::LowCmd> pub("rt/lowcmd");
  pub.InitChannel();

  for (int i = 0; i < 100; ++i) {
    q1::msg::LowState st{};
    st.tick = i;
    st.fsm_id = 10;
    sub.MockPush(st);

    q1::msg::LowCmd cmd{};
    cmd.tick = i;
    cmd.wheel[0].mode = 1;
    cmd.wheel[1].mode = 1;
    cmd.wheel[0].dq = 0.2f;
    cmd.wheel[1].dq = 0.2f;
    pub.Write(&cmd);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }

  loco.SwitchToInternalCtrl();
  loco.Damp();
  std::cout << "user_ctrl example done\n";
  return 0;
}
