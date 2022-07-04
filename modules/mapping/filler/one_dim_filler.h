#pragma once

#include <type_traits>

#include "common/type.h"
#include "mapping/data_filler.h"

namespace chaos::mapping {
template <data_filler_concepts::ArithmeticType T, bool _Override = true,
          bool _AllowGetData = true>
struct scalar_filler_t
    : public one_dim_filler_base<scalar_filler_t<T, _Override, _AllowGetData>,
                                 OneDimTraits<_Override, _AllowGetData>> {
  using Base = one_dim_filler_base<scalar_filler_t<T, _Override, _AllowGetData>,
                                   OneDimTraits<_Override, _AllowGetData>>;
  using typename Base::Traits;

  scalar_filler_t(T &data) : m_data(data) {}
  inline void setZero() { m_data = 0; }

  inline real_t *data() FILLER_DATA_REQUIRES { return &m_data; }

  inline index_t _size() const { return 1; }

  template <bool is_override>
  inline void _fill(index_t, real_t val) FILLER_FILL_REQUIRES {
    _batch_fill<is_override>(val);
  }

  template <bool is_override, data_filler_concepts::ArithmeticType U>
  inline void _batch_fill(const U &val) FILLER_FILL_REQUIRES {
    if constexpr (is_override) {
      m_data = val;
    } else {
      m_data += val;
    }
  }

 private:
  T &m_data;
};

template <data_filler_concepts::UnaryAssignable T, bool _Override = true,
          bool _AllowGetData = true, bool _Parallel = true>
struct one_dim_filler_t
    : public one_dim_filler_base<
          one_dim_filler_t<T, _Override, _AllowGetData, _Parallel>,
          OneDimTraits<_Override, _AllowGetData, _Parallel>> {
  using Base = one_dim_filler_base<
      one_dim_filler_t<T, _Override, _AllowGetData, _Parallel>,
      OneDimTraits<_Override, _AllowGetData, _Parallel>>;
  using typename Base::Traits;
  one_dim_filler_t(T &data) : m_data(data) {}
  inline void setZero() { m_data.setZero(); }

  inline real_t *data() FILLER_DATA_REQUIRES { return m_data.data(); }

  inline index_t _size() const { return m_data.size(); }

  template <bool is_override>
  inline void _fill(index_t p, real_t val) FILLER_FILL_REQUIRES {
    if constexpr (is_override) {
      m_data[p] = val;
    } else {
      m_data[p] += val;
    }
  }

  template <bool is_override, data_filler_concepts::UnaryAccessible DerivedV>
  inline void _batch_fill(const DerivedV &val) FILLER_FILL_REQUIRES {
    if constexpr (is_override) {
      m_data = val;
    } else {
      m_data += val;
    }
  }

 private:
  T &m_data;
};

}  // namespace chaos::mapping
