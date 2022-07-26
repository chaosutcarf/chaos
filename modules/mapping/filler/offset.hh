#pragma once

#include "mapping/filler.hh"
#include "mapping/filler_concept.hh"

namespace chaos::mapping {
template <typename Filler>
struct OneDimOffsetFillerCore {
  using Traits = OneDimTraits<Filler::Traits::Override, false,
                              Filler::Traits::CanParallel>;
  OneDimOffsetFillerCore(Filler &filler, index_t offset);
  static auto create(Filler &filler, index_t offset) {
    return OneDimFiller<OneDimOffsetFillerCore<Filler>>(filler, offset);
  }
  inline index_t size() const { return filler.size() - offset; }
  inline void setZero() { filler.setZero(); }
  template <bool isOverride>
  inline void fill(index_t p, real_t val) FILLER_FILL_REQUIRES {
    filler.core().template fill<isOverride>(p + offset, val);
  }

 private:
  Filler &filler;
  index_t offset;
};
template <typename Filler>
struct TwoDimOffsetFillerCore {
  using Traits =
      TwoDimTraits<Filler::Traits::MatFillMode, Filler::Traits::Override, false,
                   Filler::Traits::CanParallel>;
  TwoDimOffsetFillerCore(Filler &filler, index_t off_r, index_t off_c);
  static auto create(Filler &filler, index_t off_r, index_t off_c) {
    return TwoDimFiller<TwoDimOffsetFillerCore<Filler>>(filler, off_r, off_c);
  }
  inline index_t rows() const { return filler.rows() - off_r; }
  inline index_t cols() const { return filler.cols() - off_c; }
  inline void setZero() { filler.setZero(); }
  template <bool isOverride>
  inline void fill(index_t r, index_t c, real_t val) FILLER_FILL_REQUIRES {
    filler.core().template fill<isOverride>(r + off_r, c + off_c, val);
  }

 private:
  Filler &filler;
  index_t off_r, off_c;
};
}  // namespace chaos::mapping
