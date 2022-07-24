#pragma once

#include <set>

#include "common/type.h"
#include "mapping/data_filler.h"
#include "utils/logger/logger.h"
namespace chaos::mapping {

#ifndef NDEBUG
#define IDMAP_CHECK()                         \
  std::set<index_t> idset;                    \
  index_t _max = 0;                           \
  for (size_t i = 0; i < idmap.size(); ++i) { \
    if (idmap[i] < _max) {                    \
      _max = idmap[i];                        \
    }                                         \
    idset.insert(idmap[i]);                   \
  }                                           \
  CHAOS_DEBUG_ASSERT(idset.size() == idmap.size());
#else
#define IDMAP_CHECK()
#endif

template <data_filler_concepts::OneDimFillerConcept T,
          data_filler_concepts::UnaryAccessible IndexList>
struct idmap_1d_filler_t
    : public one_dim_filler_base<
          idmap_1d_filler_t<T, IndexList>,
          OneDimTraits<T::Traits::Override, false, T::Traits::CanParallel>> {
  using Base = one_dim_filler_base<
      idmap_1d_filler_t<T, IndexList>,
      OneDimTraits<T::Traits::Override, false, T::Traits::CanParallel>>;
  using typename Base::Traits;

  idmap_1d_filler_t(T &filler, const IndexList &idmap)
      : filler(filler), idmap(idmap) {
    IDMAP_CHECK();
#ifndef NDEBUG
    CHAOS_DEBUG_ASSERT(_max < filler.size(), _max, filler.size());
#endif
  }

  inline index_t _size() const { return idmap.size(); }

  template <bool is_override>
  inline void _fill(index_t p, real_t val) FILLER_FILL_REQUIRES {
    filler.template _fill<is_override>(idmap[p], val);
  }

 private:
  T &filler;
  const IndexList &idmap;
};

template <data_filler_concepts::TwoDimFillerConcept T, typename IndexList,
          bool BothMap = true>
requires data_filler_concepts::UnaryAccessible<IndexList, index_t>
struct idmap_2d_filler_t
    : public two_dim_filler_base<
          idmap_2d_filler_t<T, IndexList, BothMap>,
          TwoDimTraits<T::Traits::MatFillMode, T::Traits::Override, false,
                       T::Traits::CanParallel>> {
  using Base = two_dim_filler_base<
      idmap_2d_filler_t<T, IndexList, BothMap>,
      TwoDimTraits<T::Traits::MatFillMode, T::Traits::Override, false,
                   T::Traits::CanParallel>>;
  using typename Base::Traits;

  idmap_2d_filler_t(T &filler, const IndexList &idmap)
      : filler(filler), idmap(idmap) {
    IDMAP_CHECK();
#ifndef NDEBUG
    CHAOS_DEBUG_ASSERT(_max < filler.rows() && _max < filler.cols(), _max,
                       filler.cols(), filler.rows());
#endif
  }

  inline index_t _rows() const {
    if constexpr (BothMap) {
      return idmap.size();
    } else {
      return filler._rows();
    }
  }
  inline index_t _cols() const { return idmap.size(); }

  template <bool is_override>
  inline void _fill(index_t r, index_t c, real_t val) FILLER_FILL_REQUIRES {
    if constexpr (BothMap) {
      filler.template _fill<is_override>(idmap[r], idmap[c], val);
    } else {
      filler.template _fill<is_override>(r, idmap[c], val);
    }
  }

 private:
  T &filler;
  const IndexList &idmap;
};

#undef IDMAP_CHECK
}  // namespace chaos::mapping
