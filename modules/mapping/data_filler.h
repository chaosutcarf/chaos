#pragma once

#include "common/pattern.h"
#include "common/type.h"
#include "mapping/data_filler_concepts.h"
#include "utils/logger/logger.h"

namespace chaos::mapping {
//-> use CRTP to do some common dim checking.
template <data_filler_concepts::OneDimFillerConcept Derived>
struct one_dim_filler_base {
  CRTP_derived_interface(Derived, one_dim_filler_base);

  inline index_t size() const { return derived()._size(); }

  template <bool override_mode = true>
  requires data_filler_concepts::FillOverrideCheck<override_mode, Derived>
  inline void fill(index_t pos, real_t val) {
    CHAOS_DEBUG_ASSERT(pos < size(), pos, size());
    constexpr bool is_override =
        override_mode && data_filler_concepts::IsOverride<Derived>;
    derived().template _fill<is_override>(pos, val);
  }

  template <bool override_mode = true, typename DerivedV>
  requires data_filler_concepts::FillOverrideCheck<override_mode, Derived>
  inline void batch_fill(const DerivedV &vec) {
    constexpr bool is_floating_point{std::floating_point<DerivedV>};
    constexpr bool is_unary_accessible{
        data_filler_concepts::UnaryAccessible<DerivedV>};
    constexpr bool is_override =
        override_mode && data_filler_concepts::IsOverride<Derived>;
    constexpr bool has_batch_fill{
        data_filler_concepts::ProvideBatchFill<Derived, DerivedV>};
    constexpr bool can_parallel{data_filler_concepts::CanParallel<Derived>};

    static_assert(is_floating_point || is_unary_accessible,
                  "vec should satisfy UnaryAccessible | floating_point");

    if constexpr (is_floating_point) {
      CHAOS_DEBUG_ASSERT(size() == 1, size());
      if constexpr (has_batch_fill) {
        derived().template _batch_fill<is_override, DerivedV>(vec);
      } else {
        derived().template _fill<is_override>(0, vec);
      }
    } else {
      CHAOS_DEBUG_ASSERT(vec.size() == size(), vec.size(), size());
      if constexpr (has_batch_fill) {
        derived().template _batch_fill<is_override, DerivedV>(vec);
      } else {
#define RUN()                                         \
  for (index_t i = 0; i < size(); ++i) {              \
    derived().template _fill<is_override>(i, vec[i]); \
  }

        if constexpr (can_parallel) {
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
template <data_filler_concepts::TwoDimFillerConcept Derived>
struct two_dim_filler_base {
  CRTP_derived_interface(Derived, two_dim_filler_base);

  inline index_t rows() const { return derived()._rows(); }
  inline index_t cols() const { return derived()._cols(); }

  template <bool override_mode = true>
  requires data_filler_concepts::FillOverrideCheck<override_mode, Derived>
  inline void fill(index_t r, index_t c, real_t val) {
    CHAOS_DEBUG_ASSERT(r < rows() && c < cols(), r, c, rows(), cols());

    constexpr bool is_override =
        override_mode && data_filler_concepts::IsOverride<Derived>;

    derived().template _fill<is_override>(r, c, val);
  }

  template <bool override_mode = true,
            data_filler_concepts::BinaryAccessible DerivedH>
  requires data_filler_concepts::FillOverrideCheck<override_mode, Derived>
  inline void batch_fill(const DerivedH &H) {
    constexpr bool is_override =
        override_mode && data_filler_concepts::IsOverride<Derived>;

#define RUN()                                                            \
  for (index_t r = 0; r < rows(); ++r) {                                 \
    index_t c, end;                                                      \
    if constexpr (data_filler_concepts::FullFillMode<Derived>) {         \
      c = 0, end = cols();                                               \
    } else if constexpr (data_filler_concepts::LowerFillMode<Derived>) { \
      c = 0, end = r + 1;                                                \
    } else {                                                             \
      c = r, end = cols();                                               \
    }                                                                    \
    for (; c < end; ++c) {                                               \
      derived().template _fill<is_override>(r, c, H(r, c));              \
    }                                                                    \
  }

    CHAOS_DEBUG_ASSERT(H.rows() == rows(), H.cols() == cols(), H.rows(),
                       H.cols(), rows(), cols());
    if constexpr (data_filler_concepts::ProvideBatchFill<Derived, DerivedH>) {
      derived().template _batch_fill<is_override, DerivedH>(H);
    } else {
      //-> default batch fill.
      if constexpr (data_filler_concepts::CanParallel<Derived>) {
#pragma omp parallel for default(none) shared(H)
        RUN();
      } else {
        RUN();
      }
    }
#undef RUN
  }
};

#define ONE_DIM_INTERFACE(_Override, _Parallel, _GetData) \
  static constexpr bool Override = _Override;             \
  static constexpr bool CanParallel = _Parallel;          \
  static constexpr bool CanGetData = _GetData;

#define TWO_DIM_INTERFACE(_Override, _Parallel, _FillMode, _GetData) \
  static constexpr bool Override = _Override;                        \
  static constexpr bool CanParallel = _Parallel;                     \
  static constexpr MATRIX_FILL_MODE FillMode = _FillMode;            \
  static constexpr bool CanGetData =                                 \
      _Override && _FillMode == MATRIX_FILL_MODE::FULL && _GetData;
}  // namespace chaos::mapping
