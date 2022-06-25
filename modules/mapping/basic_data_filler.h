#pragma once

#include <type_traits>

#include "common/type.h"
#include "mapping/data_filler.h"

namespace chaos::mapping {
#define ONE_DIM_INTERFACE(_Override, _Parallel, _GetData) \
  static constexpr bool Override = _Override;             \
  static constexpr bool CanParallel = _Parallel;          \
  static constexpr bool CanGetData = _GetData;

template <std::floating_point T, bool _Override = true, bool _GetData = true>
struct scalar_filler_t
    : public one_dim_filler_base<scalar_filler_t<T, _Override, _GetData>> {
  static constexpr bool Override = _Override;
  static constexpr bool CanGetData = _GetData;

  scalar_filler_t(T &data) : m_data(data) {}
  inline void setZero() { m_data = 0; }

  inline index_t _size() const { return 1; }
  inline void _set(index_t, real_t val) { m_data = val; }
  template <bool is_override>
  requires(Override || !is_override) inline void _fill(index_t, real_t val) {
    if constexpr (is_override && Override) {
      m_data = val;
    } else {
      m_data += val;
    }
  }

  template <bool is_override, std::floating_point U>
  inline void _batch_fill(const U &val) {
    _fill<is_override>(0, val);
  }

 private:
  T &m_data;
};

template <details::data_filler_concepts::UnaryAssignable T,
          bool _Override = true, bool _GetData = true, bool _Parallel = true>
struct one_dim_filler_t
    : public one_dim_filler_base<
          one_dim_filler_t<T, _Override, _GetData, _Parallel>> {};

}  // namespace chaos::mapping