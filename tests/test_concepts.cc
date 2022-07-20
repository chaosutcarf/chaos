#include <concepts>
#include <iostream>
#include <type_traits>

#include "common/pattern.h"
#include "common/type.h"
#include "mapping/data_filler_concepts.h"
#include "mapping/function_concepts.h"
using namespace chaos;
using namespace chaos::mapping::data_filler_concepts;
using namespace chaos::mapping::function_concepts;
template <typename T>
concept HasT = requires {
  T::Traits::Flag;
};

template <typename T>
concept TestTraits = HasT<T>;

template <typename T>
struct Base {
  Base() { static_assert(TestTraits<T>, "check"); }
};

struct ATraits {
  static constexpr bool Flag = true;
};

struct A : public Base<A> {
    static constexpr int fdim{11};
};

int main(int argc, char *argv[]) {
  if constexpr (CompileTimeNfConcept<A>) {
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
