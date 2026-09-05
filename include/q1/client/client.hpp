#pragma once
#include <cstdint>
#include <string>
#include <unordered_map>
#include "../channel/channel_factory.hpp"

namespace q1 {
namespace robot {

/** Minimal request/response client base (Pre-SDK mockable). */
class Client {
 public:
  explicit Client(std::string service_name, bool lease = false)
      : service_name_(std::move(service_name)), lease_(lease) {}
  virtual ~Client() = default;

  void SetApiVersion(std::string v) { api_version_ = std::move(v); }
  void SetTimeout(float seconds) { timeout_s_ = seconds; }
  const std::string& ServiceName() const { return service_name_; }

 protected:
  void RegApi(int32_t api_id) { registry_[api_id] = true; }

  int32_t Call(int32_t api_id, const std::string& parameter, std::string& data) {
    if (!ChannelFactory::Instance()->Inited()) return -1;
    if (!registry_.count(api_id)) return -2;
    last_api_ = api_id;
    last_parameter_ = parameter;
    if (ChannelFactory::Instance()->IsMock()) {
      data = parameter.empty() ? std::string("{\"data\":0}") : parameter;
      return 0;
    }
    data.clear();
    return -100;  // NOT_IMPLEMENTED until firmware bridge
  }

  int32_t LastApi() const { return last_api_; }

 private:
  std::string service_name_;
  std::string api_version_{"1.0.0.0"};
  bool lease_{false};
  float timeout_s_{5.f};
  std::unordered_map<int32_t, bool> registry_;
  int32_t last_api_{0};
  std::string last_parameter_;
};

}  // namespace robot
}  // namespace q1
