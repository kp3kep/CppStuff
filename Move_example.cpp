#include <iostream>
#include <vector>

struct Pointer {
    int* pointer;
    Pointer() : pointer(new int) {
        std::cout << "Constructor" << std::endl;
    }
    explicit Pointer(int x) : pointer(new int) {
        *pointer = x;
        std::cout << "Constructor " << x << std::endl;
    }

    Pointer(const Pointer&) = default;

    Pointer& operator=(const Pointer&) = delete;

    Pointer(Pointer&& other) noexcept : pointer(other.pointer) {
        std::cout << "Move constructor" << std::endl;
        other.pointer = nullptr;
    }

    Pointer& operator=(Pointer&& other) noexcept {
        std::cout << "Move assignment" << std::endl;
        pointer = other.pointer;
        other.pointer = nullptr;
        return *this;
    }

    ~Pointer() {
        std::cout << "Destructor" << std::endl;
        if (pointer) {
            std::cout << "NON nullptr " << *pointer << std::endl;
        }
        else {
            std::cout << "nullptr" << std::endl;
        }
        delete pointer;
    }

    explicit Pointer(const std::string& s) : pointer(new int) {
        std::cout << "Constructor " << s << std::endl;
    }
};

struct S {
    Pointer ptr {0 };
    std::vector<Pointer> v;

    S() = default;
    S(int x) : ptr(x) {}

    template <typename... Args>
    S(Args&&... args) {
        v.reserve(sizeof...(args));
        std::cout << "sizeof " << sizeof...(args) << std::endl;
        (v.push_back(std::forward<Args>(args)), ...);
    }

    [[nodiscard]] Pointer getData() const & {
        std::cout << "lvalue\n";
        return ptr;
    }

    [[nodiscard]] Pointer getData() && {
        std::cout << "rvalue\n";
        return std::move(ptr);
    }
};

int main() {
    S s {Pointer(0), Pointer(1), Pointer(7)};

    return 0;
}