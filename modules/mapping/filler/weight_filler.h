#pragma once

#include "common/type.h"
#include "mapping/data_filler.h"

namespace chaos::mapping {

template <data_filler_concepts::OneDimFillerConcept T>
struct weight_1d_filler_t : public one_dim_filler_base<weight_1d_filler_t<T>> {
  weight_1d_filler_t(T& filler, real_t w) : filler(filler), w(w) {}

  inline index_t _size() const { return filler._size(); }

  template <bool is_override>
  inline void _fill(index_t p, real_t val) {
    filler.template _fill<is_override>(p, w * val);
  }

 private:
  T& filler;
  real_t w;
};

template <data_filler_concepts::TwoDimFillerConcept T>
struct weight_2d_filler_t : public two_dim_filler_base<weight_2d_filler_t<T>> {
  weight_2d_filler_t(T& filler, real_t w) : filler(filler), w(w) {}

  inline index_t _rows() const { return filler._rows(); }
  inline index_t _cols() const { return filler._cols(); }

  template <bool is_override>
  inline void _fill(index_t r, index_t c, real_t val) {
    filler.template _fill<is_override>(r, c, val * w);
  }

 private:
  T& filler;
  real_t w;
};
}  // namespace chaos::mapping
