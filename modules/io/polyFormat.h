#pragma once

#include <vector>

#include "common/type.h"
#include "utils/logger/logger.h"

namespace chaos::io {
struct polyFormat {
  template <typename Scalar>
  using Coord = std::vector<Scalar>;
  template <typename Index>
  using Face = std::vector<Index>;
  template <typename Scalar>
  using CoordList = std::vector<Coord<Scalar>>;
  template <typename Index>
  using FaceList = std::vector<Face<Index>>;
};
}  // namespace chaos::io
