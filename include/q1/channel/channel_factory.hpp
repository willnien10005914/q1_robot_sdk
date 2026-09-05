#pragma once
#include <memory>
#include <mutex>
#include <string>

namespace q1 {

/** DDS channel factory (CycloneDDS-backed on device; mock in Pre-SDK CI). */
class ChannelFactory {
 public:
  static ChannelFactory* Instance() {
    static ChannelFactory inst;
    return &inst;
  }

  void Init(int domain_id, const std::string& network_interface) {
    std::lock_guard<std::mutex> lock(mu_);
    domain_id_ = domain_id;
    iface_ = network_interface;
    mock_ = (network_interface == "mock" || network_interface == "lo");
    inited_ = true;
  }

  bool Inited() const { return inited_; }
  bool IsMock() const { return mock_; }
  int DomainId() const { return domain_id_; }
  const std::string& Interface() const { return iface_; }

 private:
  ChannelFactory() = default;
  std::mutex mu_;
  bool inited_{false};
  bool mock_{true};
  int domain_id_{0};
  std::string iface_{"mock"};
};

}  // namespace q1
