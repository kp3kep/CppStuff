#include <iostream>

struct Granny {
    virtual ~Granny() = default;
    virtual void f() {
        std::cout << "Granny" << std::endl;
    }
    int g{};
};

struct Mom: virtual Granny {
    int m{};
};

struct Dad: virtual Granny {
    int d{};
};

struct Son final : Mom, Dad {
    int s{};
    void f() override {
        std::cout << "Son" << std::endl;
    }
};

int main() {

    Son s;
    Granny* g = &s;

    if (Son* ptr = dynamic_cast<Son*>(g)) {
        ptr->f();
    }
    else {
        std::cerr << "error" << std::endl;
    }

    return 0;
}