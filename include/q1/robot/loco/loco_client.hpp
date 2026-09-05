#pragma once
#include <sstream>
#include "loco_api.hpp"
#include "loco_error.hpp"
#include "../../client/client.hpp"

namespace q1 {
namespace robot {

class LocoClient : public Client {
 public:
  LocoClient() : Client(LOCO_SERVICE_NAME, false) {}

  void Init() {
    SetApiVersion(LOCO_API_VERSION);
    RegApi(ROBOT_API_ID_LOCO_GET_FSM_ID);
    RegApi(ROBOT_API_ID_LOCO_GET_FSM_MODE);
    RegApi(ROBOT_API_ID_LOCO_SET_FSM_ID);
    RegApi(ROBOT_API_ID_LOCO_SET_VELOCITY);
    RegApi(ROBOT_API_ID_LOCO_SET_SPEED_MODE);
    RegApi(ROBOT_API_ID_LOCO_SWITCH_TO_USER_CTRL);
    RegApi(ROBOT_API_ID_LOCO_SWITCH_TO_INTERNAL_CTRL);
    RegApi(ROBOT_API_ID_LOCO_STOP_MOVE);
    RegApi(ROBOT_API_ID_LOCO_DAMP);
    RegApi(ROBOT_API_ID_LOCO_STANDBY);
  }

  int32_t GetFsmId(int& fsm_id) {
    std::string parameter, data;
    int32_t ret = Call(ROBOT_API_ID_LOCO_GET_FSM_ID, parameter, data);
    if (ret == 0) fsm_id = static_cast<int>(FsmId::STANDBY);
    return ret;
  }

  int32_t SetFsmId(int fsm_id) {
    std::string data;
    return Call(ROBOT_API_ID_LOCO_SET_FSM_ID, std::to_string(fsm_id), data);
  }

  int32_t SetVelocity(float vx, float vy, float vyaw, float duration = 1.f) {
    std::ostringstream oss;
    oss << "{\"velocity\":[" << vx << "," << vy << "," << vyaw
        << "],\"duration\":" << duration << "}";
    std::string data;
    return Call(ROBOT_API_ID_LOCO_SET_VELOCITY, oss.str(), data);
  }

  int32_t StopMove() {
    std::string data;
    return Call(ROBOT_API_ID_LOCO_STOP_MOVE, "", data);
  }

  int32_t Damp() {
    std::string data;
    return Call(ROBOT_API_ID_LOCO_DAMP, "", data);
  }

  int32_t Standby() {
    std::string data;
    return Call(ROBOT_API_ID_LOCO_STANDBY, "", data);
  }

  int32_t Move(float vx, float vy, float vyaw) {
    return SetVelocity(vx, vy, vyaw, 1.f);
  }

  int32_t SwitchToUserCtrl() {
    std::string data;
    return Call(ROBOT_API_ID_LOCO_SWITCH_TO_USER_CTRL, "", data);
  }

  int32_t SwitchToInternalCtrl() {
    std::string data;
    return Call(ROBOT_API_ID_LOCO_SWITCH_TO_INTERNAL_CTRL, "", data);
  }
};

}  // namespace robot
}  // namespace q1
