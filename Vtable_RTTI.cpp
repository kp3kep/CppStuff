#include <iostream>
#include <list>

struct Arbuzishe {
    int* x = nullptr;

    Arbuzishe() : x(new int(77)) {}

    virtual void f() {
        std::cout << "A::f\n";
    }

    virtual ~Arbuzishe() {
        std::cout << "~Arbuzishe\n";
        delete x;
    }

    void print_x() const {
        std::cout << *x << '\n';
    }
};

struct S {
    char name[8];
};

int main() {
    Arbuzishe* a = new Arbuzishe();
    void** vptr = (void**)a;
    void** vtable = (void**)vptr[0];
    void** rtti = (void**)vtable[-1];
    S* type_name_A = (S*)rtti[1];
    std::cout << type_name_A->name << std::endl;

    std::list<int> l;
    l.sort();

    using fp = void (*)(Arbuzishe*);

    a->print_x();

    fp f_ptr = (fp)vtable[2];

    f_ptr(a);

//    a.print_x();
    delete a;

    return 0;
}
