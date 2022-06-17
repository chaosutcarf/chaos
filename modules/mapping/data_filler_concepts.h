#pragma once

#include <type_traits>

#include "common/type.h"
#include "common/type_traits.h"

namespace chaos::mapping::details {

template <typename T>
concept OneDimFillerConcept = requires{
  true;
};

template <typename T>
concept TwoDimFillerConcept = requires{
  true;
};

}  // namespace chaos::mapping::details
