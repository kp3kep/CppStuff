#include <iostream>
#include <vector>

struct S {

    S() try: x(7) {

    }
    catch(...) {

    }

    void f() try {

    }
    catch (...) {

    }

    ~S() noexcept(false) {
        if (!std::uncaught_exceptions()) {
            throw 1;
        }
    }

    int x { 0 };
};

template<typename _Tp>
void g() {}

int main() {
    if constexpr (noexcept(g<int>())) {
        ;
    }

    return 0;
}