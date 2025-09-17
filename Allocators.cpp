#include <cstddef>
#include <iostream>
#include <memory>

#include "Allocators.h"


int main() {
    char c;
    int x;

    int* px = &x;

    std::cout << static_cast<void*>(&c) << std::endl;
    std::cout << px << std::endl;

    c = std::rand();
    x = std::rand();

    return 0;
}