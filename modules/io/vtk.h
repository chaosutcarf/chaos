#pragma once
#include <cstddef>
#include <map>
#include <numeric>
#include <string>
#include <vector>

#include "common/macro.h"
#include "common/numerical.h"
#include "common/type.h"
#include "io/io_basic.h"
#include "io/polyFormat.h"
namespace chaos::io {
struct vtkFormat : public polyFormat {
  enum DataType { ASCII, BINARY };
  inline static std::map<std::string, DataType> datatype_map{
      STRING_ENUM_MAP(ASCII), STRING_ENUM_MAP(BINARY)};

  enum DatasetType {
    STRUCTURED_POINTS,
    STRUCTURED_GRID,
    UNSTRUCTURED_GRID,
    POLYDATA,
    RECTILINEAR_GRID,
    FIELD
  };

  inline static std::map<std::string, DatasetType> dataset_map{
      STRING_ENUM_MAP(STRUCTURED_POINTS), STRING_ENUM_MAP(STRUCTURED_GRID),
      STRING_ENUM_MAP(UNSTRUCTURED_GRID), STRING_ENUM_MAP(POLYDATA),
      STRING_ENUM_MAP(RECTILINEAR_GRID),  STRING_ENUM_MAP(FIELD)};

  enum CellType {
    //-> Linear cell types.
    VTK_VERTEX = 1,
    VTK_POLY_VERTEX,
    VTK_LINE,
    VTK_POLY_LINE,
    VTK_TRIANGLE,
    VTK_TRIANGLE_STRIP,
    VTK_POLYGON,
    VTK_PIXEL,
    VTK_QUAD,
    VTK_TETRA,
    VTK_VOXEL,
    VTK_HEXAHEDRON,
    VTK_WEDGE,
    VTK_PYRAMID,
    //-> non-linear cell types.
    VTK_QUADRATIC_EDGE = 21,
    VTK_QUADRATIC_TRIANGLE,
    VTK_QUADRATIC_QUAD,
    VTK_QUADRATIC_TETRA,
    VTK_QUADRATIC_HEXAHEDRON,
  };

  template <typename Index>
  using Cell = std::vector<Index>;
  template <typename Index>
  using CellList = std::vector<Cell<Index>>;
  using CellTypeList = std::vector<CellType>;

  template <typename Scalar = double, typename Index = size_t>
  inline static bool load(const std::string &file, CoordList<Scalar> &nods,
                          CellList<Index> &cells, CellTypeList &cell_types);

  template <typename Scalar = double, typename Index = size_t>
  inline static bool save(const std::string &file,
                          const CoordList<Scalar> &nods,
                          const CellList<Index> &cells,
                          const CellTypeList &cell_types);

  inline static bool load_basic_part(std::istream &is, std::string &header,
                                     std::string &title, DataType &type,
                                     DatasetType &dataset);

  template <typename Scalar = double, typename Index = size_t>
  inline static bool load_data_part(std::istream &is, DataType &type,
                                    DatasetType &dataset,
                                    CoordList<Scalar> &nods,
                                    CellList<Index> &cells,
                                    CellTypeList &cell_types);

  template <typename Scalar>
  inline static bool load_scalar_property(const std::string &file,
                                          vec_t<Scalar> &ppt,
                                          const std::string &ppt_name);
  template <typename Scalar>
  inline static bool load_scalar_property(const std::string &file,
                                          std::vector<Scalar> &ppt,
                                          const std::string &ppt_name);
  template <typename Scalar>
  inline static bool load_vector_property(const std::string &file,
                                          std::vector<std::vector<Scalar>> &ppt,
                                          const std::string &ppt_name);
  template <typename Scalar>
  inline static bool load_vector_property(const std::string &file,
                                          std::vector<vec_t<Scalar>> &ppt,
                                          const std::string &ppt_name);
  template <typename Derived>
  inline static bool export_property(const std::string &file,
                                     const Eigen::MatrixBase<Derived> &ppt,
                                     const std::string &type,
                                     const std::string &ppt_name,
                                     bool flag = true);
  template <typename Scalar>
  inline static bool export_property(const std::string &file,
                                     const std::vector<Scalar> &ppt,
                                     const std::string &type,
                                     const std::string &ppt_name,
                                     bool flag = true);
  template <typename Scalar>
  inline static bool export_property(
      const std::string &file, const std::vector<std::vector<Scalar>> &ppt,
      const std::string &type, const std::string &ppt_name, bool flag = true);
  template <typename Scalar>
  inline static bool export_property(const std::string &file,
                                     const std::vector<vec_t<Scalar>> &ppt,
                                     const std::string &type,
                                     const std::string &ppt_name,
                                     bool flag = true);

  template <typename ppt_type>
  inline static bool export_node_property(const std::string &file,
                                          const ppt_type &ppt,
                                          const std::string &ppt_name,
                                          bool flag = true);
  template <typename ppt_type>
  inline static bool export_cell_property(const std::string &file,
                                          const ppt_type &ppt,
                                          const std::string &ppt_name,
                                          bool flag = true);

  template <typename Scalar = double>
  inline static bool load_points(std::istream &is, CoordList<Scalar> &nods);

  template <typename Index = size_t>
  inline static bool load_cells(std::istream &is, CellList<Index> &cells);

  inline static bool load_cell_types(std::istream &is,
                                     CellTypeList &cell_types);
};

////////////////////////////////////////////////////////////////////////
//                       template implementation                      //
////////////////////////////////////////////////////////////////////////
template <typename Scalar>
bool vtkFormat::load_scalar_property(const std::string &file,
                                     vec_t<Scalar> &ppt,
                                     const std::string &ppt_name) {
  return with_read(file, [&](std::istream &is) {
    std::string line;
    std::string type, name;
    bool ret = false;
    //-> locate.
    while (nextline(is, line)) {
      std::stringstream ss(line);
      ss >> type >> name;
      if (type == "SCALARS" && name == ppt_name) {
        //-> pickup the lookup table line.
        nextline(is, line);
        if (line.find("LOOKUP_TABLE") != std::string::npos) {
          ret = true;
        } else {
          warn_msg("vtk format load property failed.");
        }
        break;
      }
    }
    if (ret) {
      for (int i = 0; i < ppt.size(); ++i) {
        is >> ppt[i];
      }
    }
    return ret;
  });
}
template <typename Scalar>
bool vtkFormat::load_scalar_property(const std::string &file,
                                     std::vector<Scalar> &ppt,
                                     const std::string &ppt_name) {
  return with_read(file, [&](std::istream &is) {
    std::string line;
    std::string type, name;
    bool ret = false;
    //-> locate.
    while (nextline(is, line)) {
      std::stringstream ss(line);
      ss >> type >> name;
      if (type == "SCALARS" && name == ppt_name) {
        //-> pickup the lookup table line.
        nextline(is, line);
        if (line.find("LOOKUP_TABLE") != std::string::npos) {
          ret = true;
        } else {
          warn_msg("vtk format load property failed.");
        }
        break;
      }
    }
    if (ret) {
      for (size_t i = 0; i < ppt.size(); ++i) {
        is >> ppt[i];
      }
    }
    return ret;
  });
}
template <typename Scalar>
bool vtkFormat::load_vector_property(const std::string &file,
                                     std::vector<std::vector<Scalar>> &ppt,
                                     const std::string &ppt_name) {
  return with_read(file, [&](std::istream &is) {
    std::string line;
    std::string type, name;
    bool ret = false;
    //-> locate.
    while (nextline(is, line)) {
      std::stringstream ss(line);
      ss >> type >> name;
      if (type == "VECTORS" && name == ppt_name) {
        ret = true;
        break;
      }
    }
    if (ret) {
      for (size_t i = 0; i < ppt.size(); ++i) {
        //-> ensure the vector data is x,y,z
        ppt[i].resize(3);
        is >> ppt[i][0] >> ppt[i][1] >> ppt[i][2];
      }
    }
    return ret;
  });
}
template <typename Scalar>
bool vtkFormat::load_vector_property(const std::string &file,
                                     std::vector<vec_t<Scalar>> &ppt,
                                     const std::string &ppt_name) {
  return with_read(file, [&](std::istream &is) {
    std::string line;
    std::string type, name;
    bool ret = false;
    //-> locate.
    while (nextline(is, line)) {
      std::stringstream ss(line);
      ss >> type >> name;
      if (type == "VECTORS" && name == ppt_name) {
        ret = true;
        break;
      }
    }
    if (ret) {
      for (size_t i = 0; i < ppt.size(); ++i) {
        //-> ensure the vector data is x,y,z
        ppt[i].resize(3);
        is >> ppt[i][0] >> ppt[i][1] >> ppt[i][2];
      }
    }
    return ret;
  });
}
template <typename Scalar>
bool vtkFormat::export_property(const std::string &file,
                                const std::vector<Scalar> &ppt,
                                const std::string &type,
                                const std::string &ppt_name, bool flag) {
  return with_append(file, [&](std::ostream &os) {
    if (flag) {
      os << type << " " << ppt.size() << "\n";
    }
    os << "SCALARS " << ppt_name << " double 1\nLOOKUP_TABLE default\n";
    for (const auto &p : ppt) {
      os << p << "\n";
    }
  });
}
template <typename Derived>
bool vtkFormat::export_property(const std::string &file,
                                const Eigen::MatrixBase<Derived> &ppt,
                                const std::string &type,
                                const std::string &ppt_name, bool flag) {
  size_t total_dim;
  std::string header;
  if (ppt.cols() == 1) {
    header = "SCALARS " + ppt_name + " double 1\nLOOKUP_TABLE default\n";
    total_dim = ppt.size();
  } else {
    //-> assume ppt_matrix: R^{3 x N}
    header = "VECTORS " + ppt_name + " double\n";
    total_dim = ppt.cols();
  }
  return with_append(file, [&](std::ostream &os) {
    if (flag) {
      os << type << " " << total_dim << "\n";
    }
    os << header;
    for (int i = 0; i < ppt.cols(); ++i) {
      for (int j = 0; j < ppt.rows(); ++j) {
        os << ppt(j, i) << " ";
      }
      os << "\n";
    }
  });
}

template <typename Scalar>
bool vtkFormat::export_property(const std::string &file,
                                const std::vector<vec_t<Scalar>> &ppt,
                                const std::string &type,
                                const std::string &ppt_name, bool flag) {
  return with_append(file, [&](std::ostream &os) {
    if (flag) {
      os << type << " " << ppt.size() << "\n";
    }
    os << "VECTORS " << ppt_name << " double\n";
    for (const auto &p : ppt) {
      for (const auto &q : p) {
        os << q << " ";
      }
      os << "\n";
    }
  });
}

template <typename Scalar>
bool vtkFormat::export_property(const std::string &file,
                                const std::vector<std::vector<Scalar>> &ppt,
                                const std::string &type,
                                const std::string &ppt_name, bool flag) {
  return with_append(file, [&](std::ostream &os) {
    if (flag) {
      os << type << " " << ppt.size() << "\n";
    }
    os << "VECTORS " << ppt_name << " double\n";
    for (const auto &p : ppt) {
      for (const auto &q : p) {
        os << q << " ";
      }
      os << "\n";
    }
  });
}

template <typename ppt_type>
bool vtkFormat::export_node_property(const std::string &file,
                                     const ppt_type &ppt,
                                     const std::string &ppt_name, bool flag) {
  return export_property(file, ppt, "POINT_DATA", ppt_name, flag);
}

template <typename ppt_type>
bool vtkFormat::export_cell_property(const std::string &file,
                                     const ppt_type &ppt,
                                     const std::string &ppt_name, bool flag) {
  return export_property(file, ppt, "CELL_DATA", ppt_name, flag);
}

bool vtkFormat::load_basic_part(std::istream &is, std::string &header,
                                std::string &title, DataType &type,
                                DatasetType &dataset) {
  std::string type_str, _, dataset_str;
  if (std::getline(is, header) && std::getline(is, title)) {
    is >> type_str >> _ >> dataset_str;
    if (_ == "DATASET") {
      if (auto iter = datatype_map.find(type_str); iter != datatype_map.end()) {
        type = iter->second;
        if (auto iter = dataset_map.find(dataset_str);
            iter != dataset_map.end()) {
          dataset = iter->second;
          return true;
        }
      }
    }
  }

  return false;
}

template <typename Scalar>
bool vtkFormat::load_points(std::istream &is, CoordList<Scalar> &nods) {
  std::string _;
  is >> _;
  if (_ != "POINTS") {
    return false;
  }
  size_t nods_num;
  is >> nods_num >> _;  //-> ignore datatype input.
  nods.reserve(nods_num);
  for (size_t i = 0; i < nods_num; ++i) {
    Scalar x, y, z;
    is >> x >> y >> z;
    nods.emplace_back(Coord<Scalar>{x, y, z});
  }
  return nods.size() == nods_num;
}

template <typename Index>
bool vtkFormat::load_cells(std::istream &is, CellList<Index> &cells) {
  std::string _;
  is >> _;
  if (_ != "CELLS") {
    return false;
  }
  size_t cells_num, total;
  is >> cells_num >> total;
  cells.reserve(cells_num);
  for (size_t i = 0; i < cells_num; ++i) {
    size_t points_num;
    is >> points_num;
    Cell<Index> C(points_num);
    for (size_t j = 0; j < points_num; ++j) {
      is >> C[j];
    }
    cells.emplace_back(C);
  }
  return cells.size() == cells_num;
}

bool vtkFormat::load_cell_types(std::istream &is, CellTypeList &cell_types) {
  std::string _;
  is >> _;
  if (_ != "CELL_TYPES") {
    return false;
  }
  size_t cell_type_num;
  is >> cell_type_num;
  cell_types.reserve(cell_type_num);
  for (size_t i = 0; i < cell_type_num; ++i) {
    int _;
    is >> _;
    cell_types.emplace_back(static_cast<CellType>(_));
  }
  return cell_types.size() == cell_type_num;
}

template <typename Scalar, typename Index>
bool vtkFormat::load_data_part(std::istream &is, DataType &type,
                               DatasetType &dataset, CoordList<Scalar> &nods,
                               CellList<Index> &cells,
                               CellTypeList &cell_types) {
  if (type == BINARY || dataset != UNSTRUCTURED_GRID) {
    warn_msg("Not supported yet.");
    return false;
  }
  return load_points(is, nods) && load_cells(is, cells) &&
         load_cell_types(is, cell_types);
}

template <typename Scalar, typename Index>
bool vtkFormat::load(const std::string &file, CoordList<Scalar> &nods,
                     CellList<Index> &cells, CellTypeList &cell_types) {
  return with_read(file, [&](std::istream &is) {
    DataType type;
    DatasetType dataset;
    std::string _;
    return load_basic_part(is, _, _, type, dataset) &&
           load_data_part(is, type, dataset, nods, cells, cell_types);
  });
}

template <typename Scalar, typename Index>
bool vtkFormat::save(const std::string &file, const CoordList<Scalar> &nods,
                     const CellList<Index> &cells,
                     const CellTypeList &cell_types) {
  return with_write(file, [&](std::ostream &os) {
    os << "# vtk DataFile Version 2.0\n"
          "chaos vtkFormat utilities\n"
          "ASCII\n"
          "DATASET UNSTRUCTURED_GRID\n";
    os.precision(numerical::constant<Scalar>::precision);
    //-> export nodes.
    os << "POINTS " << nods.size() << " double\n";
    for (const auto &node : nods) {
      for (const auto &p : node) {
        os << p << " ";
      }
      for (size_t i = node.size(); i < 3; ++i) {
        os << 0 << " ";
      }
      os << "\n";
    }
    //-> export cells.
    size_t total = std::accumulate(cells.begin(), cells.end(), 0,
                                   [](size_t last, const Cell<Index> &cur) {
                                     return last + cur.size() + 1;
                                   });
    os << "CELLS " << cells.size() << " " << total << "\n";
    for (const auto &cell : cells) {
      os << cell.size();
      for (const auto &c : cell) {
        os << " " << c;
      }
      os << "\n";
    }
    //-> export cell_types.
    os << "CELL_TYPES " << cell_types.size() << "\n";
    for (const auto &t : cell_types) {
      os << t << "\n";
    }
  });
}
}  // namespace chaos::io
