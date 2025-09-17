#include <iostream>
#include <memory>
#include <thread>

void* operator new(size_t n) {
    std::cout << n << std::endl;
    void* p = malloc(n);
    if (p == nullptr) {
        throw std::bad_alloc();
    }
    return p;
}


void f() {
    std::cout << "f" << std::endl;
}

struct S {
    long long a;
    long long b;

    ~S() {
        std::cout << "~S()\n";
    }
};

int main() {
    uint64_t i {0};
    std::thread t(f);
    while (i < 1'000'000'000'0) {
        ++i;
    }

    t.detach();

    return 0;
}