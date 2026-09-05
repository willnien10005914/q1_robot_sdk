#pragma once
#include <cstdint>
#include <string>
#include "../../client/client.hpp"

namespace q1 {
namespace robot {

const int32_t ROBOT_API_ID_AUDIO_TTS = 9101;
const int32_t ROBOT_API_ID_AUDIO_BEEP = 9102;

class AudioClient : public Client {
 public:
  AudioClient() : Client("audio", false) {}

  void Init() {
    SetApiVersion("1.0.0.0");
    RegApi(ROBOT_API_ID_AUDIO_TTS);
    RegApi(ROBOT_API_ID_AUDIO_BEEP);
  }

  int32_t Tts(const std::string& text) {
    std::string data;
    return Call(ROBOT_API_ID_AUDIO_TTS, text, data);
  }

  int32_t Beep(int count = 1) {
    std::string data;
    return Call(ROBOT_API_ID_AUDIO_BEEP, std::to_string(count), data);
  }
};

}  // namespace robot
}  // namespace q1
