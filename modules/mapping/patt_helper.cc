#include "patt_helper.h"

namespace chaos::mapping {

auto patt_helper::diag_patt(size_t xdim) -> patt_ptr_t {
  auto patt = std::make_unique<patt_t>();
  for (size_t i = 0; i < xdim; ++i) {
    patt->insert({i, i});
  }
  return patt;
};

auto patt_helper::self_adjoint_patt(const patt_t *patt) -> patt_ptr_t {
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
};

const patt_helper::patt_ptr_t patt_helper::empty_patt =
    std::make_unique<patt_helper::patt_t>();

}  // namespace chaos::mapping
