// #include "common/type.h"
// #include "mapping/autodiff.h"
// #include "mapping/data_filler.h"
// #include "utils/stopwatch/stopwatch.h"
// using namespace chaos;
// using namespace chaos::mapping;
// struct poly_f : public chaos::mapping::autodiff_function_base<poly_f, 3, 1> {
//   template <typename T>
//   inline T mapsto(const Eigen::Ref<const vec_t<T, 3>> &x) const {
//     return x.squaredNorm();
//   }
// };

// struct poly_f2 : public chaos::mapping::autodiff_function_base<poly_f2, 3, 2> {
//   template <typename T>
//   inline vec_t<T, 2> mapsto(const Eigen::Ref<const vec_t<T, 3>> &x) const {
//     return vec_t<T, 2>(x.squaredNorm(), x.squaredNorm() * x.sum());
//   }
// };

// // struct scalar_filler_t : public mapping::one_dim_filler_base<scalar_filler_t>
// // {
// //   scalar_filler_t(real_t &data) : data(data) {}
// //   inline index_t size() const { return 1; }
// //   inline void _fill_impl(index_t, real_t val) { data = val; }

// //  private:
// //   real_t &data;
// // };

// // template <typename T>
// // struct vector_filler_t
// //     : public mapping::one_dim_filler_base<vector_filler_t<T>> {
// //   vector_filler_t(T &data) : data(data) {}
// //   inline void _fill_impl(index_t pos, real_t val) { data[pos] = val; }
// //   inline index_t size() const { return data.size(); }

// //  private:
// //   T &data;
// // };

// // template <typename T>
// // struct gra_filler_t : public mapping::two_dim_filler_base<gra_filler_t<T>> {
// //   gra_filler_t(T &data) : data(data) {}
// //   inline void _fill_impl(index_t, index_t q, real_t val) { data[q] = val; }
// //   inline index_t rows() const { return 1; }
// //   inline index_t cols() const { return data.size(); }

// //  private:
// //   T &data;
// // };

// // template <typename Filler>
// // struct off_filler_t
// //     : public mapping::two_dim_filler_base<off_filler_t<Filler>> {
// //   off_filler_t(Filler &&filler) : filler(std::forward<Filler>(filler)) {}
// //   inline void _fill_impl(index_t p, index_t q, real_t val) {
// //     filler.fill(p, q + 2, val);
// //   }
// //   inline index_t rows() const { return filler.rows(); }
// //   inline index_t cols() const { return filler.cols() - 2; }

// //  private:
// //   Filler &&filler;
// // };

// // template <typename T>
// // struct mat_filler_t : public mapping::two_dim_filler_base<mat_filler_t<T>> {
// //   mat_filler_t(T &data) : data(data) {}
// //   inline index_t rows() const { return data.rows(); }
// //   inline index_t cols() const { return data.cols(); }
// //   inline void _fill_impl(index_t p, index_t q, real_t val) { data(p, q) =
// //   val; }

// //  private:
// //   T &data;
// // };

// int main(int argc, char *argv[]) {
//   if (1) {
//     poly_f f;
//     vec3r_t x;
//     matxr_t G(2, 3);
//     matxr_t H(3, 3);
//     G.setOnes();
//     x.setRandom();
//     real_t data;
//     f.Val(one_dim_filler_t<decltype(data)>(data), x);
//     auto Grow0 = G.row(0);
//     f.Jac(mat_filler_t<decltype(Grow0)>(Grow0), x);
//     f.Hes(mat_filler_t<decltype(H)>(H), x);
//     info_msg("x: {}", x);
//     info_msg("g: {}", G);
//     info_msg("H : \n{}", H);
//   }  // else {
//   //   poly_f2 g;
//   //   vec3r_t x;
//   //   x.setRandom();
//   //   vec2r_t res;
//   //   matxr_t jac;
//   //   matxr_t H;

//   //   jac.resize(2, 3);
//   //   H.resize(6, 3);
//   //   // g.Val(vector_filler_t(res), x);
//   //   // g.Jac(mat_filler_t(jac), x);
//   //   // info_msg("x: {}", x);
//   //   // info_msg("val: {}", res);
//   //   // info_msg("{}, {}", x.sum(), x.squaredNorm());
//   //   // info_msg("jac: {}", jac);
//   //   g.ValJacHes(vector_filler_t(res), mat_filler_t(jac), mat_filler_t(H), x);
//   //   info_msg("hes: \n{}", H);
//   //   info_msg("val: \n{}", res);
//   //   info_msg("jac: \n{}", jac);
//   //   utils::STW_START("val.jac");
//   //   for (size_t i = 0; i < 10000; ++i) {
//   //     g.Val(vector_filler_t(res), x);
//   //     g.Jac(mat_filler_t(jac), x);
//   //     // g.ValJac(vector_filler_t(res), mat_filler_t(jac), x);
//   //   }
//   //   utils::STW_STOP("val.jac");
//   //   info_msg("val: {}", res);
//   //   info_msg("jac: {}", jac);
//   // }
//   return 0;
// }
