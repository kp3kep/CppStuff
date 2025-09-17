#include <iostream>

template <typename First, typename Second, typename... Tail>
struct is_homogeneous {
    static constexpr bool value = std::is_same_v<First, Second> && is_homogeneous<Second, Tail...>::value;
};

template <typename First, typename Second>
struct is_homogeneous<First, Second> {
    static constexpr bool value = std::is_same_v<First, Second>;
};

template <typename First, typename Second, typename... Tail>
constexpr bool is_homogeneous_v = is_homogeneous<First, Second, Tail...>::value;

template <typename... Types>
void print(const Types&... types) {
    (std::cout << ... << types) << ' ';
}


int main() {
    print(1, 2.0, "abc");

    if constexpr (!is_homogeneous_v<int, double, char>) {
        std::cout << "TADA" << '\n';
    }

    return 0;
}