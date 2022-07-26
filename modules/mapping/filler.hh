#pragma once

#include "common/pattern.h"
#include "mapping/filler_concept.hh"
#include "utils/logger/logger.h"

namespace chaos::mapping {
//-> use MIXIN to do some common dim checking.
template <OneDimCoreConcept Core>
struct OneDimFiller : public Core {
  using Core::Core;
  using Core::size;
  using typename Core::Traits;

  MIXIN_core_interface(Core);

  template <bool mode = Traits::Override>
  inline void fill(index_t pos, real_t val);

  template <bool mode = Traits::Override, typename DerivedV>
  inline void fill(const DerivedV& vec);
};

template <TwoDimCoreConcept Core>
struct TwoDimFiller : public Core {
  using Core::cols;
  using Core::Core;
  using Core::rows;
  using typename Core::Traits;

  MIXIN_core_interface(Core);

  template <bool mode = Traits::Override>
  inline void fill(index_t row, index_t col, real_t val);

  template <bool mode = Traits::Override, typename DerivedH>
  inline void fill(const DerivedH& H);
};
#define CHECK_OVERRIDE_FILLMODE() \
  static_assert(Traits::Override || !mode, "Check override mode");
#define FILLER_FILL_REQUIRES \
  requires chaos::mapping::FillOverrideCheck<isOverride, Traits::Override>
#define FILLER_DATA_REQUIRES requires Traits::CanGetData
//////////////////////////////////////////////////////////////////////////////
//                          template implementation                          //
///////////////////////////////////////////////////////////////////////////////
template <OneDimCoreConcept Core>
template <bool mode>
inline void OneDimFiller<Core>::fill(index_t pos, real_t val) {
  CHAOS_DEBUG_ASSERT(pos < size(), pos, size());
  Core::template fill<mode>(pos, val);
}
template <TwoDimCoreConcept Core>
template <bool mode>
inline void TwoDimFiller<Core>::fill(index_t r, index_t c, real_t val) {
  CHAOS_DEBUG_ASSERT(r < rows() && c < cols(), r, c, rows(), cols());
  Core::template fill<mode>(r, c, val);
}

template <OneDimCoreConcept Core>
template <bool mode, typename U>
inline void OneDimFiller<Core>::fill(const U& rhs) {
  constexpr bool is_scalar{ArithmeticType<U>};
  constexpr bool is_unary_accessible{UnaryAccessible<U>};
  constexpr bool core_provide_fill{ProvideBatchFill<Core, U>};

  if constexpr (is_scalar) {
    CHAOS_DEBUG_ASSERT(size() == 1, size());
    if constexpr (core_provide_fill) {
      Core::template fill<mode, U>(rhs);
    } else {
      Core::template fill<mode>(0, rhs);
    }
  } else {
    CHAOS_DEBUG_ASSERT(rhs.size() == size(), rhs.size(), size());
    if constexpr (core_provide_fill) {
      Core::template fill<mode, U>(rhs);
    } else {
#define RUN()                             \
  for (index_t i = 0; i < size(); ++i) {  \
    Core::template fill<mode>(i, rhs[i]); \
  }
      if constexpr (Traits::CanParallel) {
#pragma omp parallel for default(none) shared(rhs)
        RUN();
      } else {
        RUN();
      }
#undef RUN
    }
  }
}

template <TwoDimCoreConcept Core>
template <bool mode, typename DerivedH>
inline void TwoDimFiller<Core>::fill(const DerivedH& H) {
  constexpr bool core_provide_fill{ProvideBatchFill<Core, DerivedH>};
  CHAOS_DEBUG_ASSERT(H.rows() == rows() && H.cols() == cols(), H.rows(), rows(),
                     H.cols(), cols());
  if constexpr (core_provide_fill) {
    Core::template fill<mode, DerivedH>(H);
  } else {
    //-> default batch fill.
#define RUN()                                                              \
  for (index_t r = 0; r < rows(); ++r) {                                   \
    index_t c, end;                                                        \
    if constexpr (Traits::MatFillMode == MATRIX_FILL_MODE::FULL) {         \
      c = 0, end = cols();                                                 \
    } else if constexpr (Traits::MatFillMode == MATRIX_FILL_MODE::LOWER) { \
      c = 0, end = r + 1;                                                  \
    } else {                                                               \
      c = r, end = cols();                                                 \
    }                                                                      \
    for (; c < end; ++c) {                                                 \
      Core::template fill<mode>(r, c, H(r, c));                            \
    }                                                                      \
  }

    if constexpr (Traits::CanParallel) {
#pragma omp parallel for default(none) shared(H)
      RUN();
    } else {
      RUN();
    }
  }
#undef RUN
}

}  // namespace chaos::mapping
