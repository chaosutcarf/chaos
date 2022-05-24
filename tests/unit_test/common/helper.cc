#include <catch2/catch.hpp>
#include <functional>
#include <initializer_list>
#include <iostream>
#include <list>
#include <queue>
#include <ratio>
#include <vector>

#include "common/numerical.h"
#include "common/range_helper.h"
#include "common/type.h"
#include "common/type_helper.h"

using namespace chaos;
using namespace chaos::common;
using namespace std;

TEMPLATE_TEST_CASE("test type helper to_vec", "[common]", float, double, int) {
#define DATA_ 1, 2, 3, 4, 5
  vec_t<TestType> ref(5);
  ref << DATA_;

  SECTION("initialize list") {
    const auto cmp{to_vec<TestType>({DATA_})};
    CHECK(numerical::is_zero((ref - cmp).norm()));
  }

#define TEST_TYPE(type)                            \
  SECTION(#type) {                                 \
    type<TestType> data{DATA_};                    \
    const auto cmp{to_vec<TestType>(data)};        \
    CHECK(numerical::is_zero((ref - cmp).norm())); \
  }

  TEST_TYPE(vector);
  TEST_TYPE(initializer_list);
  TEST_TYPE(list);

#undef DATA_
#undef TEST_TYPE
}

TEMPLATE_TEST_CASE("test type helper spm_to_tpl", "[common]", float, double,
                   int) {
#define TEST_LAYOUT(Layout)                                                  \
  {                                                                          \
    tpl_list_t<TestType> coo;                                                \
    coo.emplace_back(0, 0, 1);                                               \
    coo.emplace_back(1, 0, 2);                                               \
    coo.emplace_back(1, 1, 3);                                               \
    sp_mat_t<TestType, Layout> spm(2, 2);                                    \
    spm.setFromTriplets(coo.begin(), coo.end());                             \
    auto spm1 = tpl_to_spm<TestType, sp_mat_t<TestType, Layout>>(2, 2, coo); \
    auto spm2 = tpl_to_spm<TestType, sp_mat_t<TestType, Layout>>(2, coo);    \
    CHECK(numerical::is_zero(                                                \
        ((mat_t<TestType>)(spm - spm1)).cwiseAbs2().maxCoeff()));            \
    CHECK(numerical::is_zero(                                                \
        ((mat_t<TestType>)(spm - spm2)).cwiseAbs2().maxCoeff()));            \
    auto tpl = spm_to_tpl<TestType>(spm);                                    \
    CHECK(tpl.size() == coo.size());                                         \
    auto spm3 = tpl_to_spm<TestType, sp_mat_t<TestType, Layout>>(2, tpl);    \
    CHECK(numerical::is_zero(                                                \
        ((mat_t<TestType>)(spm - spm3)).cwiseAbs2().maxCoeff()));            \
  }

  TEST_LAYOUT(Eigen::RowMajor);
  TEST_LAYOUT(Eigen::ColMajor);
#undef TEST_LAYOUT
}

TEMPLATE_TEST_CASE("test type helper hash/equal", "[common]", float, double,
                   int) {
#define DATA1_ 1, 2, 3, 4, 5, 6
#define DATA2_ 7, 8, 9, 10, 11, 12

  auto hasher = std::hash<vec_t<TestType>>();
  auto fixed_hasher = std::hash<vec_t<TestType, 6>>();
  auto equal = std::equal_to<vec_t<TestType>>();
  auto mat_equal = std::equal_to<mat_t<TestType>>();
  vec_t<TestType> v1(6), v2(6), v3(6);
  mat_t<TestType, 3, 2> m1, m2, m3;
  mat_t<TestType, 2, 3> m4;
  m1 << DATA1_;
  m2 << DATA2_;
  m3 << DATA1_;
  m4 << DATA1_;
  v1 << DATA1_;
  v2 << DATA2_;
  v3 << DATA1_;

  CHECK(hasher(v1) != hasher(v2));
  CHECK(hasher(v1) == hasher(v3));
  CHECK(fixed_hasher(v1) != fixed_hasher(v2));
  CHECK(fixed_hasher(v1) == fixed_hasher(v3));
  CHECK(!equal(v1, v2));
  CHECK(equal(v1, v3));
  CHECK(!mat_equal(m1, m2));
  CHECK(mat_equal(m1, m3));
  CHECK(!mat_equal(m1, m4));

#undef DATA1_
#undef DATA2_
}

TEMPLATE_TEST_CASE("test range helper join", "[common]", float, double, int) {
#define DATA1_ 1, 2, 3, 4, 5
#define DATA2_ 6, 7, 8, 9, 10
#define DATA3_ -1, -2, -3, -4, -5

  vec_t<TestType> ref(15);
  ref << DATA1_, DATA2_, DATA3_;

  SECTION("initialize list") {
    const auto& res = join<TestType>({{DATA1_}, {DATA2_}, {DATA3_}});
    const auto& cmp{to_vec<TestType>(res)};
    CHECK(numerical::is_zero((ref - cmp).norm()));
  }

#define TEST_TYPE(type)                             \
  SECTION(#type) {                                  \
    type<TestType> t1{DATA1_};                      \
    type<TestType> t2{DATA2_};                      \
    type<TestType> t3{DATA3_};                      \
    const auto& res = join<TestType>({t1, t2, t3}); \
    const auto& cmp{to_vec<TestType>(res)};         \
    CHECK(numerical::is_zero((ref - cmp).norm()));  \
  }

  TEST_TYPE(vector);
  TEST_TYPE(initializer_list);
  TEST_TYPE(list);

#undef DATA1_
#undef DATA2_
#undef DATA3_
#undef TEST_TYPE
}

TEMPLATE_TEST_CASE("test Vector of Vector <--> NXMatrix", "[common]", float,
                   double, int) {
#define ROW1_DATA_ 1, 2, 3
#define ROW2_DATA_ 4, 5, 6

  std::vector<std::vector<TestType>> vecofvec;
  mat_t<TestType> mat;

  SECTION("Vector of Vector to NXMatrix") {
    mat_t<TestType> refMat(2, 3);
    refMat << ROW1_DATA_, ROW2_DATA_;
    vecofvec.emplace_back(std::vector<TestType>{ROW1_DATA_});
    vecofvec.emplace_back(std::vector<TestType>{ROW2_DATA_});
    mat = toNXMatrix(vecofvec);
    CHECK(std::equal_to<mat_t<TestType>>()(mat, refMat.transpose()));
  }

  SECTION("NXMatrix to Vector of Vector") {
    mat.resize(2, 3);
    mat << ROW1_DATA_, ROW2_DATA_;
    std::vector<std::vector<TestType>> refVecOfVec;
    refVecOfVec.emplace_back(std::vector<TestType>{ROW1_DATA_});
    refVecOfVec.emplace_back(std::vector<TestType>{ROW2_DATA_});
    vecofvec = fromNXMatrix<TestType>(mat.transpose());
    CHECK(vecofvec.size() == refVecOfVec.size());
    CHECK(vecofvec[0].size() == refVecOfVec[0].size());
    CHECK(std::equal_to()(to_vec<TestType>(vecofvec[0]),
                          to_vec<TestType>(refVecOfVec[0])));
    CHECK(std::equal_to()(to_vec<TestType>(vecofvec[1]),
                          to_vec<TestType>(refVecOfVec[1])));
  }

  SECTION("Vector of Vector to NXMatrix Failed Case") {
    CHECK(!toNXMatrix(vecofvec, mat));
    vecofvec.emplace_back(std::vector<TestType>{ROW1_DATA_, ROW2_DATA_});
    vecofvec.emplace_back(std::vector<TestType>{ROW1_DATA_});
    CHECK(!toNXMatrix(vecofvec, mat));
  }

#undef ROW1_DATA_
#undef ROW2_DATA_
}
