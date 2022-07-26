#pragma once

#include "mapping/filler.hh"

namespace chaos::mapping {
template <typename Filler>
struct OneDimWeightFillerCore {
  using Traits = OneDimTraits<Filler::Traits::Override, false,
                              Filler::Traits::CanParallel>;
  OneDimWeightFillerCore(Filler &filler, real_t w);
  inline index_t size() const { return filler.size(); }
  inline void setZero() { return filler.setZero(); }
  template <bool isOverride>
  inline void fill(index_t p, real_t val) FILLER_FILL_REQUIRES {
    filler.core().template fill<isOverride>(p, w * val);
  }
  template <bool isOverride, typename U>
  inline void fill(const U &rhs) FILLER_FILL_REQUIRES &&requires(U u) {
    { std::declval<real_t>() * u } -> ProvideBatchFill<Filler>;
  }
  { filler.template fill<isOverride>(w * rhs); }

  static auto create(Filler &filler, real_t w) {
    return OneDimFiller<OneDimWeightFillerCore<Filler>>(filler, w);
  }

 private:
  Filler &filler;
  real_t w;
};

template <typename Filler>
struct TwoDimWeightFillerCore {
  using Traits =
      TwoDimTraits<Filler::Traits::MatFillMode, Filler::Traits::Override, false,
                   Filler::Traits::CanParallel>;
  TwoDimWeightFillerCore(Filler &filler, real_t w);
  static auto create(Filler &filler, real_t w) {
    return TwoDimFiller<TwoDimWeightFillerCore<Filler>>(filler, w);
  }
  inline index_t rows() const { return filler.rows(); }
  inline index_t cols() const { return filler.cols(); }
  inline void setZero() { filler.setZero(); }
  template <bool isOverride>
  inline void fill(index_t r, index_t c, real_t val) FILLER_FILL_REQUIRES {
    filler.core().template fill<isOverride>(r, c, w * val);
  }
  template <bool isOverride, typename U>
  inline void fill(const U &rhs) FILLER_FILL_REQUIRES &&requires(U u) {
    { std::declval<real_t>() * u } -> ProvideBatchFill<Filler>;
  }
  { filler.template fill<isOverride>(w * rhs); }

 private:
  Filler &filler;
  real_t w;
};
}  // namespace chaos::mapping
