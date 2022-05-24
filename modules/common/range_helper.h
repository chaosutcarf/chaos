#pragma once

#include <initializer_list>
#include <vector>

namespace chaos::common {
template <typename Scalar, typename RangeTarget = std::vector<Scalar>,
          typename RangeRefs = std::vector<Scalar>>
constexpr void join(RangeTarget &target,
                    const std::initializer_list<RangeRefs> &list) {
  for (const auto &l : list) {
    for (const auto &item : l) {
      target.emplace_back(item);
    }
  }
}

template <typename Scalar, typename RangeTarget = std::vector<Scalar>,
          typename RangeRefs = std::vector<Scalar>>
constexpr RangeTarget join(const std::initializer_list<RangeRefs> &list) {
  RangeTarget result;
  join<Scalar, RangeTarget, RangeRefs>(result, list);
  return result;
}

}  // namespace chaos::common
