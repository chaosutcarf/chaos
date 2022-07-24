#pragma once

#include "common/type.h"
#include "mapping/data_filler_concepts.h"
#include "utils/logger/logger.h"

namespace chaos::mapping {
template <bool _Override = false, bool _AllowGetData = false,
          bool _Parallel = false>
struct OneDimTraits {
  static constexpr bool Override = _Override;
  static constexpr bool CanGetData = _Override && _AllowGetData;
  static constexpr bool CanParallel = _Parallel;
};

template <MATRIX_FILL_MODE _MatFillMode = MATRIX_FILL_MODE::FULL,
          bool _Override = false, bool _AllowGetData = false,
          bool _Parallel = false>
struct TwoDimTraits {
  static constexpr MATRIX_FILL_MODE MatFillMode = _MatFillMode;
  static constexpr bool Override = _Override;
  static constexpr bool CanGetData =
      _MatFillMode == MATRIX_FILL_MODE::FULL && _Override && _AllowGetData;
  static constexpr bool CanParallel = _Parallel;
};

//-> use MIXIN to do some common dim checking.
template <OneDimCoreConcept Core>
struct OneDimFiller : public Core {
  using Core::Core;
  using Core::size;
  using typename Core::Traits;

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

  template <bool mode = Traits::Override>
  inline void fill(index_t row, index_t col, real_t val);

  template <bool mode = Traits::Override, typename DerivedH>
  inline void fill(const DerivedH& H);
};
///////////////////////////////////////////////////////////////////////////////
//                          template implementation                          //
///////////////////////////////////////////////////////////////////////////////
template <OneDimCoreConcept Core>
template <bool mode>
inline void OneDimFiller<Core>::fill(index_t pos, real_t val) {
  CHAOS_DEBUG_ASSERT(pos < size(), pos, size());
  Core::template fill<mode>(pos, val);
}

template <OneDimCoreConcept Core>
template <bool mode, typename DerivedV>
inline void OneDimFiller<Core>::fill(const DerivedV& vec) {
  constexpr bool is_scalar{ArithmeticType<DerivedV>};
  constexpr bool is_unary_accessible{UnaryAccessible<DerivedV>};
  constexpr bool core_provide_fill{ProvideBatchFill<Core, DerivedV>};

  static_assert(is_scalar || is_unary_accessible,
                "vec should satisfy UnaryAccessible | ArithmeticType");

  if constexpr (is_scalar) {
    CHAOS_DEBUG_ASSERT(size() == 1, size());
    if constexpr (core_provide_fill) {
      Core::template fill<mode, DerivedV>(vec);
    } else {
      Core::template fill<mode>(0, vec);
    }
  } else {
    CHAOS_DEBUG_ASSERT(vec.size() == size(), vec.size(), size());
    if constexpr (core_provide_fill) {
      Core::template fill<mode, DerivedV>(vec);
    } else {
#define RUN()                             \
  for (index_t i = 0; i < size(); ++i) {  \
    Core::template fill<mode>(i, vec[i]); \
  }

      if constexpr (Traits::CanParallel) {
#pragma omp parallel for default(none) shared(vec)
        RUN();
      } else {
        RUN();
      }
#undef RUN
    }
  }
}

template <TwoDimCoreConcept Core>
template <bool mode>
inline void TwoDimFiller<Core>::fill(index_t r, index_t c, real_t val) {
  CHAOS_DEBUG_ASSERT(r < rows() && c < cols(), r, c, rows(), cols());
  Core::template fill<mode>(r, c, val);
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
}
}  // namespace chaos::mapping

#define FILLER_DATA_REQUIRES requires Traits::CanGetData

#define FILLER_FILL_REQUIRES \
  requires chaos::mapping::FillOverrideCheck<is_override, Traits::Override>
