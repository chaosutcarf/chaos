#include "patt_helper.h"

namespace chaos::mapping {
auto PattHelper::diag_patt(index_t dim) -> patt_ptr_t {
  auto patt = std::make_unique<patt_t>();
  for (index_t i = 0; i < dim; ++i) {
    patt->insert({i, i});
  }
  return patt;
}

auto PattHelper::self_adjoint_patt(const patt_t *patt) -> patt_ptr_t {
  if (patt == nullptr) {
    return nullptr;
  }
  auto full_patt = std::make_unique<patt_t>();
  for (const auto &oo : *patt) {
    full_patt->insert({oo.first, oo.second});
    if (oo.first != oo.second) {
      full_patt->insert({oo.second, oo.first});
    }
  }
  return full_patt;
}

const PattHelper::patt_ptr_t PattHelper::empty_patt =
    std::make_unique<patt_t>();
}  // namespace chaos::mapping
