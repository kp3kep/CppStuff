#include <cstring>
#include <iostream>

template<typename  T, typename U>
struct is_same {
    static constexpr bool value = false;
};

template<typename T>
struct is_same<T, T> {
    static constexpr bool value = true;
};

template<typename T, typename U>
void f(T& x, U& y) {
    if constexpr (is_same<T, U>::value) {
        x = y;
    }
}

struct Foo {
    int x;
    explicit Foo(const int v) : x(v) { std::cout << "Ctor " << x << "\n"; }
    ~Foo() { std::cout << "Dtor " << x << "\n"; }
};

template<typename T>
void CopyObjects(T* dst, const T* src, size_t count) {
    if constexpr (std::is_trivially_copyable_v<T>) {
        std::memcpy(dst, src, count * sizeof(T));
    } else {
        for (size_t i = 0; i < count; ++i) {
            new (dst + i) T(src[i]);
        }
    }
}

int main() {
    int x = 5;
    int y = 77;
    std::string s = std::to_string(x);
    f(x, s);
    f(x, y);
    std::cout << x << std::endl;

    alignas(Foo) char buffer[sizeof(Foo)]; // сырой буфер на стеке

    Foo* f = new (buffer) Foo(42);  // placement new в стеке
    std::cout << f->x << "\n";      // 42
    f->~Foo();
}