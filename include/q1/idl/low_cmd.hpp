#pragma once
#include <array>
#include <cstdint>

namespace q1 {
namespace msg {

struct WheelCmd {
  float q{0.f};
  float dq{0.f};
  float tau{0.f};
  float kp{0.f};
  float kd{0.f};
  uint8_t mode{0};  // 0=disable 1=speed 2=torque
};

struct JointCmd {
  float q{0.f};
  float dq{0.f};
  float tau{0.f};
  float kp{0.f};
  float kd{0.f};
  uint8_t mode{0};
};

struct LowCmd {
  uint32_t tick{0};
  std::array<WheelCmd, 2> wheel{};
  std::array<JointCmd, 14> joint{};
  uint8_t reserve[4]{};
};

}  // namespace msg
}  // namespace q1
