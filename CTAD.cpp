#include <iostream>
#include <vector>

/// dectype keyword

template <typename T>
struct Debug {
    Debug() = delete;
};

// CTAD
template <typename Container>
auto getElement(Container& cont, size_t index)
    -> decltype(cont[index])
{
    return cont[index];
}

// Тоже самое , что и предыдущее, но короче
template <typename Container>
decltype(auto) getElement2(Container& cont, size_t index)
{
    return cont[index];
}

int main() {
    int x = 0;
    int& y = x;
    decltype(y) z = y;

    std::vector<bool> v(5);
    getElement(v, 0) = true;

    for (int i : v) {
        std::cout << i << ' ';
    }

    return 0;
}