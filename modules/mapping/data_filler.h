#pragma once

#include "common/pattern.h"
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

//-> use CRTP to do some common dim checking.
template <typename Derived,
          data_filler_concepts::OneDimTraitsConcept _Traits = OneDimTraits<>>
struct one_dim_filler_base {
  using Traits = _Traits;
  one_dim_filler_base() {
    //-> since Derived is a incomplete type, so check it here.
    static_assert(data_filler_concepts::OneDimFillerConcept<Derived>,
                  "Check OneDimFillerConcept.");
  }

  CRTP_derived_interface(Derived, one_dim_filler_base);

  inline index_t size() const { return derived()._size(); }

  template <bool mode = Traits::Override>
  requires data_filler_concepts::FillOverrideCheck<mode, Traits::Override>
  inline void fill(index_t pos, real_t val) {
    CHAOS_DEBUG_ASSERT(pos < size(), pos, size());
    derived().template _fill<mode>(pos, val);
  }

  template <bool mode = Traits::Override, typename DerivedV>
  requires data_filler_concepts::FillOverrideCheck<mode, Traits::Override>
  inline void fill(const DerivedV &vec) {
    constexpr bool is_scalar{data_filler_concepts::ArithmeticType<DerivedV>};
    constexpr bool is_unary_accessible{
        data_filler_concepts::UnaryAccessible<DerivedV>};
    constexpr bool has_batch_fill{
        data_filler_concepts::ProvideBatchFill<Derived, DerivedV>};

    static_assert(is_scalar || is_unary_accessible,
                  "vec should satisfy UnaryAccessible | ArithmeticType");

    if constexpr (is_scalar) {
      CHAOS_DEBUG_ASSERT(size() == 1, size());
      if constexpr (has_batch_fill) {
        derived().template _fill<mode, DerivedV>(vec);
      } else {
        derived().template _fill<mode>(0, vec);
      }
    } else {
      CHAOS_DEBUG_ASSERT(vec.size() == size(), vec.size(), size());
      if constexpr (has_batch_fill) {
        derived().template _fill<mode, DerivedV>(vec);
      } else {
#define RUN()                                  \
  for (index_t i = 0; i < size(); ++i) {       \
    derived().template _fill<mode>(i, vec[i]); \
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
};

//-> use CRTP to do some common dim checking.
template <typename Derived,
          data_filler_concepts::TwoDimTraitsConcept _Traits = TwoDimTraits<>>
struct two_dim_filler_base {
  using Traits = _Traits;
  two_dim_filler_base() {
    //-> since Derived is an incomplete type, so check here.
    static_assert(data_filler_concepts::TwoDimFillerConcept<Derived>,
                  "Check TwoDimFillerConcept.");
  }

  CRTP_derived_interface(Derived, two_dim_filler_base);

  inline index_t rows() const { return derived()._rows(); }
  inline index_t cols() const { return derived()._cols(); }

  template <bool mode = Traits::Override>
  requires data_filler_concepts::FillOverrideCheck<mode, Traits::Override>
  inline void fill(index_t r, index_t c, real_t val) {
    CHAOS_DEBUG_ASSERT(r < rows() && c < cols(), r, c, rows(), cols());
    derived().template _fill<mode>(r, c, val);
  }

  template <bool mode = Traits::Override,
            data_filler_concepts::BinaryAccessible DerivedH>
  requires data_filler_concepts::FillOverrideCheck<mode, Traits::Override>
  inline void fill(const DerivedH &H) {
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
      derived().template _fill<mode>(r, c, H(r, c));                       \
    }                                                                      \
  }

    CHAOS_DEBUG_ASSERT(H.rows() == rows(), H.cols() == cols(), H.rows(),
                       H.cols(), rows(), cols());
    if constexpr (data_filler_concepts::ProvideBatchFill<Derived, DerivedH>) {
      derived().template _fill<mode, DerivedH>(H);
    } else {
      //-> default batch fill.
      if constexpr (Traits::CanParallel) {
#pragma omp parallel for default(none) shared(H)
        RUN();
      } else {
        RUN();
      }
    }
#undef RUN
  }
};

#define FILLER_DATA_REQUIRES requires Traits::CanGetData

#define FILLER_FILL_REQUIRES                                        \
  requires chaos::mapping::data_filler_concepts::FillOverrideCheck< \
      is_override, Traits::Override>

}  // namespace chaos::mapping
