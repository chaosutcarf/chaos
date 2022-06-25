#pragma once

#include <type_traits>

#include "common/type.h"
#include "common/type_traits.h"

namespace chaos::mapping::details::data_filler_traits {

#define const_interface_no_args(op)                            \
  template <typename T>                                        \
  class has_##op {                                             \
    template <typename U>                                      \
    using impl_t = decltype(std::declval<const U &>().op());   \
                                                               \
   public:                                                     \
    static constexpr bool value =                              \
        std::is_convertible_v<detected_t<impl_t, T>, index_t>; \
  };                                                           \
  EASY_VALUE(has_##op);

const_interface_no_args(rows);
const_interface_no_args(cols);
const_interface_no_args(size);
#undef const_interface_no_args

template <typename T>
class has_unary_access {
  template <typename U>
  using impl_t = decltype(std::declval<const U &>()[std::declval<index_t>()]);

 public:
  static constexpr bool value =
      std::is_convertible_v<detected_t<impl_t, T>, real_t>;
};
EASY_VALUE(has_unary_access);

template <typename T>
class has_binary_access {
  template <typename U>
  using impl_t = decltype(std::declval<const U &>()(std::declval<index_t>(),
                                                    std::declval<index_t>()));

 public:
  static constexpr bool value =
      std::is_convertible_v<detected_t<impl_t, T>, real_t>;
};
EASY_VALUE(has_binary_access);

template <typename T>
class has_coeffRef {
  template <typename U>
  using impl_t = decltype(std::declval<U>().coeffRef(std::declval<index_t>(),
                                                     std::declval<index_t>()));

 public:
  //-> how to check ref type?
  static constexpr bool value =
      std::is_same_v<is_detected<impl_t, T>, std::true_type>;
};
EASY_VALUE(has_coeffRef);

DEFINE_HAS_MEMBER(p, fill_mode);
DEFINE_HAS_MEMBER(p, override_mode);
DEFINE_HAS_MEMBER(p, can_parallel);
DEFINE_HAS_MEMBER(p, can_get_data);

template <typename T>
class has_one_dim_fill_impl {
  template <typename U>
  using impl_t = decltype(std::declval<U>()._fill_impl(std::declval<index_t>(),
                                                       std::declval<real_t>()));

 public:
  static constexpr bool value =
      std::is_same_v<is_detected<impl_t, T>, std::true_type>;
};
EASY_VALUE(has_one_dim_fill_impl);

template <typename T>
class has_two_dim_fill_impl {
  template <typename U>
  using impl_t = decltype(std::declval<U>()._fill_impl(std::declval<index_t>(),
                                                       std::declval<index_t>(),
                                                       std::declval<real_t>()));

 public:
  static constexpr bool value =
      std::is_same_v<is_detected<impl_t, T>, std::true_type>;
};
EASY_VALUE(has_two_dim_fill_impl);

template <typename T>
class has_override_batch_fill {
  template <typename U>
  using impl_t =
      decltype(std::declval<U>()._batch_fill(std::declval<Eigen::MatrixXd>()));

 public:
  static constexpr bool value =
      std::is_same_v<is_detected<impl_t, T>, std::true_type>;
};
EASY_VALUE(has_override_batch_fill);

template <typename T,
          std::enable_if_t<!has_member_override_mode_v<T>, bool> = true>
inline constexpr bool is_override_mode() {
  return false;
}

template <typename T,
          std::enable_if_t<has_member_override_mode_v<T>, bool> = true>
inline constexpr bool is_override_mode() {
  return T::override_mode;
}

template <typename T,
          std::enable_if_t<!has_member_can_get_data_v<T>, bool> = true>
inline constexpr bool is_can_get_data() {
  return false;
}

template <typename T,
          std::enable_if_t<has_member_can_get_data_v<T>, bool> = true>
inline constexpr bool is_can_get_data() {
  return T::can_get_data;
}

template <typename T>
class has_data {
  template <typename U>
  using impl_t = decltype(std::declval<U>().data());

 public:
  static constexpr bool value = is_can_get_data<T>() && is_override_mode<T>() &&
                                std::is_same_v<detected_t<impl_t, T>, real_t *>;
};
EASY_VALUE(has_data);

}  // namespace chaos::mapping::details::data_filler_traits
