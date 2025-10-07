#include <iostream>
#include <variant>
#include <vector>
#include <string>
#include <type_traits>

// --- Overload pattern ---
template <typename... Ts>
struct Overload : Ts... {
    using Ts::operator()...; // inherit all operator() overloads
};
// deduction guide (C++17)
template <class... Ts>
Overload(Ts...) -> Overload<Ts...>;

int main() {
    std::vector<std::variant<std::vector<int>, double, std::string>> vecVariant{
            1.5,
            std::vector<int>{1, 2, 3, 4, 5},
            "Hello"
    };

    auto DisplayMe = Overload{
            // Case 1: handle std::vector<int>
            [](std::vector<int>& myVec) {
                for (auto v : myVec) std::cout << v << " ";
                std::cout << "\n";
            },

            // Case 2: handle double or string
            [](auto& arg) {
                if constexpr (std::is_same_v<std::decay_t<decltype(arg)>, std::string>) {
                    std::cout << "string: " << arg << "\n";
                } else if constexpr (std::is_same_v<std::decay_t<decltype(arg)>, double>) {
                    std::cout << "double: " << arg << "\n";
                }
            }
    };

    for (auto& v : vecVariant) {
        std::visit(DisplayMe, v);
    }
}
