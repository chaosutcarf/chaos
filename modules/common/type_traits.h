#pragma once

#include <type_traits>

namespace chaos {
namespace details {

// http://en.cppreference.com/w/cpp/experimental/is_detected
template <class Default, class AlwaysVoid, template <class...> class Op,
          class... Args>
struct detector {
  using value_t = std::false_type;
  using type = Default;
};

template <class Default, template <class...> class Op, class... Args>
struct detector<Default, std::void_t<Op<Args...>>, Op, Args...> {
  using value_t = std::true_type;
  using type = Op<Args...>;
};

// http://en.cppreference.com/w/cpp/experimental/nonesuch
struct nonesuch {
  nonesuch() = delete;
  ~nonesuch() = delete;
  nonesuch(nonesuch const &) = delete;
  void operator=(nonesuch const &) = delete;
};

}  // namespace details
   //
/// Implementation of \p std::is_detected.
/**
 * Implementation of \p std::is_detected, from C++17. See:
 * http://en.cppreference.com/w/cpp/experimental/is_detected.
 */
template <template <class...> class Op, class... Args>
using is_detected =
    typename details::detector<details::nonesuch, void, Op, Args...>::value_t;

/// Implementation of \p std::detected_t.
/**
 * Implementation of \p std::detected_t, from C++17. See:
 * http://en.cppreference.com/w/cpp/experimental/is_detected.
 */
template <template <class...> class Op, class... Args>
using detected_t =
    typename details::detector<details::nonesuch, void, Op, Args...>::type;

#define DEFINE_HAS_MEMBER(prefix, member_name)                        \
  template <typename prefix##T>                                       \
  class has_member_##member_name {                                    \
    template <typename U>                                             \
    static std::true_type test(decltype(&U::member_name));            \
    template <typename U>                                             \
    static std::false_type test(...);                                 \
                                                                      \
   public:                                                            \
    static constexpr bool value =                                     \
        std::is_same_v<decltype(test<prefix##T>(0)), std::true_type>; \
  };

}  // namespace chaos
