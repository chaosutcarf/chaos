#pragma once

#include <memory>
#include <set>

#include "common/numerical.h"
#include "common/type.h"

namespace chaos::mapping {

struct patt_helper {
  using patt_t = std::set<std::pair<index_t, index_t>>;
  using patt_ptr_t = std::unique_ptr<patt_t>;

  static const patt_ptr_t empty_patt;

  static patt_ptr_t diag_patt(index_t xdim);
  static patt_ptr_t self_adjoint_patt(const patt_t *patt);

  template <bool UpperOnly, typename Derived>
  static patt_ptr_t extract_A_patt(const Eigen::MatrixBase<Derived> &A) {
    using Index = typename Derived::Index;
    auto patt = std::make_unique<patt_t>();
    const auto insert = [&patt, &A](index_t row, index_t col) {
      if (!numerical::is_zero(A(row, col))) {
        patt->insert({row, col});
      }
    };
    for (Index i = 0; i < A.rows(); ++i) {
      Index j{0};
      if constexpr (UpperOnly) {
        j = i;
      }
      for (; j < A.cols(); ++j) {
        insert(i, j);
      }
    }
    return patt;
  }
};

}  // namespace chaos::mapping
