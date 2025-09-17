#include <iostream>
#include <optional>
#include <vector>

template <int N, typename... Args>
void tuple_out(std::tuple<Args...> t) {
    std::cout << std::get<N>(t) << ' ';
    if constexpr (N > 0)
        tuple_out<N - 1, Args...>(t);
}

int main() {

    std::tuple t{1, 2.0, 'a'};

    auto [x, y, z] = t;
    x = 15;

    tuple_out<2>( t);

    return 0;
}