#pragma once
#include <array>

namespace q1 {
namespace msg {

struct Odom {
  double x{0.0};
  double y{0.0};
  double yaw{0.0};
  std::array<float, 3> twist{};  // vx, vy, vyaw
};

}  // namespace msg
}  // namespace q1
