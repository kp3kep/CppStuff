#include <iostream>

struct Granny {
    virtual ~Granny() = default;

    virtual void f() {}
    void non_virtual_granny();

    int g;
};

struct Mom: virtual Granny {
    int m = 7;

    void f() override {}
    virtual void mom() {}

    void non_virtual_mom() {}
};

struct Dad: virtual Granny {
    int d = 3;

    void f() override {}
    virtual void dad() {}

    void non_virtual_dad() {}
};

struct Son: Mom, Dad {
    int s = 4;
    void f() override {
        std::cout << "Son" << std::endl;
    }

    void mom() override {}

    void non_virtual_son(int x) {}
};

int main() {
    Son son;

    void** vptr = reinterpret_cast<void **>(&son);

    std::cout << vptr << std::endl;
    std::cout << *vptr << std::endl;

    void (*f)(Son*, int, int) = reinterpret_cast<void(*)(Son*, int, int)>(*vptr);
    f(&son, 1, 0);

    return 0;
}