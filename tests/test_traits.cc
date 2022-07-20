// #include <type_traits>
// #include <utility>

// #include "common/type.h"
// #include "common/type_traits.h"
// #include "mapping/data_filler.h"
// #include "mapping/data_filler_traits.h"
// #include "mapping/function.h"
// #include "mapping/function_traits.h"
// struct B {};
// using namespace chaos::mapping;
// struct C {
//   static constexpr bool override_mode = false;
//   static constexpr int xdim = 1;
// };

// struct A : public C {
//   static B fill_mode;
//   template <typename D, typename _ = double,
//             std::enable_if_t<std::is_same_v<_, B>, bool> = true>
//   void _fill(D &&v);
//   template <bool _ = override_mode, std::enable_if_t<_ == true, bool> = true>
//   chaos::real_t *data() {
//     return nullptr;
//   }
// };

// template <typename T>
// class has_fill {
//   template <typename U>
//   using impl_t =
//       decltype(std::declval<const U &>().template fill<Eigen::MatrixXd>(
//           std::declval<Eigen::MatrixXd>()));

//  public:
//   static constexpr bool value =
//       std::is_same_v<chaos::detected_t<impl_t, T>, void>;
// };

// int main(int argc, char *argv[]) {
//   printf("%u\n", details::function_traits::get_xdim<A>());
//   // chaos::matxr_t mat;
//   // chaos::mapping::one_dim_filler_t a(val);
//   // chaos::mapping::override_lower_mat_filler_t b(mat);
//   // if constexpr (chaos::mapping::details::data_filler_traits::
//   //                   has_data_v<A>) {
//   //   printf("yes");
//   // }
//   // printf("%d\n",sizeof(A));

//   // A a;
//   // a.data();
//   // a.data();

//   return 0;
// }
