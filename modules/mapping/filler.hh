#pragma once

#include "mapping/filler_concepts.hh"
#include "utils/logger/logger.h"

namespace chaos::mapping {

#define CHECK_OVERRIDE_FILLMODE(Override, fillmode) \
  static_assert(Override || !(fillmode),            \
                "Check Traits::Override and "       \
                "fillmode");
#define CHECK_1D_FILL(pos, Override, fillmode)   \
  CHAOS_DEBUG_ASSERT(pos < size(), pos, size()); \
  CHECK_OVERRIDE_FILLMODE(Override, fillmode);

#define CHECK_2D_FILL(r, c, Override, fillmode)                       \
  CHAOS_DEBUG_ASSERT(r < rows() && c < cols(), r, c, rows(), cols()); \
  CHECK_OVERRIDE_FILLMODE(Override, fillmode);

#define FILLER_FILL_REQUIRES requires FillOverrideCheck<isOverride, Override>
namespace details {
template <bool flag>
concept is_true = flag;
}  // namespace details

#define FILLER_DATA_REQUIRES \
  requires chaos::mapping::details::is_true<Traits::CanGetData()>
//-> fillmode: -1 use the default OverrideMode of Filler.
//->            0 means accumulate
//->            1 means override.
template <int fillmode, typename Traits>
constexpr bool Fillmode2Override() {
  if constexpr (fillmode == 0) {
    return false;
  } else if constexpr (fillmode == 1) {
    return true;
  } else {
    return Traits::Override();
  }
}

template <int fillmode = -1, OneDimFillerConcept Filler, typename U>
inline void default_1d_batch_fill(Filler &&filler, const U &rhs) {
  using Traits = FillerTraits<Filler>;
  constexpr bool isOverride{Fillmode2Override<fillmode, Traits>()};
  constexpr bool isArithmetic = ArithmeticType<U>;
  constexpr bool isVector = UnaryAccessible<U>;
  static_assert(isArithmetic || isVector,
                "U should be ArithmeticType || UnaryAccessible");

  CHECK_OVERRIDE_FILLMODE(Traits::Override(), isOverride);
  if constexpr (ProvideBatchFill<Filler, U>) {
    filler.template fill<isOverride, U>(rhs);
  } else {
    if constexpr (isArithmetic) {
      CHAOS_DEBUG_ASSERT(filler.size() == 1, filler.size());
      filler.template fill<isOverride>(0, rhs);
    } else if constexpr (isVector) {
      CHAOS_DEBUG_ASSERT(filler.size() == rhs.size(), filler.size(),
                         rhs.size());
#define RUN()                                    \
  for (index_t i = 0; i < filler.size(); ++i) {  \
    filler.template fill<isOverride>(i, rhs[i]); \
  }
      if constexpr (Traits::CanParallel()) {
#pragma omp parallel for default(none) shared(rhs, filler)
        RUN();
      } else {
        RUN();
      }
#undef RUN
    }
  }
}

template <int fillmode = -1, TwoDimFillerConcept Filler, typename U>
inline void default_2d_batch_fill(Filler &&filler, const U &rhs) {
  using Traits = FillerTraits<Filler>;
  constexpr bool isOverride{Fillmode2Override<fillmode, Traits>()};
  constexpr bool isArithmetic = ArithmeticType<U>;
  constexpr bool isMatrix = BinaryAccessible<U>;
  static_assert(isArithmetic || isMatrix,
                "U should be ArithmeticType || BinaryAccessible");

  CHECK_OVERRIDE_FILLMODE(Traits::Override(), isOverride);
  if constexpr (ProvideBatchFill<Filler, U>) {
    filler.template fill<isOverride, U>(rhs);
  } else {
    if constexpr (isArithmetic) {
      CHAOS_DEBUG_ASSERT(filler.rows() == 1 && filler.cols() == 1,
                         filler.rows(), filler.cols());
      filler.template fill<isOverride>(0, 0, rhs);
    } else if constexpr (isMatrix) {
      CHAOS_DEBUG_ASSERT(
          filler.rows() == rhs.rows() && filler.cols() == rhs.cols(),
          filler.rows(), filler.cols(), rhs.rows(), rhs.cols());
#define RUN()                                                  \
  for (index_t r = 0; r < filler.rows(); ++r) {                \
    constexpr auto MatMode = Traits::MatFillMode();            \
    index_t c = 0, end;                                        \
    if constexpr (MatMode == MATRIX_FILL_MODE::FULL) {         \
      c = 0, end = filler.cols();                              \
    } else if constexpr (MatMode == MATRIX_FILL_MODE::LOWER) { \
      c = 0, end = r + 1;                                      \
    } else if constexpr (MatMode == MATRIX_FILL_MODE::UPPER) { \
      c = r, end = filler.cols();                              \
    }                                                          \
    for (; c < end; ++c) {                                     \
      filler.template fill<isOverride>(r, c, rhs(r, c));       \
    }                                                          \
  }
      if constexpr (Traits::CanParallel()) {
#pragma omp parallel for default(none) shared(rhs, filler)
        RUN();
      } else {
        RUN();
      }
#undef RUN
    }
  }
}

}  // namespace chaos::mapping
