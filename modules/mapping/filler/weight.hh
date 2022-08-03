#pragma once

#include <type_traits>

#include "mapping/filler.hh"

namespace chaos::mapping {

template <typename Filler>
struct WeightFillerCore {
  using Traits = std::conditional_t<
      TwoDimCoreConcept<Filler>,
      TwoDimTraits<Filler::Traits::MatFillMode, Filler::Traits::Override, false,
                   Filler::Traits::CanParallel>,
      OneDimTraits<Filler::Traits::Override, false,
                   Filler::Traits::CanParallel>>;
  WeightFillerCore(Filler &filler, real_t w) : filler(filler), w(w) {}

  inline index_t rows() const requires HasFunctionRows<Filler> {
    return filler.rows();
  }
  inline index_t cols() const requires HasFunctionCols<Filler> {
    return filler.cols();
  }
  inline index_t size() const requires HasFunctionSize<Filler> {
    return filler.size();
  }
  inline void setZero() { filler.setZero(); }
  template <bool isOverride>
  inline void _fill(index_t r, index_t c,
                    real_t val) FILLER_FILL_REQUIRES &&HasFunctionRows<Filler> {
    filler.template _fill<isOverride>(r, c, w * val);
  }
  template <bool isOverride>
  inline void _fill(index_t p,
                    real_t val) FILLER_FILL_REQUIRES &&HasFunctionSize<Filler> {
    filler.template _fill<isOverride>(p, w * val);
  }
  template <bool isOverride, typename U>
  inline void _fill(const U &rhs) FILLER_FILL_REQUIRES &&requires(U u) {
    { std::declval<real_t>() * u } -> ProvideBatchFill<Filler>;
  }
  { filler.template _fill<isOverride>(w * rhs); }

 private:
  Filler &filler;
  real_t w;
};

template <typename Filler>
inline auto WeightFiller(Filler &filler, real_t w) {
  if constexpr (OneDimCoreConcept<Filler>) {
    return OneDimFiller<WeightFillerCore<Filler>>(filler, w);
  } else {
    return TwoDimFiller<WeightFillerCore<Filler>>(filler, w);
  }
}
}  // namespace chaos::mapping
