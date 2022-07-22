#include <iostream>
using namespace std;

struct A {
  void test() const { cout << "A" << std::endl; }

  template <typename T>
  void next(const T &) const {}

  void good() const {}
};

template <typename T>
struct B : public T {
  using T::good;
  using T::next;
  template <typename D>
  void next() const {}
  using T::test;
};

int main(int argc, char *argv[]) {
  B<A> b;
  b.test();
  b.next<int>(1);
  b.good();
  b.next<int>();
  return 0;
}
