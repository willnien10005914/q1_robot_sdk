#pragma once
#include <cstdint>
#include <cstring>
#include <string>
#include "channel_factory.hpp"

namespace q1 {
namespace channel {

template <typename Msg>
class ChannelPublisher {
 public:
  explicit ChannelPublisher(std::string topic) : topic_(std::move(topic)) {}

  void InitChannel() {
    ready_ = ChannelFactory::Instance()->Inited();
  }

  bool Write(const Msg* msg) {
    if (!ready_ || msg == nullptr) return false;
    last_ = *msg;
    ++seq_;
    return true;
  }

  const std::string& Topic() const { return topic_; }
  uint64_t Seq() const { return seq_; }

 private:
  std::string topic_;
  bool ready_{false};
  uint64_t seq_{0};
  Msg last_{};
};

}  // namespace channel
}  // namespace q1
