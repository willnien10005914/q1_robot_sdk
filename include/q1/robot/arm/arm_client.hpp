#pragma once
#include <array>
#include <sstream>
#include "arm_api.hpp"
#include "../../client/client.hpp"

namespace q1 {
namespace robot {

class ArmClient : public Client {
 public:
  ArmClient() : Client(ARM_SERVICE_NAME, false) {}

  void Init() {
    SetApiVersion(ARM_API_VERSION);
    RegApi(ROBOT_API_ID_ARM_PLAY_PRESET);
    RegApi(ROBOT_API_ID_ARM_SET_JOINT_TARGETS);
    RegApi(ROBOT_API_ID_ARM_STOP);
  }

  int32_t PlayPreset(const std::string& name) {
    std::string data;
    return Call(ROBOT_API_ID_ARM_PLAY_PRESET, name, data);
  }

  int32_t SetJointTargets(const std::array<float, 7>& left,
                          const std::array<float, 7>& right) {
    std::ostringstream oss;
    oss << "{\"left\":[";
    for (size_t i = 0; i < left.size(); ++i) {
      if (i) oss << ",";
      oss << left[i];
    }
    oss << "],\"right\":[";
    for (size_t i = 0; i < right.size(); ++i) {
      if (i) oss << ",";
      oss << right[i];
    }
    oss << "]}";
    std::string data;
    return Call(ROBOT_API_ID_ARM_SET_JOINT_TARGETS, oss.str(), data);
  }

  int32_t Stop() {
    std::string data;
    return Call(ROBOT_API_ID_ARM_STOP, "", data);
  }
};

}  // namespace robot
}  // namespace q1
