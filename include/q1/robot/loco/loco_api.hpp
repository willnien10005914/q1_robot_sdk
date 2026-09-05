#pragma once
#include <cstdint>
#include <string>

namespace q1 {
namespace robot {

const std::string LOCO_SERVICE_NAME = "sport";
const std::string LOCO_API_VERSION = "1.0.0.0";

const int32_t ROBOT_API_ID_LOCO_GET_FSM_ID = 7001;
const int32_t ROBOT_API_ID_LOCO_GET_FSM_MODE = 7002;
const int32_t ROBOT_API_ID_LOCO_SET_FSM_ID = 7101;
const int32_t ROBOT_API_ID_LOCO_SET_VELOCITY = 7105;
const int32_t ROBOT_API_ID_LOCO_SET_SPEED_MODE = 7107;
const int32_t ROBOT_API_ID_LOCO_SWITCH_TO_USER_CTRL = 7110;
const int32_t ROBOT_API_ID_LOCO_SWITCH_TO_INTERNAL_CTRL = 7111;
const int32_t ROBOT_API_ID_LOCO_STOP_MOVE = 7112;
const int32_t ROBOT_API_ID_LOCO_DAMP = 7113;
const int32_t ROBOT_API_ID_LOCO_STANDBY = 7114;

enum class FsmId : int {
  DAMP = 0,
  STANDBY = 1,
  MOVE = 2,
  RECOVERY = 3,
  USER_CTRL = 10,
};

enum class InternalFsmMode { LAST, PASSIVE, MOVE };

}  // namespace robot
}  // namespace q1
