#include <catch2/catch.hpp>
#include <ostream>
#include <sstream>
#include <string>

#include "common/numerical.h"
#include "common/type_helper.h"
#include "io/dump.h"
#include "io/io_basic.h"
#include "io/line/line.h"
#include "io/obj.h"
#include "io/off.h"
#include "io/vtk.h"
#include "utils/fs/fshelper.h"
using namespace std;
using namespace chaos;
using namespace chaos::io;
TEST_CASE("test file basic io", "[io]") {
  string file_name{"basic_simple.txt"};
  std::ofstream fout(file_name);
  string content{"hello world\ngoodbye\n"};
  fout << content;
  fout.close();

  std::string my_content;
  CHECK(with_open(
            file_name,
            [&my_content](auto &is) {
              my_content = string((std::istreambuf_iterator<char>(is)),
                                  std::istreambuf_iterator<char>());
            },
            std::fstream::in) == true);
  CHECK(my_content == content);

  CHECK(with_open(
            file_name,
            [&my_content](auto &is) {
              my_content = string((std::istreambuf_iterator<char>(is)),
                                  std::istreambuf_iterator<char>());
              return false;
            },
            std::fstream::in) == false);
  CHECK(my_content == content);

  my_content.clear();
  CHECK(with_readlines(file_name, [&my_content](std::string &line) {
    my_content += line + "\n";
  }));
  const string donotexist{"donotexist.txt"};
  chaos::utils::rm_file(donotexist);
  CHECK(with_open(
            donotexist, [](auto &) {}, std::fstream::in) == false);
  CHECK(with_read(donotexist, [](auto &) {}) == false);
  CHECK(with_write(donotexist, [](auto &os) { os << "hello\n"; }) == true);
  CHECK(with_append(donotexist, [](auto &os) { os << "world"; }) == true);
  CHECK(with_append(donotexist, [](auto &os) { os << "\n"; }) == true);
  my_content.clear();
  CHECK(with_readlines(
      donotexist, [&my_content](std::string &line) { my_content += line; }));
  CHECK(my_content == "helloworld");
}

template <typename T>
static inline bool near_v(const T &v1, const T &v2) {
  if (v1.size() != v2.size()) {
    return false;
  } else {
    for (size_t i = 0; i < v1.size(); ++i) {
      if (v1[i].size() != v2[i].size()) {
        return false;
      } else {
        for (size_t j = 0; j < v1[i].size(); ++j) {
          if (!chaos::numerical::near(v1[i][j], v2[i][j])) {
            return false;
          }
        }
      }
    }
    return true;
  }
}

#define MY_CHECK(v)          \
  if (!near_v(v, ref_##v)) { \
    error_msg("{}", v);      \
  }                          \
  CHECK(near_v(v, ref_##v));

TEST_CASE("test objloader", "[io]") {
  const std::string objfile{"cube.obj"};
  with_write(objfile, [](std::ostream &os) {
    os << R"delimiter(v 1.000000 1.000000 -1.000000
v 1.000000 -1.000000 -1.000000
v 1.000000 1.000000 1.000000
v 1.000000 -1.000000 1.000000
v -1.000000 1.000000 -1.000000
v -1.000000 -1.000000 -1.000000
v -1.000000 1.000000 1.000000
v -1.000000 -1.000000 1.000000
vt 0.625000 0.500000
vt 0.875000 0.500000
vt 0.875000 0.750000
vt 0.625000 0.750000
vt 0.375000 0.750000
vt 0.625000 1.000000
vt 0.375000 1.000000
vt 0.375000 0.000000
vt 0.625000 0.000000
vt 0.625000 0.250000
vt 0.375000 0.250000
vt 0.125000 0.500000
vt 0.375000 0.500000
vt 0.125000 0.750000
vn 0.0000 1.0000 0.0000
vn 0.0000 0.0000 1.0000
vn -1.0000 0.0000 0.0000
vn 0.0000 -1.0000 0.0000
vn 1.0000 0.0000 0.0000
vn 0.0000 0.0000 -1.0000
f 1/1/1 5/2/1 7/3/1 3/4/1
f 4/5/2 3/4/2 7/6/2 8/7/2
f 8/8/3 7/9/3 5/10/3 6/11/3
f 6/12/4 2/13/4 4/5/4 8/14/4
f 2/13/5 1/1/5 3/4/5 4/5/5
f 6/11/6 5/10/6 1/1/6 2/13/6
)delimiter";
  });

  objFormat::CoordList<double> ref_v{
      {1.000000, 1.000000, -1.000000},  {1.000000, -1.000000, -1.000000},
      {1.000000, 1.000000, 1.000000},   {1.000000, -1.000000, 1.000000},
      {-1.000000, 1.000000, -1.000000}, {-1.000000, -1.000000, -1.000000},
      {-1.000000, 1.000000, 1.000000},  {-1.000000, -1.000000, 1.000000}},
      ref_vt{{0.625000, 0.500000}, {0.875000, 0.500000}, {0.875000, 0.750000},
             {0.625000, 0.750000}, {0.375000, 0.750000}, {0.625000, 1.000000},
             {0.375000, 1.000000}, {0.375000, 0.000000}, {0.625000, 0.000000},
             {0.625000, 0.250000}, {0.375000, 0.250000}, {0.125000, 0.500000},
             {0.375000, 0.500000}, {0.125000, 0.750000}},
      ref_vn{{0.0000, 1.0000, 0.0000},  {0.0000, 0.0000, 1.0000},
             {-1.0000, 0.0000, 0.0000}, {0.0000, -1.0000, 0.0000},
             {1.0000, 0.0000, 0.0000},  {0.0000, 0.0000, -1.0000}};
  objFormat::FaceList<int> ref_f{{0, 4, 6, 2}, {3, 2, 6, 7}, {7, 6, 4, 5},
                                 {5, 1, 3, 7}, {1, 0, 2, 3}, {5, 4, 0, 1}},
      ref_ft{{0, 1, 2, 3},    {4, 3, 5, 6},  {7, 8, 9, 10},
             {11, 12, 4, 13}, {12, 0, 3, 4}, {10, 9, 0, 12}},
      ref_fn{{0, 0, 0, 0}, {1, 1, 1, 1}, {2, 2, 2, 2},
             {3, 3, 3, 3}, {4, 4, 4, 4}, {5, 5, 5, 5}};
  objFormat::CoordList<double> v, vt, vn;
  objFormat::FaceList<int> f, ft, fn;

  const auto clear = [&]() {
    v.clear(), vt.clear(), vn.clear(), f.clear(), ft.clear(), fn.clear();
    ref_v.clear(), ref_vt.clear(), ref_vn.clear(), ref_f.clear(),
        ref_ft.clear(), ref_fn.clear();
  };

#define BATCH_MY_CHECK() \
  MY_CHECK(v);           \
  MY_CHECK(vt);          \
  MY_CHECK(vn);          \
  MY_CHECK(f);           \
  MY_CHECK(ft);          \
  MY_CHECK(fn);

#define MY_SIMPLE_TEST(mode)                                            \
  clear();                                                              \
  objFormat::load<mode>(objfile, ref_v, ref_vt, ref_vn, ref_f, ref_ft,  \
                        ref_fn);                                        \
  objFormat::save<mode>("out-" + objfile, ref_v, ref_vt, ref_vn, ref_f, \
                        ref_ft, ref_fn);                                \
  objFormat::load<mode>("out-" + objfile, v, vt, vn, f, ft, fn);        \
  BATCH_MY_CHECK();

  //-> check load.
  objFormat::load<objFormat::ALL_MODE>(objfile, v, vt, vn, f, ft, fn);
  BATCH_MY_CHECK();

  v.clear(), vt.clear(), vn.clear(), f.clear(), ft.clear(), fn.clear();
  objFormat::load<objFormat::ALL_MODE ^ objFormat::FN_MODE>(objfile, v, vt, vn,
                                                            f, ft, fn);
  MY_CHECK(v);
  MY_CHECK(vt);
  MY_CHECK(vn);
  MY_CHECK(f);
  MY_CHECK(ft);

  v.clear(), vt.clear(), vn.clear(), f.clear(), ft.clear(), fn.clear();
  objFormat::load<objFormat::ALL_MODE ^ objFormat::FTC_MODE>(objfile, v, vt, vn,
                                                             f, ft, fn);
  MY_CHECK(v);
  MY_CHECK(vt);
  MY_CHECK(vn);
  MY_CHECK(f);
  MY_CHECK(fn);

  v.clear(), vt.clear(), vn.clear(), f.clear(), ft.clear(), fn.clear();
  objFormat::load<objFormat::ALL_MODE ^ objFormat::FTC_MODE ^
                  objFormat::FN_MODE>(objfile, v, vt, vn, f, ft, fn);
  MY_CHECK(v);
  MY_CHECK(vt);
  MY_CHECK(vn);
  MY_CHECK(f);

  MY_SIMPLE_TEST(objFormat::ALL_MODE);
  MY_SIMPLE_TEST(objFormat::SIMPLE_MODE);
  MY_SIMPLE_TEST(objFormat::V_MODE);
  MY_SIMPLE_TEST(objFormat::V_MODE | objFormat::TC_MODE);
  MY_SIMPLE_TEST(objFormat::V_MODE | objFormat::TC_MODE | objFormat::VN_MODE);
  MY_SIMPLE_TEST(objFormat::V_MODE | objFormat::TC_MODE | objFormat::F_MODE |
                 objFormat::FTC_MODE);

  //-> add one more error line to the objfile.
  with_append(objfile, [](std::ostream &os) { os << "f error failed line\n"; });
  MY_SIMPLE_TEST(objFormat::ALL_MODE);

#undef MY_SIMPLE_TEST

  SECTION("test simple mode") {
    clear();
    objFormat::load(objfile, ref_v, ref_f);
    objFormat::save("out-" + objfile, ref_v, ref_f);
    objFormat::load("out-" + objfile, v, f);
    BATCH_MY_CHECK();
  }

#undef BATCH_MY_CHECK
}

TEST_CASE("test vtkloader", "[io]") {
  const std::string vtkfile{"cube.vtk"};
  with_write(vtkfile, [](std::ostream &os) {
    os << R"delimiter(# vtk DataFile Version 2.0
chaos vtkFormat utilities
ASCII
DATASET UNSTRUCTURED_GRID
POINTS 8 double
1.000000 1.000000 -1.000000
1.000000 -1.000000 -1.000000
1.000000 1.000000 1.000000
1.000000 -1.000000 1.000000
-1.000000 1.000000 -1.000000
-1.000000 -1.000000 -1.000000
-1.000000 1.000000 1.000000
-1.000000 -1.000000 1.000000
CELLS 6 30
4 0 4 6 2
4 3 2 6 7
4 7 6 4 5
4 5 1 3 7
4 1 0 2 3
4 5 4 0 1
CELL_TYPES 6
9
9
9
9
9
9
)delimiter";
  });
  vtkFormat::CoordList<double> ref_v{
      {1.000000, 1.000000, -1.000000},  {1.000000, -1.000000, -1.000000},
      {1.000000, 1.000000, 1.000000},   {1.000000, -1.000000, 1.000000},
      {-1.000000, 1.000000, -1.000000}, {-1.000000, -1.000000, -1.000000},
      {-1.000000, 1.000000, 1.000000},  {-1.000000, -1.000000, 1.000000},
  },
      v;
  vtkFormat::CellList<int> ref_c{{0, 4, 6, 2}, {3, 2, 6, 7}, {7, 6, 4, 5},
                                 {5, 1, 3, 7}, {1, 0, 2, 3}, {5, 4, 0, 1}},
      c;
  vtkFormat::CellTypeList ref_ct(6, vtkFormat::CellType::VTK_QUAD), ct;

  const auto clear = [&]() { v.clear(), c.clear(), ct.clear(); };

  //-> check load.
  CHECK(vtkFormat::load(vtkfile, v, c, ct));
  MY_CHECK(v);
  MY_CHECK(c);
  CHECK(ref_ct.size() == ct.size());
  for (size_t i = 0; i < ct.size(); ++i) {
    CHECK(ref_ct[i] == ct[i]);
  }

  CHECK(vtkFormat::save("out-" + vtkfile, ref_v, ref_c, ref_ct));
  clear();
  CHECK(vtkFormat::load("out-" + vtkfile, v, c, ct));
  MY_CHECK(v);
  MY_CHECK(c);
  CHECK(ref_ct.size() == ct.size());
  for (size_t i = 0; i < ct.size(); ++i) {
    CHECK(ref_ct[i] == ct[i]);
  }
}

TEST_CASE("test failed cases of vtk loader", "[io]") {
  vtkFormat::CoordList<double> nods;
  vtkFormat::CellList<int> cells;
  vtkFormat::CellTypeList celltypes;

  SECTION("not support binary type") {
    const std::string vtkfile{"failed.binary.vtk"};
    with_write(vtkfile, [](std::ostream &os) {
      os << R"delimiter(# vtk DataFile Version 2.0
chaos vtkFormat utilities
BINARY
DATASET UNSTRUCTURED_GRID
)delimiter";
    });
    CHECK(!vtkFormat::load(vtkfile, nods, cells, celltypes));
  }

  SECTION("only support UNSTRUCTURED_GRID") {
    const std::string vtkfile{"failed.dataset.vtk"};
    with_write(vtkfile, [](std::ostream &os) {
      os << R"delimiter(# vtk DataFile Version 2.0
chaos vtkFormat utilities
BINARY
DATASET STRUCTURED_GRID
)delimiter";
    });
    CHECK(!vtkFormat::load(vtkfile, nods, cells, celltypes));
  }

  SECTION("typos of dataset type") {
    const std::string vtkfile{"failed.dataset.typo.vtk"};
    with_write(vtkfile, [](std::ostream &os) {
      os << R"delimiter(# vtk DataFile Version 2.0
chaos vtkFormat utilities
ASCII
'DATASET UNSTRUCTURED_GRID
)delimiter";
    });
    CHECK(!vtkFormat::load(vtkfile, nods, cells, celltypes));
  }

  SECTION("typos of points") {
    const std::string vtkfile{"failed.points.typo.vtk"};
    with_write(vtkfile, [](std::ostream &os) {
      os << R"delimiter(# vtk DataFile Version 2.0
chaos vtkFormat utilities
ASCII
DATASET UNSTRUCTURED_GRID
'POINTS 8 double
1.000000 1.000000 -1.000000
1.000000 -1.000000 -1.000000
1.000000 1.000000 1.000000
1.000000 -1.000000 1.000000
-1.000000 1.000000 -1.000000
-1.000000 -1.000000 -1.000000
-1.000000 1.000000 1.000000
-1.000000 -1.000000 1.000000
CELLS 6 30
4 0 4 6 2
4 3 2 6 7
4 7 6 4 5
4 5 1 3 7
4 1 0 2 3
4 5 4 0 1
CELL_TYPES 6
9
9
9
9
9
9
)delimiter";
    });
    CHECK(!vtkFormat::load(vtkfile, nods, cells, celltypes));
  }

  SECTION("typos of cells") {
    const std::string vtkfile{"failed.cells.typo.vtk"};
    with_write(vtkfile, [](std::ostream &os) {
      os << R"delimiter(# vtk DataFile Version 2.0
chaos vtkFormat utilities
ASCII
DATASET UNSTRUCTURED_GRID
POINTS 8 double
1.000000 1.000000 -1.000000
1.000000 -1.000000 -1.000000
1.000000 1.000000 1.000000
1.000000 -1.000000 1.000000
-1.000000 1.000000 -1.000000
-1.000000 -1.000000 -1.000000
-1.000000 1.000000 1.000000
-1.000000 -1.000000 1.000000
'CELLS 6 30
4 0 4 6 2 4 3 2 6 7 4 7 6 4 5 4 5 1 3 7 4 1 0 2 3 4 5 4 0 1
CELL_TYPES 6
9 9 9 9 9
)delimiter";
    });
    CHECK(!vtkFormat::load(vtkfile, nods, cells, celltypes));
  }

  SECTION("typos of celltypes") {
    const std::string vtkfile{"failed.celltypes.typo.vtk"};
    with_write(vtkfile, [](std::ostream &os) {
      os << R"delimiter(# vtk DataFile Version 2.0
chaos vtkFormat utilities
ASCII
DATASET UNSTRUCTURED_GRID
POINTS 8 double
1.000000 1.000000 -1.000000
1.000000 -1.000000 -1.000000
1.000000 1.000000 1.000000
1.000000 -1.000000 1.000000
-1.000000 1.000000 -1.000000
-1.000000 -1.000000 -1.000000
-1.000000 1.000000 1.000000
-1.000000 -1.000000 1.000000
CELLS 6 30
4 0 4 6 2 4 3 2 6 7 4 7 6 4 5 4 5 1 3 7 4 1 0 2 3 4 5 4 0 1
'CELL_TYPES 6
9 9 9 9 9 9
)delimiter";
    });
    CHECK(!vtkFormat::load(vtkfile, nods, cells, celltypes));
  }
}

TEST_CASE("test offloader", "[io]") {
  const std::string offfile{"cube.off"};
  with_write(offfile, [](std::ostream &os) {
    os << R"delimiter(OFF 8 6 0
# vertices
1.000000 1.000000 -1.000000
1.000000 -1.000000 -1.000000
1.000000 1.000000 1.000000
1.000000 -1.000000 1.000000
-1.000000 1.000000 -1.000000
-1.000000 -1.000000 -1.000000
-1.000000 1.000000 1.000000
-1.000000 -1.000000 1.000000
# faces
4 0 4 6 2
4 3 2 6 7
4 7 6 4 5
4 5 1 3 7
4 1 0 2 3
4 5 4 0 1
)delimiter";
  });

  offFormat::CoordList<double> ref_v{
      {1.000000, 1.000000, -1.000000},  {1.000000, -1.000000, -1.000000},
      {1.000000, 1.000000, 1.000000},   {1.000000, -1.000000, 1.000000},
      {-1.000000, 1.000000, -1.000000}, {-1.000000, -1.000000, -1.000000},
      {-1.000000, 1.000000, 1.000000},  {-1.000000, -1.000000, 1.000000},
  },
      v;
  offFormat::FaceList<int> ref_f{{0, 4, 6, 2}, {3, 2, 6, 7}, {7, 6, 4, 5},
                                 {5, 1, 3, 7}, {1, 0, 2, 3}, {5, 4, 0, 1}},
      f;

  const auto clear = [&]() { v.clear(), f.clear(); };

  //-> check load.
  CHECK(offFormat::load(offfile, v, f));
  MY_CHECK(v);
  MY_CHECK(f);

  //-> check save.
  CHECK(offFormat::save("out-" + offfile, ref_v, ref_f));
  clear();
  CHECK(offFormat::load("out-" + offfile, v, f));
  MY_CHECK(v);
  MY_CHECK(f);
}

TEST_CASE("test failed case of off loader", "[io]") {
  offFormat::CoordList<double> V;
  offFormat::FaceList<int> F;

  SECTION("only OFF support") {
    const std::string offfile{"failed.off.off"};
    with_write(offfile, [](std::ostream &os) {
      os << R"delimiter(NOFF 0 0 0)delimiter";
    });
    CHECK(!offFormat::load(offfile, V, F));
  }

  SECTION("only ASCII support") {
    const std::string offfile{"failed.ascii.off"};
    with_write(offfile, [](std::ostream &os) {
      os << R"delimiter(OFF BINARY 0 0 0)delimiter";
    });
    CHECK(!offFormat::load(offfile, V, F));
  }

  SECTION("num of vertice is wrong.") {
    const std::string offfile{"failed.v.off"};
    with_write(offfile, [](std::ostream &os) {
      os << R"delimiter(OFF 8 6 0
1.000000 1.000000 -1.000000
1.000000 -1.000000 -1.000000
1.000000 1.000000 1.000000
1.000000 -1.000000 1.000000
-1.000000 1.000000 -1.000000
-1.000000 -1.000000 -1.000000
-1.000000 1.000000 1.000000
)delimiter";
    });
    CHECK(!offFormat::load(offfile, V, F));
  }

  SECTION("num of faces is wrong") {
    const std::string offfile{"failed.f.off"};
    with_write(offfile, [](std::ostream &os) {
      os << R"delimiter(OFF 8 6 0
1.000000 1.000000 -1.000000
1.000000 -1.000000 -1.000000
1.000000 1.000000 1.000000
1.000000 -1.000000 1.000000
-1.000000 1.000000 -1.000000
-1.000000 -1.000000 -1.000000
-1.000000 1.000000 1.000000
-1.000000 -1.000000 1.000000
4 0 4 6 2
4 3 2 6 7
4 7 6 4 5
4 5 1 3 7
4 1 0 2 3
)delimiter";
    });
    CHECK(!offFormat::load(offfile, V, F));
  }
}

#undef MY_CHECK

TEST_CASE("test dump utils", "[io]") {
  chaos::matxr_t mat(10, 20), in_mat;
  mat.setRandom();
  dump_matrix_binary("dump_dense.dat", mat);
  read_matrix_binary("dump_dense.dat", in_mat);
  CHECK(std::equal_to<chaos::matxr_t>()(mat, in_mat));

  chaos::csr_matr_t spmat(10, 20), in_spmat;
  spmat = mat.sparseView();
  dump_sparse_matrix_binary("dump_sparse.dat", spmat);
  read_sparse_matrix_binary("dump_sparse.dat", in_spmat);
  CHECK(std::equal_to<chaos::matxr_t>()(chaos::matxr_t(spmat),
                                        (chaos::matxr_t)in_spmat));
}

TEST_CASE("test line vtk", "[io]") {
  chaos::matxr_t pos(3, 6), qtn(4, 5), disp(3, 6), basis(18, 2);
  pos.setRandom();
  qtn.setRandom();
  disp.setRandom();
  basis.setRandom();
  qtn.colwise().normalize();
  line::save_line("line.vtk", pos);
  line::save_line_frame("line-frame.vtk", pos, qtn);
  line::save_disp_on_line("disp-lin.vtk", pos, disp);
  line::save_basis("basis-", pos, basis);
  line::save_patch_line("patch.vtk", pos, 2);
  chaos::matxr_t in_pos;
  line::read_line("line.vtk", in_pos);
  CHECK(std::equal_to<chaos::matxr_t>()(pos, in_pos));
}

TEST_CASE("test vtk ppt", "[io]") {
  //-> simple two nodes with one edge.
  vtkFormat::CoordList<real_t> nods;
  vtkFormat::CellList<int> cells;
  vtkFormat::CellTypeList celltypes;
  nods.push_back({0, 0, 0});
  nods.push_back({1, 0, 0});
  cells.push_back({0, 1});
  celltypes.push_back(vtkFormat::VTK_LINE);
  //-> node property.
  std::vector<real_t> vec_ppt(2), vec_ppt_load(2);
  vec_ppt[0] = 0;
  vec_ppt[1] = 1;
  vtkFormat::save("ppt_vtk.vtk", nods, cells, celltypes);
  vtkFormat::export_node_property("ppt_vtk.vtk", vec_ppt, "vec_ppt");
  vtkFormat::load_scalar_property("ppt_vtk.vtk", vec_ppt_load, "vec_ppt");
  Eigen::Map<vecxr_t> v1(vec_ppt.data(), 2);
  Eigen::Map<vecxr_t> v2(vec_ppt_load.data(), 2);
  vecxr_t v3(2);
  CHECK(std::equal_to<vecxr_t>()(v1, v2));
  vtkFormat::export_node_property("ppt_vtk.vtk", vec_ppt, "vec_ppt2", false);
  vtkFormat::load_scalar_property("ppt_vtk.vtk", vec_ppt_load, "vec_ppt2");
  vtkFormat::load_scalar_property("ppt_vtk.vtk", v3, "vec_ppt2");
  CHECK(std::equal_to<vecxr_t>()(v1, v2));
  CHECK(std::equal_to<vecxr_t>()(v1, v3));
  vtkFormat::export_node_property("ppt_vtk.vtk", v3, "v3", false);
  vtkFormat::load_scalar_property("ppt_vtk.vtk", vec_ppt_load, "v3");
  CHECK(std::equal_to<vecxr_t>()(v2, v3));
  //-> node vector ppt.
  std::vector<vecxr_t> vector_ppt(2), vector_ppt_load(2);
  vector_ppt[0] = vec3r_t{0, 0, 0};
  vector_ppt[1] = vec3r_t{0, 1, 0};
  vtkFormat::export_node_property("ppt_vtk.vtk", vector_ppt, "vector_ppt",
                                  false);
  vtkFormat::load_vector_property("ppt_vtk.vtk", vector_ppt_load, "vector_ppt");
  CHECK(std::equal_to<vecxr_t>()(vector_ppt[0], vector_ppt_load[0]));
  CHECK(std::equal_to<vecxr_t>()(vector_ppt[1], vector_ppt_load[1]));

  //-> cell property.
  std::vector<real_t> cell_ppt(1);
  cell_ppt[0] = 10;
  vtkFormat::export_cell_property("ppt_vtk.vtk", cell_ppt, "cell_ppt");
  std::vector<vecxr_t> cell_vector(1);
  cell_vector[0] = vec3r_t{0, 1, 0};
  vtkFormat::export_cell_property("ppt_vtk.vtk", cell_vector, "cell_vector",
                                  false);
}
