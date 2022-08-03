#include <iostream>

template <typename Core>
struct MixinPrint : Core {
  template <bool flag>
  inline void print() {
    Core::template print<flag>();
  }
};

struct hasPrint {
  template <bool flag>
  void print() {
    std::cout << flag << std::endl;
    std::cout << "has print" << std::endl;
  }
};

int main(int argc, char *argv[]) {
  MixinPrint<hasPrint> b;
  b.print<true>();
  return 0;
}
