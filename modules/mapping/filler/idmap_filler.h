#pragma once

#include "mapping/data_filler.h"

namespace chaos::mapping {
template <data_filler_concepts::OneDimFillerConcept T,
          data_filler_concepts::UnaryAccessible IndexList>
struct idmap_1d_filler_t
    : public one_dim_filler_base<idmap_1d_filler_t<T, IndexList>> {
  idmap_1d_filler_t(T &filler, const IndexList &idmap)
      : filler(filler), idmap(idmap) {}

  inline index_t _size() const { return idmap.size(); }

  template <bool is_override>
  inline void _fill(index_t p, real_t val) {
    filler.template _fill<is_override>(idmap[p], val);
  }

 private:
  T &filler;
  const IndexList &idmap;
};

template <data_filler_concepts::TwoDimFillerConcept T,
          data_filler_concepts::UnaryAccessible IndexList>
struct idmap_2d_filler_t
    : public two_dim_filler_base<idmap_2d_filler_t<T, IndexList>> {
  idmap_2d_filler_t(T &filler, const IndexList &idmap)
      : filler(filler), idmap(idmap) {}

  inline index_t _rows() const { return idmap.size(); }
  inline index_t _cols() const { return idmap.size(); }

  template <bool is_override>
  inline void _fill(index_t r, index_t c, real_t val) {
    filler.template _fill<is_override>(idmap[r], idmap[c], val);
  }

 private:
  T &filler;
  const IndexList &idmap;
};
}  // namespace chaos::mapping
