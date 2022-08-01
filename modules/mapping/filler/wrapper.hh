#pragma once

#include "mapping/filler_concepts.hh"
#include "utils/logger/logger.h"
namespace chaos::mapping {
#define CONSTEXPR_VAR(name) static constexpr decltype(_##name) name{_##name};
//-> scalar wrapper.
template <ArithmeticType T, bool _Override = true>
struct ScalarFiller {
  CONSTEXPR_VAR(Override);

  ScalarFiller(T &data) : m_data(data) {}
  static constexpr index_t size() { return 1; }
  static constexpr index_t rows() { return 1; }
  static constexpr index_t cols() { return 1; }
  inline void setZero() { m_data = 0; }

  template <bool isOverride = Override>
  inline void fill(index_t p, real_t val) {
    CHAOS_DEBUG_ASSERT(p == 0, p);
    fill<isOverride>(val);
  }
  template <bool isOverride = Override>
  inline void fill(index_t r, index_t c, real_t val) {
    CHAOS_DEBUG_ASSERT(r == 0 && c == 0, r, c);
    fill<isOverride>(val);
  }
  template <bool isOverride = Override>
  inline void fill(real_t val) {
    if constexpr (isOverride) {
      m_data = val;
    } else {
      m_data += val;
    }
  }

 private:
  T &m_data;
};

//-> Eigen::Vector Wrapper
template <typename T, bool _Override = true>
struct VectorFiller {
  CONSTEXPR_VAR(Override);

  VectorFiller(T &data) : m_data(data) {}
  inline void setZero() { m_data.setZero(); }

  inline index_t size() const { return m_data.size(); }
  template <bool isOverride>
  inline void fill(index_t p, real_t val) {
    CHAOS_DEBUG_ASSERT(p < size(), p, size());
    if constexpr (isOverride) {
      m_data[p] = val;
    } else {
      m_data[p] += val;
    }
  }

  //-> TODO. check typeU.
  template <bool isOverride, typename U>
  inline void fill(const U &rhs) {
    if constexpr (isOverride) {
      m_data = rhs;
    } else {
      m_data += rhs;
    }
  }

 private:
  T &m_data;
};

//-> Eigen::Matrix Wrapper.
template <typename T, MATRIX_FILL_MODE _MatFillMode = MATRIX_FILL_MODE::FULL,
          bool _Override = true, bool _AllowGetData = true>
struct MatrixFiller {
  CONSTEXPR_VAR(MatFillMode);
  CONSTEXPR_VAR(Override);
  MatrixFiller(T &data) : m_data(data) {}

  inline void setZero() { m_data.setZero(); }
  inline index_t rows() const { return m_data.rows(); }
  inline index_t cols() const { return m_data.cols(); }

  template <bool isOverride>
  inline void fill(index_t r, index_t c, real_t val) {
    CHAOS_DEBUG_ASSERT(r < rows() && c < cols(), rows(), cols());
    if constexpr (isOverride) {
      m_data(r, c) = val;
    } else {
      m_data(r, c) += val;
    }
  }

  template <bool isOverride, typename U>
  inline void fill(const U &rhs) {
    if constexpr (isOverride) {
      m_data = rhs;
    } else {
      m_data += rhs;
    }
  }

 private:
  T &m_data;
};
}  // namespace chaos::mapping
