#include "iostream"
#include "mapping/filler_concepts.hh"
using namespace chaos::mapping;
using namespace std;

struct A {
  static constexpr bool Override{true};
  static constexpr bool CanGetData{true};
  static constexpr chaos::MATRIX_FILL_MODE MatFillMode{
      chaos::MATRIX_FILL_MODE::FULL};
  using Traits = FillerTraits<A>;

  template <bool fillmode = Traits::Override()>
  void hello() {
    cout << fillmode << std::endl;
    cout << "mat: " << (int)Traits::MatFillMode() << std::endl;
    cout << "CanGetData: " << Traits::CanGetData() << std::endl;
    cout << "CanParallel: " << Traits::CanParallel() << std::endl;
    cout << "Override: " << Traits::Override() << std::endl;
  }
};

int main(int argc, char *argv[]) {
  A a;
  a.hello();
  return 0;
}
