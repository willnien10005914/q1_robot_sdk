#pragma once
#include <array>
#include <cstdint>

namespace q1 {
namespace msg {

struct ImuState {
  std::array<float, 4> quaternion{1.f, 0.f, 0.f, 0.f};  // wxyz
  std::array<float, 3> gyroscope{};
  std::array<float, 3> accelerometer{};
};

struct WheelState {
  float q{0.f};
  float dq{0.f};
  float tau_est{0.f};
};

struct JointState {
  float q{0.f};
  float dq{0.f};
  float tau_est{0.f};
  float temperature{0.f};
};

/** Mirrors G1-style LowState for Edu familiarity, wheeled-adapted. */
struct LowState {
  uint32_t tick{0};
  uint8_t fsm_id{1};
  uint8_t battery_percent{100};
  ImuState imu{};
  std::array<WheelState, 2> wheel{};   // left, right
  std::array<JointState, 14> joint{};  // dual 7-DoF arms (placeholder)
  uint32_t fault_bits{0};
};

}  // namespace msg
}  // namespace q1
