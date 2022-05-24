#include <catch2/catch.hpp>
#include <type_traits>

#include "common/numerical.h"
#include "common/pattern.h"
#include "common/type.h"

using namespace chaos;
using namespace chaos::numerical;
using namespace std;
using namespace Eigen;

template <typename T1, typename T2>
static inline void type_same_check() {
  CHECK(is_same<T1, T2>::value);
}

TEMPLATE_TEST_CASE("test type exists", "[common]", int, float, double) {
  type_same_check<coo_t<TestType>, Triplet<TestType>>();
  type_same_check<tpl_t<TestType>, Triplet<TestType>>();
  type_same_check<coo_list_t<TestType>, std::vector<Triplet<TestType>>>();
  type_same_check<tpl_list_t<TestType>, std::vector<Triplet<TestType>>>();
  type_same_check<sp_mat_t<TestType, RowMajor>,
                  SparseMatrix<TestType, RowMajor>>();
  type_same_check<sp_mat_t<TestType, ColMajor>,
                  SparseMatrix<TestType, ColMajor>>();
  type_same_check<sp_vec_t<TestType>, SparseVector<TestType>>();
  type_same_check<mat_t<TestType, Dynamic, Dynamic>,
                  Matrix<TestType, Dynamic, Dynamic>>();
  type_same_check<vec_t<TestType, Dynamic>, Matrix<TestType, Dynamic, 1>>();
  type_same_check<qtn_t<TestType>, Quaternion<TestType>>();
}

TEST_CASE("test common type defs", "[common]") {
  type_same_check<mat22r_t, Matrix<real_t, 2, 2, ColMajor>>();
  type_same_check<mat33r_t, Matrix<real_t, 3, 3, ColMajor>>();
  type_same_check<mat44r_t, Matrix<real_t, 4, 4, ColMajor>>();

  type_same_check<mat2xr_t, Matrix<real_t, 2, -1, ColMajor>>();
  type_same_check<mat3xr_t, Matrix<real_t, 3, -1, ColMajor>>();
  type_same_check<mat4xr_t, Matrix<real_t, 4, -1, ColMajor>>();
  type_same_check<matx2r_t, Matrix<real_t, -1, 2, ColMajor>>();
  type_same_check<matx3r_t, Matrix<real_t, -1, 3, ColMajor>>();
  type_same_check<matx4r_t, Matrix<real_t, -1, 4, ColMajor>>();
  type_same_check<matxr_t, Matrix<real_t, -1, -1, ColMajor>>();

  type_same_check<mat22i_t, Matrix<int, 2, 2, ColMajor>>();
  type_same_check<mat33i_t, Matrix<int, 3, 3, ColMajor>>();
  type_same_check<mat44i_t, Matrix<int, 4, 4, ColMajor>>();

  type_same_check<mat2xi_t, Matrix<int, 2, -1, ColMajor>>();
  type_same_check<mat3xi_t, Matrix<int, 3, -1, ColMajor>>();
  type_same_check<mat4xi_t, Matrix<int, 4, -1, ColMajor>>();
  type_same_check<matx2i_t, Matrix<int, -1, 2, ColMajor>>();
  type_same_check<matx3i_t, Matrix<int, -1, 3, ColMajor>>();
  type_same_check<matx4i_t, Matrix<int, -1, 4, ColMajor>>();
  type_same_check<matxi_t, Matrix<int, -1, -1, ColMajor>>();

  type_same_check<vec2r_t, Matrix<real_t, 2, 1>>();
  type_same_check<vec3r_t, Matrix<real_t, 3, 1>>();
  type_same_check<vec4r_t, Matrix<real_t, 4, 1>>();
  type_same_check<vecxr_t, Matrix<real_t, -1, 1>>();

  type_same_check<vec2i_t, Matrix<int, 2, 1>>();
  type_same_check<vec3i_t, Matrix<int, 3, 1>>();
  type_same_check<vec4i_t, Matrix<int, 4, 1>>();
  type_same_check<vecxi_t, Matrix<int, -1, 1>>();

  type_same_check<csr_matr_t, SparseMatrix<real_t, RowMajor>>();
  type_same_check<csc_matr_t, SparseMatrix<real_t, ColMajor>>();
  type_same_check<csr_mati_t, SparseMatrix<int, RowMajor>>();
  type_same_check<csc_mati_t, SparseMatrix<int, ColMajor>>();

  type_same_check<sp_vecr_t, SparseVector<real_t>>();
  type_same_check<sp_veci_t, SparseVector<int>>();
}

TEST_CASE("test pattern", "[common]") {
  class noncopy_A {
    DECLARE_NON_COPYABLE(noncopy_A);
  };

  class nonmove_A {
    DECLARE_NON_MOVEABLE(nonmove_A);
  };

  class single_A {
    DECLARE_SINGLETON(single_A, NIL_FUNC);

   public:
    int eval() { return 0; }
  };

  class lazy_single_A {
    DECLARE_LAZY_SINGLETON(lazy_single_A, NIL_FUNC);

   public:
    int eval() { return 1; }
  };

  class single_A_with_init {
    DECLARE_SINGLETON(single_A_with_init, printf, "decl\n");

   public:
    int eval() { return 2; }
  };

  CHECK(!is_copy_constructible<noncopy_A>::value);
  CHECK(!is_copy_assignable<noncopy_A>::value);

  CHECK(!is_move_constructible<nonmove_A>::value);
  CHECK(!is_move_assignable<nonmove_A>::value);

  CHECK(!is_copy_constructible<single_A>::value);
  CHECK(!is_copy_assignable<single_A>::value);

  CHECK(!is_copy_constructible<lazy_single_A>::value);
  CHECK(!is_copy_assignable<lazy_single_A>::value);

  CHECK(!is_copy_constructible<single_A_with_init>::value);
  CHECK(!is_copy_assignable<single_A_with_init>::value);

  //-> call the singleton by this way.
  auto& ins = single_A::instance();
  auto& ins_lazy = lazy_single_A::instance();
  auto& ins_with_init = single_A_with_init::instance();
  CHECK(ins.eval() == 0);
  CHECK(single_A::instance().eval() == 0);
  CHECK(ins_lazy.eval() == 1);
  CHECK(lazy_single_A::instance().eval() == 1);
  CHECK(ins_with_init.eval() == 2);
  CHECK(single_A_with_init::instance().eval() == 2);
}

template <typename T>
class flyable {
 public:
  std::string fly() { return "[base]" + static_cast<T*>(this)->fly_impl(); }
};

// clang-format off
CRTPclass(bird_t, flyable) {
public:
  std::string fly_impl() {
    return "bird";
  }
};

CRTPclass(eagle_t, flyable) {
public:
  std::string fly_impl() {
    return "eagle";
  }
};
// clang-format on

TEST_CASE("test crtp pattern", "[common]") {
  flyable<bird_t> o1;
  flyable<eagle_t> o2;
  CHECK(o1.fly() == "[base]bird");
  CHECK(o2.fly() == "[base]eagle");
}

TEST_CASE("test numerical constant", "[common]") {
  CHECK(constant<double>::golden_ratio == GOLDEN_RATIO_64);
  CHECK(constant<float>::golden_ratio == GOLDEN_RATIO_32);
  CHECK(constant<double>::golden_ratio_prime == GOLDEN_RATIO_PRIME_64);
  CHECK(constant<float>::golden_ratio_prime == GOLDEN_RATIO_PRIME_32);
  CHECK(near(constant<double>::pi, PI));
  CHECK(near<float>(constant<float>::pi, PI));
  CHECK(constant<double>::precision == 15);
  CHECK(constant<float>::precision == 6);
}

TEST_CASE("test numerical helper function", "[common]") {
  CHECK(near(HALF_PI, PI / 2));
  CHECK(near(TWO_PI, PI * 2));
  CHECK(near(PI_OVER_180, PI / 180));
  CHECK(near(degree2rad(180), PI));
  CHECK(near(rad2degree(PI), 180.0));
}

TEMPLATE_TEST_CASE("test numerical basic usage", "[common]", double, float) {
  CHECK(constant<int>::eps == 0);
  CHECK(is_zero(constant<TestType>::eps / 10));

  // First create an instance of an engine.
  std::random_device rnd_device;
  // Specify the engine and distribution.
  std::mt19937 mersenne_engine{rnd_device()};  // Generates random integers
  constexpr size_t cases_num{100000};
  std::vector<TestType> cases(cases_num);

  SECTION("test random number in [eps, 1]") {
    std::uniform_real_distribution<TestType> dist{constant<TestType>::eps, 1};
    const auto& gen{
        [&dist, &mersenne_engine]() { return dist(mersenne_engine); }};
    std::generate(cases.begin(), cases.end(), gen);
    for (const auto& c : cases) {
      CHECK(near(c + constant<TestType>::eps / 2, c));
    }
  }

  SECTION("test random number in [1, 1e7]") {
    std::uniform_real_distribution<TestType> dist{1, 1e7};
    const auto& gen{
        [&dist, &mersenne_engine]() { return dist(mersenne_engine); }};
    std::generate(cases.begin(), cases.end(), gen);
    for (const auto& c : cases) {
      CHECK(near(c + constant<TestType>::eps / 2, c));
    }
  }
}
