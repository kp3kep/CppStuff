#include <iostream>

struct Granny {
    virtual ~Granny() = default;

    virtual void f() {
        std::cout << "Granny" << std::endl;
    }
    void non_virtual_granny();

    int g;
};

struct Mom: virtual Granny {
    int m = 7;

    void f() override {
        std::cout << "Mom" << std::endl;
    }
    virtual void mom() {}

    void non_virtual_mom() {}
};

struct Dad: virtual Granny {
    int d = 3;

    void f() override {
        std::cout << "Dad" << std::endl;
    }
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

    void**** vptr = reinterpret_cast<void ****>(&son); // pointer to vtable

    void (*fptr)(Son*, int, int) = reinterpret_cast<void(*)(Son*, int, int)>(**vptr); // **vptr - the address that contains pointer to Son::f
    fptr(&son, 1, 0); // print: Son

    void*** rtti_ptr = *vptr - 1; // pointer to RTTI
    void** typename_ptr  = *rtti_ptr + 1; // pointer to type name

    std::cout << static_cast<char*>(*typename_ptr) << std::endl; // print : 3Son

    return 0;
}