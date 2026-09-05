#pragma once
#include <cstdint>
#include <string>

namespace q1 {
namespace robot {

const std::string ARM_SERVICE_NAME = "arm";
const std::string ARM_API_VERSION = "1.0.0.0";

const int32_t ROBOT_API_ID_ARM_PLAY_PRESET = 8001;
const int32_t ROBOT_API_ID_ARM_SET_JOINT_TARGETS = 8002;
const int32_t ROBOT_API_ID_ARM_STOP = 8003;

}  // namespace robot
}  // namespace q1
