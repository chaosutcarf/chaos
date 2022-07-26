#include "iostream"
#include "mapping/filler_concept.hh"
using namespace chaos::mapping;
using namespace std;

template <typename Derived>
struct Base {
  void world() {
    this->print();
    std::cout << "world\n";
  }
};

template <typename T>
struct B : public T {
  using T::T;
  void print() const { std::cout << "print" << std::endl; }
};

template<bool flag>
struct Traits{
    constexpr static bool _f = flag;
};

template<bool f>
struct A {
    using t = Traits<f>;

    template<bool flag = t::_f>
    void print() {
        std::cout << flag << std::endl;
    }
};



int main(int argc, char *argv[]) {
    A<true> a;
    A<false> b;
    a.print();
    b.print();
  return 0;
}
