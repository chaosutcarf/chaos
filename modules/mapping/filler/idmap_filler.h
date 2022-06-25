#pragma once

#include "common/type.h"
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

struct identity_mapping {
  identity_mapping(index_t m_size) : m_size(m_size) {}
  inline index_t size() const { return m_size; }
  index_t operator[](index_t x) const { return x; }

 private:
  index_t m_size;
};

template <data_filler_concepts::TwoDimFillerConcept T, typename IndexListC,
          typename IndexListR>
requires data_filler_concepts::UnaryAccessible<IndexListC, index_t> &&
    data_filler_concepts::UnaryAccessible<IndexListR, index_t>
struct idmap_2d_filler_t
    : public two_dim_filler_base<idmap_2d_filler_t<T, IndexListC, IndexListR>> {
  idmap_2d_filler_t(T &filler, const IndexListC &idmap_c)
      : filler(filler), idmap_c(idmap_c) {}

  inline index_t _rows() const { return idmap_r.size(); }
  inline index_t _cols() const { return idmap_c.size(); }

  template <bool is_override>
  inline void _fill(index_t r, index_t c, real_t val) {
    filler.template _fill<is_override>(idmap_r[r], idmap_c[c], val);
  }

 private:
  T &filler;
  const IndexListC &idmap_c;
  const IndexListR &idmap_r;
};
}  // namespace chaos::mapping
