#include <iostream>

template<typename T>
concept HasPrint = requires(T a) {
a.print();
};

template<typename Core>
struct MixinPrint: Core{
    static constexpr bool _flag = HasPrint<Core>;

    inline void print() {
        if constexpr (_flag) {
            Core::print();
        } else {
            std::cout << "no print" << std::endl;
        }
    }
};

struct noPrint{};

struct hasPrint{
    void print() {
        std::cout << "has print" << std::endl;
    }
}
    ;

int main(int argc, char *argv[]) {
    MixinPrint<noPrint> a;
    MixinPrint<hasPrint> b;
    a.print();
    b.print();
    return 0;
}
