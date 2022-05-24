#include "line.h"

namespace chaos::io::line {
void save_line_frame(const std::string &filename,
                     const Eigen::Ref<const mat3xr_t> &pos,
                     const Eigen::Ref<const mat4xr_t> &qtn) {
  CHAOS_ASSERT(pos.cols() == qtn.cols() + 1);
  //-> compute N.
  size_t N = pos.cols();

  io::vtkFormat::CoordList<real_t> nods;
  io::vtkFormat::CellList<int> cells;
  io::vtkFormat::CellTypeList celltypes;
  std::vector<double> ppt;

  //-> allocate memory.
  nods.reserve(4 * N - 4);
  cells.reserve(3 * N - 3);
  celltypes.reserve(3 * N - 3);

  //-> for each segment.
  for (size_t i = 0; i < N - 1; ++i) {
    mat33r_t frame =
        Eigen::Map<const qtnr_t>(qtn.col(i).data()).toRotationMatrix();
    real_t length = (pos.col(i + 1) - pos.col(i)).norm() / 2;
    vec3r_t O = (pos.col(i + 1) + pos.col(i)) / 2;
    //-> construct 4 points.
    nods.emplace_back(O.data(), O.data() + 3);
    for (int j = 0; j < 3; ++j) {
      vec3r_t dx = O + frame.col(j) * length;
      nods.emplace_back(dx.data(), dx.data() + 3);
      //-> construct index.
      io::vtkFormat::Cell<int> index;
      index.emplace_back(4 * i);
      index.emplace_back(4 * i + j + 1);
      cells.emplace_back(index);
      ppt.emplace_back(j);
      celltypes.emplace_back(io::vtkFormat::VTK_LINE);
    }
  }

  io::vtkFormat::save(filename, nods, cells, celltypes);
  io::vtkFormat::export_cell_property(filename, ppt, "frame_color");
}

void save_line(const std::string &filename,
               const Eigen::Ref<const matxr_t> &x) {
  CHAOS_ASSERT(x.rows() == 2 || x.rows() == 3);
  io::vtkFormat::CellList<int> cells;
  io::vtkFormat::CellTypeList celltypes;
  //-> construct index.
  io::vtkFormat::Cell<int> index;

  //-> allocate memory.
  index.reserve(x.cols());
  cells.reserve(2);
  celltypes.reserve(2);

  for (int i = 0; i < x.cols(); ++i) {
    index.emplace_back(i);
  }
  //-> save line.
  cells.emplace_back(index);
  celltypes.emplace_back(io::vtkFormat::VTK_POLY_LINE);
  //-> save points.
  cells.emplace_back(index);
  celltypes.emplace_back(io::vtkFormat::VTK_POLY_VERTEX);

  io::vtkFormat::save(filename, common::fromNXMatrix<real_t>(x), cells,
                      celltypes);
}

void save_patch_line(const std::string &filename,
                     const Eigen::Ref<const matxr_t> &x,
                     const std::vector<std::vector<int>> &indexes) {
  //-> check the max index does not overflow.

  io::vtkFormat::CellList<int> cells;
  io::vtkFormat::CellTypeList celltypes;
  std::vector<double> ppt;
  int N = indexes.size();

  //-> allocate memory.
  cells.reserve(2 * N);
  celltypes.reserve(2 * N);
  ppt.reserve(2 * N);

  //-> save points.
  for (int i = 0; i < N; ++i) {
    //-> save line.
    cells.emplace_back(indexes[i]);
    celltypes.emplace_back(io::vtkFormat::VTK_POLY_LINE);
    //-> save nodes.
    cells.emplace_back(indexes[i]);
    celltypes.emplace_back(io::vtkFormat::VTK_POLY_VERTEX);
    //-> save color.
    ppt.emplace_back((i + 1) * 1.0 / N);
    ppt.emplace_back((i + 1) * 1.0 / N);
  }
  io::vtkFormat::save(filename, common::fromNXMatrix<real_t>(x), cells,
                      celltypes);
  io::vtkFormat::export_cell_property(filename, ppt, "patch_color");
}

void save_patch_line(const std::string &filename,
                     const Eigen::Ref<const matxr_t> &x,
                     const std::vector<int> &patches) {
  std::vector<std::vector<int>> indexes;
  indexes.reserve(patches.size());
  int idx = 1;
  for (size_t i = 0; i < patches.size(); ++i) {
    std::vector<int> index;
    index.resize(patches[i]);
    idx--;
    for (int j = 0; j < patches[i]; ++j) {
      index[j] = idx++;
    }
    indexes.emplace_back(index);
  }
  return save_patch_line(filename, x, indexes);
}

void save_patch_line(const std::string &filename,
                     const Eigen::Ref<const matxr_t> &x, int N) {
  CHAOS_ASSERT(x.rows() == 2 || x.rows() == 3);
  int n = (x.cols() - 1) / (N - 1);
  return save_patch_line(filename, x, std::vector<int>(n, N));
}

void save_disp_on_line(const std::string &filename,
                       const Eigen::Ref<const matxr_t> &x,
                       const Eigen::Ref<const matxr_t> &disp,
                       real_t scale_coeff) {
  CHAOS_ASSERT(x.rows() == disp.rows());
  CHAOS_ASSERT(x.cols() == disp.cols());
  CHAOS_ASSERT(x.rows() == 2 || x.rows() == 3);

  io::vtkFormat::CellList<int> cells;
  io::vtkFormat::CellTypeList celltypes;
  //-> construct nods;
  auto nods = common::fromNXMatrix<real_t>(x);
  //-> construct other nods;
  int N = disp.cols();
  int d = disp.rows();
  //-> allocate memory.
  cells.reserve(N);
  celltypes.reserve(N);
  nods.reserve(nods.size() + N);
  for (int i = 0; i < N; ++i) {
    io::vtkFormat::Cell<int> index;
    vecxr_t vec = x.col(i) + disp.col(i) * scale_coeff;
    //-> new node.
    nods.emplace_back(vec.data(), vec.data() + d);
    index.emplace_back(i);
    index.emplace_back(i + N);
    cells.emplace_back(index);
    celltypes.emplace_back(io::vtkFormat::VTK_LINE);
  }

  io::vtkFormat::save(filename, nods, cells, celltypes);
}

void save_basis(const std::string &prefix, const Eigen::Ref<const matxr_t> &pos,
                const Eigen::Ref<const matxr_t> &basis, real_t scale_coeff,
                bool save_disp_flag) {
  CHAOS_ASSERT(pos.size() == basis.rows());
  CHAOS_ASSERT(pos.rows() == 2 || pos.rows() == 3);
  int rows = pos.rows(), cols = pos.cols();
  matxr_t deform(rows, cols);
  for (int i = 0; i < basis.cols(); ++i) {
    Eigen::Map<const matxr_t> disp(basis.col(i).data(), rows, cols);
    deform = pos + scale_coeff * disp;
    save_line(prefix + "." + std::to_string(i) + ".vtk", deform);
    if (save_disp_flag) {
      save_disp_on_line(prefix + "disp-on-line" + std::to_string(i) + ".vtk",
                        pos, disp, scale_coeff);
    }
  }
}

void read_line(const std::string &filename,
               io::vtkFormat::CoordList<real_t> &nods) {
  io::vtkFormat::CellList<int> cells;
  io::vtkFormat::CellTypeList cell_types;
  io::vtkFormat::load(filename, nods, cells, cell_types);
  //-> TODO. need to check.
}

}  // namespace chaos::io::line
