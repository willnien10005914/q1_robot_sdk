#pragma once

namespace q1 {
namespace safety {

constexpr float kMaxVx = 1.2f;
constexpr float kMaxVyaw = 2.0f;
constexpr float kHeartbeatTimeoutS = 0.5f;
constexpr float kInteractionEeSpeed = 0.35f;

inline float ClampVx(float vx) {
  if (vx > kMaxVx) return kMaxVx;
  if (vx < -kMaxVx) return -kMaxVx;
  return vx;
}

inline float ClampVyaw(float w) {
  if (w > kMaxVyaw) return kMaxVyaw;
  if (w < -kMaxVyaw) return -kMaxVyaw;
  return w;
}

}  // namespace safety
}  // namespace q1
