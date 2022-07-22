// #include "mapping/autodiff.h"

// #include <catch2/catch.hpp>

// #include "common/numerical.h"
// #include "common/pattern.h"
// #include "common/type.h"
// #include "common/type_helper.h"
// #include "mapping/data_filler.h"
// #include "utils/logger/logger.h"

// using namespace chaos;
// using namespace chaos::mapping;

// struct scalar_expected {
//   static real_t val(const Eigen::Ref<const vec_t<real_t>> &x) {
//     return x.squaredNorm();
//   }
//   static vecxr_t jac(const Eigen::Ref<const vec_t<real_t>> &x) { return 2 *
//   x; } static matxr_t hes(const Eigen::Ref<const vec_t<real_t>> &x) {
//     return matxr_t::Identity(x.size(), x.size()) * 2;
//   }
// };

// struct vector_expected {
//   static vecxr_t val(const Eigen::Ref<const vec_t<real_t>> &x) {
//     vecxr_t res(2);
//     res[0] = x.squaredNorm();
//     res[1] = x.sum();
//     return res;
//   }
//   static matxr_t jac(const Eigen::Ref<const vec_t<real_t>> &x) {
//     matxr_t J(2, x.size());
//     J.row(0) = 2 * x;
//     J.row(1).setOnes();
//     return J;
//   }
//   static matxr_t hes(const Eigen::Ref<const vec_t<real_t>> &x) {
//     matxr_t H(2 * x.size(), x.size());
//     H.setZero();
//     for (int i = 0; i < x.size(); ++i) {
//       H.col(i).reshaped(2, x.size())(0, i) = 2;
//     }
//     return H;
//   }
// };

// template <int Xdim>
// struct auto_poly_f : public autodiff_function_base<auto_poly_f<Xdim>, Xdim,
// 1> {
//   template <typename T>
//   T _mapsto(const Eigen::Ref<const vec_t<T>> &x) const {
//     return x.squaredNorm();
//   }
// };

// template <int Xdim>
// struct auto_vec_f : public autodiff_function_base<auto_vec_f<Xdim>, Xdim, 2>
// {
//   template <typename T>
//   vec_t<T, 2> _mapsto(const Eigen::Ref<const vec_t<T>> &x) const {
//     return vec_t<T, 2>(x.squaredNorm(), x.sum());
//   }
// };

// TEST_CASE("test autodiff for compile time xdim and fdim", "[mapping]") {
//   SECTION("real valued function") {
//     auto_poly_f<3> f;
//     vec3r_t x;
//     x.setRandom();
//     CHECK(f.Nx() == 3);
//     CHECK(f.Nf() == 1);
//     real_t val;
//     vec3r_t jac;
//     mat33r_t hes;

//     SECTION("independent.call") {
//       f.Val(one_dim_filler_t(val), x);
//       f.Jac(gra_filler_t(jac), x);
//       f.Hes(mat_filler_t(hes), x);
//       CHECK(numerical::near(val, scalar_expected::val(x)));
//       CHECK(std::equal_to<vecxr_t>()(jac, scalar_expected::jac(x)));
//       CHECK(std::equal_to<matxr_t>()(hes, scalar_expected::hes(x)));
//     }

//     SECTION("together.call") {
//       f.ValJacHes(one_dim_filler_t(val), gra_filler_t(jac),
//       mat_filler_t(hes),
//                   x);
//       CHECK(numerical::near(val, scalar_expected::val(x)));
//       CHECK(std::equal_to<vecxr_t>()(jac, scalar_expected::jac(x)));
//       CHECK(std::equal_to<matxr_t>()(hes, scalar_expected::hes(x)));
//     }

//     SECTION("valjac") {
//       f.ValJac(one_dim_filler_t(val), gra_filler_t(jac), x);
//       CHECK(numerical::near(val, scalar_expected::val(x)));
//       CHECK(std::equal_to<vecxr_t>()(jac, scalar_expected::jac(x)));
//     }

//     SECTION("jaches") {
//       f.JacHes(gra_filler_t(jac), mat_filler_t(hes), x);
//       CHECK(std::equal_to<vecxr_t>()(jac, scalar_expected::jac(x)));
//       CHECK(std::equal_to<matxr_t>()(hes, scalar_expected::hes(x)));
//     }
//   }
//   SECTION("vector valued function") {
//     auto_vec_f<3> f;
//     CHECK(f.Nx() == 3);
//     CHECK(f.Nf() == 2);

//     vec3r_t x;
//     x.setRandom();
//     vec2r_t y;
//     y.setRandom();
//     matxr_t jac;
//     matxr_t hes;
//     jac.resize(2, 3);
//     hes.resize(6, 3);

//     SECTION("independent.call") {
//       f.Val(one_dim_filler_t(y), x);
//       f.Jac(mat_filler_t(jac), x);
//       f.Hes(mat_filler_t(hes), x);
//       CHECK(std::equal_to<vecxr_t>()(y, vector_expected::val(x)));
//       CHECK(std::equal_to<matxr_t>()(jac, vector_expected::jac(x)));
//       CHECK(std::equal_to<matxr_t>()(hes, vector_expected::hes(x)));
//     }
//     SECTION("together.call") {
//       f.ValJacHes(one_dim_filler_t(y), mat_filler_t(jac), mat_filler_t(hes),
//       x); CHECK(std::equal_to<vecxr_t>()(y, vector_expected::val(x)));
//       CHECK(std::equal_to<matxr_t>()(jac, vector_expected::jac(x)));
//       CHECK(std::equal_to<matxr_t>()(hes, vector_expected::hes(x)));
//     }
//     SECTION("valjac") {
//       f.ValJac(one_dim_filler_t(y), mat_filler_t(jac), x);
//       CHECK(std::equal_to<vecxr_t>()(y, vector_expected::val(x)));
//       CHECK(std::equal_to<matxr_t>()(jac, vector_expected::jac(x)));
//     }
//     SECTION("jaches") {
//       f.JacHes(mat_filler_t(jac), mat_filler_t(hes), x);
//       CHECK(std::equal_to<matxr_t>()(jac, vector_expected::jac(x)));
//       CHECK(std::equal_to<matxr_t>()(hes, vector_expected::hes(x)));
//     }
//   }
// }

// template <>
// struct auto_poly_f<-1> : public autodiff_function_base<auto_poly_f<-1>, -1,
// 1> {
//   auto_poly_f(int xdim) : _xdim(xdim) {}

//   index_t _nx_impl() const { return _xdim; }

//   template <typename T>
//   T _mapsto(const Eigen::Ref<const vec_t<T>> &x) const {
//     return x.squaredNorm();
//   }

//  private:
//   index_t _xdim;
// };

// template <>
// struct auto_vec_f<-1> : public autodiff_function_base<auto_vec_f<-1>, -1, -1>
// {
//   auto_vec_f(int xdim) : _xdim(xdim) {}

//   index_t _nx_impl() const { return _xdim; }
//   constexpr index_t _nf_impl() const { return 2; }

//   template <typename T>
//   vec_t<T> _mapsto(const Eigen::Ref<const vec_t<T>> &x) const {
//     vec_t<T> res;
//     res.resize(2);
//     res[0] = x.squaredNorm();
//     res[1] = x.sum();
//     return res;
//   }

//  private:
//   index_t _xdim;
// };

// TEST_CASE("test autodiff for dynamic xdim and fdim", "[mapping]") {
//   SECTION("real valued function") {
//     auto_poly_f<-1> f(3);
//     vec3r_t x;
//     x.setRandom();
//     CHECK(f.Nx() == 3);
//     CHECK(f.Nf() == 1);
//     real_t val;
//     vec3r_t jac;
//     mat33r_t hes;

//     SECTION("independent.call") {
//       f.Val(one_dim_filler_t(val), x);
//       f.Jac(gra_filler_t(jac), x);
//       f.Hes(mat_filler_t(hes), x);
//       CHECK(numerical::near(val, scalar_expected::val(x)));
//       CHECK(std::equal_to<vecxr_t>()(jac, scalar_expected::jac(x)));
//       CHECK(std::equal_to<matxr_t>()(hes, scalar_expected::hes(x)));
//     }

//     SECTION("together.call") {
//       f.ValJacHes(one_dim_filler_t(val), gra_filler_t(jac),
//       mat_filler_t(hes),
//                   x);
//       CHECK(numerical::near(val, scalar_expected::val(x)));
//       CHECK(std::equal_to<vecxr_t>()(jac, scalar_expected::jac(x)));
//       CHECK(std::equal_to<matxr_t>()(hes, scalar_expected::hes(x)));
//     }

//     SECTION("valjac") {
//       f.ValJac(one_dim_filler_t(val), gra_filler_t(jac), x);
//       CHECK(numerical::near(val, scalar_expected::val(x)));
//       CHECK(std::equal_to<vecxr_t>()(jac, scalar_expected::jac(x)));
//     }

//     SECTION("jaches") {
//       f.JacHes(gra_filler_t(jac), mat_filler_t(hes), x);
//       CHECK(std::equal_to<vecxr_t>()(jac, scalar_expected::jac(x)));
//       CHECK(std::equal_to<matxr_t>()(hes, scalar_expected::hes(x)));
//     }
//   }
//   SECTION("vector valued function") {
//     auto_vec_f<-1> f(3);
//     CHECK(f.Nx() == 3);
//     CHECK(f.Nf() == 2);

//     vec3r_t x;
//     x.setRandom();
//     vec2r_t y;
//     y.setRandom();
//     matxr_t jac;
//     matxr_t hes;
//     jac.resize(2, 3);
//     hes.resize(6, 3);

//     SECTION("independent.call") {
//       f.Val(one_dim_filler_t(y), x);
//       f.Jac(mat_filler_t(jac), x);
//       f.Hes(mat_filler_t(hes), x);
//       CHECK(std::equal_to<vecxr_t>()(y, vector_expected::val(x)));
//       CHECK(std::equal_to<matxr_t>()(jac, vector_expected::jac(x)));
//       CHECK(std::equal_to<matxr_t>()(hes, vector_expected::hes(x)));
//     }
//     SECTION("together.call") {
//       f.ValJacHes(one_dim_filler_t(y), mat_filler_t(jac), mat_filler_t(hes),
//       x); CHECK(std::equal_to<vecxr_t>()(y, vector_expected::val(x)));
//       CHECK(std::equal_to<matxr_t>()(jac, vector_expected::jac(x)));
//       CHECK(std::equal_to<matxr_t>()(hes, vector_expected::hes(x)));
//     }
//     SECTION("valjac") {
//       f.ValJac(one_dim_filler_t(y), mat_filler_t(jac), x);
//       CHECK(std::equal_to<vecxr_t>()(y, vector_expected::val(x)));
//       CHECK(std::equal_to<matxr_t>()(jac, vector_expected::jac(x)));
//     }
//     SECTION("jaches") {
//       f.JacHes(mat_filler_t(jac), mat_filler_t(hes), x);
//       CHECK(std::equal_to<matxr_t>()(jac, vector_expected::jac(x)));
//       CHECK(std::equal_to<matxr_t>()(hes, vector_expected::hes(x)));
//     }
//   }
// }
