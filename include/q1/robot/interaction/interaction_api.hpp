#pragma once
#include <cstdint>
#include <string>
#include <vector>

namespace q1 {
namespace robot {

const std::string INTERACTION_SERVICE_NAME = "interaction";
const std::string INTERACTION_API_VERSION = "1.0.0.0";

const int32_t ROBOT_API_ID_IX_PLAY_ACTION = 9001;
const int32_t ROBOT_API_ID_IX_LIST_ACTIONS = 9002;
const int32_t ROBOT_API_ID_IX_STOP = 9003;

/** Pre-SDK CES / home demo pack ids. */
inline const std::vector<std::string>& BuiltinActions() {
  static const std::vector<std::string> kActions = {
      "piano_c_major_scale",
      "piano_twinkle",
      "calligraphy_stroke_heng",
      "calligraphy_stroke_shu",
      "soft_baseball_toss",
      "soft_baseball_roll",
  };
  return kActions;
}

}  // namespace robot
}  // namespace q1
