#pragma once

#include "common/type.h"
#include "mapping/data_filler.h"
#include "utils/logger/logger.h"

namespace chaos::mapping {
template <data_filler_concepts::OneDimFillerConcept T>
struct offset_1d_filler_t : public one_dim_filler_base<offset_1d_filler_t<T>> {
  ONE_DIM_INTERFACE(data_filler_concepts::IsOverride<T>,
                    data_filler_concepts::CanParallel<T>, false);
  offset_1d_filler_t(T& filler, index_t offset)
      : filler(filler), offset(offset) {
    CHAOS_DEBUG_ASSERT(offset < filler._size(), offset, filler._size());
  }

  inline index_t _size() const { return filler._size() - offset; }

  template <bool is_override>
  void _fill(index_t p, real_t val) {
    filler.template _fill<is_override>(p + offset, val);
  }

 private:
  T& filler;
  index_t offset;
};

template <data_filler_concepts::TwoDimFillerConcept T>
struct offset_2d_filler_t : public two_dim_filler_base<offset_2d_filler_t<T>> {
  TWO_DIM_INTERFACE(data_filler_concepts::IsOverride<T>,
                    data_filler_concepts::CanParallel<T>,
                    data_filler_concepts::MatFillMode<T>(), false);
  offset_2d_filler_t(T& filler, index_t off_r, index_t off_c)
      : filler(filler), off_r(off_r), off_c(off_c) {
    CHAOS_DEBUG_ASSERT(off_r < filler._rows() && off_c < filler._cols(), off_r,
                       off_c, filler._rows(), filler._cols());
  }

  inline index_t _rows() const { return filler._rows() - off_r; }
  inline index_t _cols() const { return filler._cols() - off_c; }

  template <bool is_override>
  inline void _fill(index_t r, index_t c, real_t val) {
    filler.template _fill<is_override>(r + off_r, c + off_c, val);
  }

 private:
  T& filler;
  index_t off_r, off_c;
};
}  // namespace chaos::mapping
