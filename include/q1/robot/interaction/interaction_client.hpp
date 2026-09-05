#pragma once
#include "interaction_api.hpp"
#include "../../client/client.hpp"

namespace q1 {
namespace robot {

class InteractionClient : public Client {
 public:
  InteractionClient() : Client(INTERACTION_SERVICE_NAME, false) {}

  void Init() {
    SetApiVersion(INTERACTION_API_VERSION);
    RegApi(ROBOT_API_ID_IX_PLAY_ACTION);
    RegApi(ROBOT_API_ID_IX_LIST_ACTIONS);
    RegApi(ROBOT_API_ID_IX_STOP);
  }

  int32_t PlayAction(const std::string& action_id) {
    std::string data;
    return Call(ROBOT_API_ID_IX_PLAY_ACTION, action_id, data);
  }

  int32_t Stop() {
    std::string data;
    return Call(ROBOT_API_ID_IX_STOP, "", data);
  }
};

}  // namespace robot
}  // namespace q1
