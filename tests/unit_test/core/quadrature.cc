#include "core/quadrature/quadrature.h"

#include <catch2/catch.hpp>

#include "common/numerical.h"
#include "common/type.h"
using namespace chaos;

TEST_CASE("test quadrature area", "[quadrature]") {
  using namespace numerical;
  quadrature_factory::params_t prm;
  prm.type.set_val(quadrature_factory::LINE);
  prm.order.set_val(1);
  CHECK(near<real_t>(quadrature_factory::create(prm)->W.sum(), 1));
  prm.type.set_val(quadrature_factory::QUAD);
  CHECK(near<real_t>(quadrature_factory::create(prm)->W.sum(), 1));
  prm.type.set_val(quadrature_factory::TRI);
  CHECK(near<real_t>(quadrature_factory::create(prm)->W.sum(), 1.0 / 2));
  prm.type.set_val(quadrature_factory::HEX);
  CHECK(near<real_t>(quadrature_factory::create(prm)->W.sum(), 1));
  prm.type.set_val(quadrature_factory::TET);
  CHECK(near<real_t>(quadrature_factory::create(prm)->W.sum(), 1.0 / 6));
  prm.type.set_val(quadrature_factory::WEDGE);
  CHECK(near<real_t>(quadrature_factory::create(prm)->W.sum(), 1.0 / 2));
  prm.type.set_val(quadrature_factory::PYRAMID);
  CHECK(near<real_t>(quadrature_factory::create(prm)->W.sum(), 1.0 / 3));
}

TEST_CASE("gauss quadrature on line", "[quadrature]") {
  class poly_f {
   public:
    poly_f(int n) : n(n) {}
    real_t val(real_t x) const {
      real_t res = 1;
      for (int i = 0; i < n; ++i) {
        res *= x;
      }
      return res;
    }
    real_t integral_on_0_1() const { return 1.0 / (n + 1); }

   private:
    int n;
  };

  const auto &gauss_integral = [](int degree, const poly_f &f) {
    auto qdrt = quadrature_factory::create(quadrature_factory::LINE, degree);
    real_t res = 0;
    for (size_t i = 0; i < qdrt->num(); ++i) {
      res += qdrt->weight(i) * f.val(qdrt->at(i)[0]);
    }
    return res;
  };

  int i;
  for (i = 0; i <= 21; ++i) {
    poly_f f(i);
    CHECK(numerical::near(f.integral_on_0_1(), gauss_integral(i, f)));
  }
  CHECK_THROWS(quadrature_factory::create(quadrature_factory::LINE, i));
}

TEST_CASE("quadrature prm", "[quadrature]") {
  quadrature_factory::params_t prm;
  CHECK(prm.order.set_val(-1) == false);
  CHECK(prm.order.set_val(0));
  CHECK(prm.type.set_val(quadrature_factory::LINE));
  CHECK(prm.type.set_val(quadrature_factory::TRI));
  CHECK(prm.type.set_val(quadrature_factory::QUAD));
  CHECK(prm.type.set_val(quadrature_factory::TET));
  CHECK(prm.type.set_val(quadrature_factory::WEDGE));
  CHECK(prm.type.set_val(quadrature_factory::PYRAMID));
  CHECK(prm.type.set_val(quadrature_factory::HEX));
}

TEST_CASE("quadrature qdrt", "[quadrature]") {
  auto qdrt = quadrature_factory::create(quadrature_factory::LINE, 1);
  CHECK(qdrt->dim() == 1);
  qdrt = quadrature_factory::create(quadrature_factory::TRI, 1);
  CHECK(qdrt->dim() == 2);
  qdrt = quadrature_factory::create(quadrature_factory::QUAD, 1);
  CHECK(qdrt->dim() == 2);
  qdrt = quadrature_factory::create(quadrature_factory::TET, 1);
  CHECK(qdrt->dim() == 3);
  qdrt = quadrature_factory::create(quadrature_factory::HEX, 1);
  CHECK(qdrt->dim() == 3);
  qdrt = quadrature_factory::create(quadrature_factory::WEDGE, 1);
  CHECK(qdrt->dim() == 3);
  qdrt = quadrature_factory::create(quadrature_factory::PYRAMID, 1);
  CHECK(qdrt->dim() == 3);
  CHECK_THROWS(
      quadrature_factory::create(quadrature_factory::cell_type(-1), 1));
}

TEST_CASE("quadrature on tri", "[quadrature_factory::tri]") {
  class test_f {
   public:
    test_f(int n, int i) : n(n), i(i) {}
    real_t val(const Eigen::Ref<const vecxr_t> &x) const {
      return val(x[0], x[1]);
    }
    real_t val(real_t x, real_t y) const {
      //-> x^i * y^(n-i)
      return pow(x, i) * pow(y, n - i);
    }

    real_t integral_on_tri() const {
      auto qdrt = quadrature_factory::create(quadrature_factory::LINE, n + 1);
      real_t res = 0;
      for (size_t i = 0; i < qdrt->num(); ++i) {
        real_t x = qdrt->at(i)[0];
        res += qdrt->weight(i) * val(x, 1 - x) * (1 - x);
      }
      return res / (n - i + 1);
    }
    int n, i;
  };

  const auto &gauss_integral = [](int degree, const test_f &f) {
    auto qdrt = quadrature_factory::create(quadrature_factory::TRI, degree);
    real_t res = 0;
    for (size_t i = 0; i < qdrt->num(); ++i) {
      res += qdrt->weight(i) * f.val(qdrt->at(i));
    }
    return res;
  };

  for (int n = 0; n <= 20; ++n) {
    for (int i = 0; i <= n; ++i) {
      test_f f(n, i);
      CHECK(numerical::near(f.integral_on_tri(), gauss_integral(n, f)));
    }
  }
  test_f f(21, 0);
  CHECK_THROWS(gauss_integral(21, f));
}

TEST_CASE("quadrature on tet", "[quadrature_factory::tet]") {
  class test_f {
   public:
    test_f(int n, int i, int j) : n(n), i(i), j(j) {}
    real_t val(const Eigen::Ref<const vecxr_t> &x) const {
      return val(x[0], x[1], x[2]);
    }
    real_t val(real_t x, real_t y, real_t z) const {
      //-> x^i * y^j * z^(n-i-j)
      return pow(x, i) * pow(y, j) * pow(z, n - i - j);
    }

    real_t integral_on_tet() const {
      auto qdrt = quadrature_factory::create(quadrature_factory::HEX, n + 2);
      real_t res = 0;
      const auto tmp_val = [&](const Eigen::Ref<const vecxr_t> &x) {
        return pow(x[0], i) * pow(1 - x[0], 2 + n - i) * pow(x[1], j) *
               pow(1 - x[1], n - i - j + 1) * pow(x[2], n - i - j);
      };
      for (size_t i = 0; i < qdrt->num(); ++i) {
        res += qdrt->weight(i) * tmp_val(qdrt->at(i));
      }
      return res;
    }
    int n, i, j;
  };
  const auto &gauss_integral = [](int degree, const test_f &f) {
    auto qdrt = quadrature_factory::create(quadrature_factory::TET, degree);
    real_t res = 0;
    for (size_t i = 0; i < qdrt->num(); ++i) {
      res += qdrt->weight(i) * f.val(qdrt->at(i));
    }
    return res;
  };
  for (int n = 0; n <= 14; ++n) {
    for (int i = 0; i <= n; ++i) {
      for (int j = 0; i + j <= n; ++j) {
        test_f f(n, i, j);
        CHECK(numerical::near(f.integral_on_tet(), gauss_integral(n, f)));
      }
    }
  }
  test_f f(15, 0, 0);
  CHECK_THROWS(gauss_integral(15, f));
}
