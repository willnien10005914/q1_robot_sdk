#pragma once
#include <functional>
#include <string>
#include "channel_factory.hpp"

namespace q1 {
namespace channel {

template <typename Msg>
class ChannelSubscriber {
 public:
  using Handler = std::function<void(const void*)>;

  explicit ChannelSubscriber(std::string topic) : topic_(std::move(topic)) {}

  void InitChannel(Handler handler) {
    handler_ = std::move(handler);
    ready_ = ChannelFactory::Instance()->Inited();
  }

  /** Pre-SDK helper: inject a mock sample into the handler. */
  void MockPush(const Msg& msg) {
    if (handler_) handler_(&msg);
  }

  const std::string& Topic() const { return topic_; }

 private:
  std::string topic_;
  bool ready_{false};
  Handler handler_;
};

}  // namespace channel
}  // namespace q1
