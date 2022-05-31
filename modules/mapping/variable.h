#pragma once

#include <tuple>

#include "common/type.h"
#include "utils/logger/logger.h"

namespace chaos::mapping {

namespace variable {
template <typename... Args>
struct At {
  std::tuple<Args...> args;
};

template <typename... Args>
auto at(Args&&... args) {
  return At<Args&&...>{std::forward_as_tuple(std::forward<Args>(args)...)};
}
}  // namespace variable

}  // namespace chaos::mapping
