#pragma once
#include <cstdint>

namespace q1 {
namespace robot {

const int32_t Q1_OK = 0;
const int32_t Q1_ERR_TIMEOUT = 1;
const int32_t Q1_ERR_FSM_REJECT = 2;
const int32_t Q1_ERR_LEASE_HELD = 3;
const int32_t Q1_ERR_NOT_IMPLEMENTED = 100;

}  // namespace robot
}  // namespace q1
