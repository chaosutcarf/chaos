#include "line.h"

#include "utils/logger/logger.h"

namespace chaos::geometry {

#define line_assert()                                                        \
  static_assert(space_dim > 0 && space_dim <= 3,                             \
                "geometry::line only support static space_dim setting, and " \
                "space_dim should be 1, 2 or 3.");

template <int space_dim>
line_t<space_dim>::line_t(real_t begin, real_t end, unsigned N, char xyz) {
  line_assert();
  CHAOS_ASSERT(N > 0, N);
  CHAOS_ASSERT(xyz >= 0 && xyz <= 2, xyz);

  m_pos.setZero(space_dim, N + 1);
  real_t dx = (end - begin) / N;
  for (size_t i = 0; i < N; ++i) {
    m_pos(xyz, i + 1) = m_pos(xyz, i) + dx;
  }
}

template <int space_dim>
line_t<space_dim>::line_t(
    const Eigen::Ref<const Eigen::Vector<real_t, space_dim>> &begin,
    const Eigen::Ref<const Eigen::Vector<real_t, space_dim>> &end, unsigned N) {
  line_assert();
  CHAOS_ASSERT(N > 0, N);

  m_pos.resize(space_dim, N + 1);
  Eigen::Vector<real_t, space_dim> dx = (end - begin) / N;
  m_pos.col(0) = begin;
  for (size_t i = 0; i < N; ++i) {
    m_pos.col(i + 1) = m_pos.col(i) + dx;
  }
}

template class line_t<1>;
template class line_t<2>;
template class line_t<3>;
}  // namespace chaos::geometry
