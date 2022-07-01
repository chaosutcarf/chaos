#include <concepts>
#include <iostream>
#include <type_traits>

#include "common/pattern.h"
#include "common/type.h"
#include "mapping/data_filler_concepts.h"

using namespace chaos;
using namespace chaos::mapping::data_filler_concepts;

template <typename Derived, OneDimTraitsConcept _Traits>
struct Base {
  using Traits = _Traits;
  Base() {
    static_assert(OneDimFillerConcept<Derived>, "check!");
}
};

struct AAATraits {
  static constexpr bool Override = true;
  static constexpr bool CanParallel = true;
  static constexpr bool CanGetData = true;
};

struct AAA : public Base<AAA, AAATraits> {
  index_t _size() const {return 1;}
};

struct BBB {
  // using Traits = int;
};

int main(int argc, char *argv[]) {
  AAA a;

  if constexpr (OneDimFillerConcept<AAA>) {
    printf("yes\n");
  } else {
    printf("no\n");
  }
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
