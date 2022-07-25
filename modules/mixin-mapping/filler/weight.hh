#pragma once

#include "common/type.h"
#include "mapping/data_filler.h"

namespace chaos::mapping {
template <typename FillerCore>
struct OneDimWeightFillerCore {
  using Traits = OneDimTraits<FillerCore::Traits::Override, false,
                              FillerCore::Traits::CanParallel>;
  OneDimWeightFillerCore(FillerCore &filler, real_t w) : filler(filler), w(w) {}
  inline index_t size() const { return filler.size(); }
  inline void setZero() { return filler.setZero(); }
  template <bool isOverride>
  inline void fill(index_t p, real_t val) FILLER_FILL_REQUIRES {
    filler.template fill<isOverride>(p, w * val);
  }
  template <bool isOverride, typename U>
  inline void fill(const U &rhs) FILLER_FILL_REQUIRES &&requires(U u) {
    { std::declval<real_t>() * u } -> ProvideBatchFill<FillerCore>;
  }
  { filler.template fill<isOverride>(w * rhs); }

 private:
  using FillerCore::fill;
  FillerCore &filler;
  real_t w;
};
template <typename FillerCore>
auto OneDimWeightFiller(FillerCore &filler, real_t w) {
  return OneDimFiller<OneDimWeightFillerCore<FillerCore>>(filler, w);
}

}  // namespace chaos::mapping
