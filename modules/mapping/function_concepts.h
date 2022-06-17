#pragma once

#include <concepts>

#include "common/type.h"

namespace chaos::mapping {

template <typename T>
concept FunctionLike = requires(T a) {
  a + a;
};

}  // namespace chaos::mapping
