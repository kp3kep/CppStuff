#include <iostream>
#include <vector>

void f(auto... x) {}   /// auto как аргумент - тоже самое, что template<typename T>

template <typename T> /// auto возвращаемый тип
auto g() {
    if constexpr (std::is_same_v<T, int>) {
        std::cout << "int\n";
        return 0;
    } else {
        std::cout << "HE int\n";
        return 1u;
    }
}

template <auto N>
struct Example {};

int main() {

    Example<2> ei;
    Example<'a'> ec;

    g<int>();
    g<float>();

    {
        auto x = 5;                      // int
        auto& y = x;                // int&
        const auto& z = y;      // const int&
        auto&& w = x;               // int&
    }

    return 0;
}