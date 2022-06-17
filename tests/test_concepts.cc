#include <concepts>
#include <iostream>
#include <type_traits>

template <typename T>
concept hasMemberXdim = requires(T a) {
  { T::xdim }
  ->std::convertible_to<unsigned>;
};

template <typename T>
concept compileTimeNx = hasMemberXdim<T> &&T::xdim != -1;

template <typename T>
concept runtimeNx = requires(const T &a) {
  { a._nx_impl() }
  ->std::convertible_to<unsigned>;
};

template <typename T>
concept NxConcept = compileTimeNx<T> || runtimeNx<T>;

struct A {
  static constexpr int xdim = 5;
  int _nx_impl() const { return 1; }
};

template <NxConcept A>
constexpr int f(A a) {
  if constexpr (hasMemberXdim<A>) {
    return a.xdim;
  } else {
    return a._nx_impl();
  }
}


int main(int argc, char *argv[]) {
  printf("%d\n", f(A()));
  return 0;
}
