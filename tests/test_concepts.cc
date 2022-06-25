#include <concepts>
#include <iostream>
#include <type_traits>

#include "common/pattern.h"
#include "common/type.h"
#include "mapping/data_filler_concepts.h"

struct AAA {
  template <typename T>
  requires std::floating_point<T>
  void f(const T &a) const {
    static_assert(std::floating_point<T>, "floating");
  }
};

template <typename T, typename U>
concept testC = requires(T a, U b) {
  {a.template f<U>(b)};
};

template <typename T, bool flag>
void f(const T &mat) {
  printf("%d\n", flag);
}

template <typename T>
concept isOverride = requires(T a) {
  { T::Override } -> std::convertible_to<bool>;
};

template <typename Derived>
struct Base {
  CRTP_derived_interface(Derived, Base);
  template <bool tested = true>
  void hello() const {
    //-> check.
    derived().template _hello<tested && isOverride<Derived>>();
  }
};

struct D1 : public Base<D1> {
  template <bool flag>
  void _hello() const {
    printf("d1.%d\n", flag);
  }
};
struct D2 : public Base<D2> {
  static constexpr bool Override = true;
  template <bool flag>
  void _hello() const {
    printf("d2.%d\n", flag);
  }
};

struct D3 : public Base<D3> {
  static constexpr bool Override = false;
  template <bool flag>
  void _hello() const {
    printf("d3.%d\n", flag);
  }
};

// struct D {
//   static constexpr bool CanGetData = false;
//   static constexpr bool Override = true;
//   // static constexpr chaos::MATRIX_FILL_MODE FillMode =
//   // chaos::MATRIX_FILL_MODE::FULL;
// };

int main(int argc, char *argv[]) {
  if constexpr (testC<AAA, AAA>) {
    printf("yes\n");
  } else {
    printf("no\n");
  }
  return 0;
}

// template <typename T>
// concept hasMemberXdim = requires(T a) {
//   { T::xdim }
//   ->std::convertible_to<unsigned>;
// };

// template <typename T>
// concept compileTimeNx = hasMemberXdim<T> &&T::xdim != -1;

// template <typename T>
// concept runtimeNx = requires(const T &a) {
//   { a._nx_impl() }
//   ->std::convertible_to<unsigned>;
// };

// template <typename T>
// concept NxConcept = compileTimeNx<T> || runtimeNx<T>;

// struct A {
//   static constexpr int xdim = 5;
//   int _nx_impl() const { return 1; }
// };

// template <NxConcept A>
// constexpr int f(A a) {
//   if constexpr (hasMemberXdim<A>) {
//     return a.xdim;
//   } else {
//     return a._nx_impl();
//   }
// }
