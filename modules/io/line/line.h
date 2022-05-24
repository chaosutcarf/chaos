#pragma once

#include "common/type_helper.h"
#include "io/vtk.h"

namespace chaos::io::line {
void save_line(const std::string &filename, const Eigen::Ref<const matxr_t> &x);
void save_line_frame(const std::string &filename,
                     const Eigen::Ref<const mat3xr_t> &pos,
                     const Eigen::Ref<const mat4xr_t> &qtn);
//-> index is the number idx of each patch.
void save_patch_line(const std::string &filename,
                     const Eigen::Ref<const matxr_t> &x,
                     const std::vector<std::vector<int>> &indexes);
//-> N is the number of nodes of each patch.
void save_patch_line(const std::string &filename,
                     const Eigen::Ref<const matxr_t> &x, int N);
//-> patches contains the number of nodes of each patch.
void save_patch_line(const std::string &filename,
                     const Eigen::Ref<const matxr_t> &x,
                     const std::vector<int> &patches);

void save_disp_on_line(const std::string &filename,
                       const Eigen::Ref<const matxr_t> &x,
                       const Eigen::Ref<const matxr_t> &disp,
                       real_t scale_coeff = 0.1);

void save_basis(const std::string &prefix, const Eigen::Ref<const matxr_t> &pos,
                const Eigen::Ref<const matxr_t> &basis,
                real_t scale_coeff = 0.1, bool save_disp_flag = true);

void read_line(const std::string &filename,
               io::vtkFormat::CoordList<real_t> &nods);

template <typename Derived>
void read_line(const std::string &filename,
               Eigen::PlainObjectBase<Derived> &x) {
  io::vtkFormat::CoordList<real_t> nods;
  read_line(filename, nods);
  CHAOS_ASSERT(common::toNXMatrix(nods, x));
}
}  // namespace chaos::io::line
