#pragma once

#include "common/type.h"

namespace chaos::geometry {

/*
 * current only support static 1d, 2d, 3d.
 */
template <int space_dim>
struct line_t {
  line_t(real_t begin, real_t end, unsigned num_of_segs, char xyz = 0);
  line_t(const Eigen::Ref<const Eigen::Vector<real_t, space_dim>> &begin,
         const Eigen::Ref<const Eigen::Vector<real_t, space_dim>> &end,
         unsigned num_of_segments);

  Eigen::Matrix<real_t, space_dim, -1> &pos() { return m_pos; }
  const Eigen::Matrix<real_t, space_dim, -1> &pos() const { return m_pos; }

 private:
  Eigen::Matrix<real_t, space_dim, -1> m_pos;
};

}  // namespace chaos::geometry
