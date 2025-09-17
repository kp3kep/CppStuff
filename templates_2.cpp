#include <iostream>

template <typename T>
struct S {
    using type = T;
};

template <typename T>
T* f() {
    typename S<T>::type* x = new S<T>::type;
    return x;
}

int main() {
    auto x = f<int>();
    *x = 100;
    delete x;

    return 0;
}