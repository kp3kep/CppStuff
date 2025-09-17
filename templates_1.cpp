#include <iostream>
#include <map>
#include <vector>

template <typename T>
struct S {
    T field;
    S(T _field) : field(_field) {}
};

template <typename T, template <typename> typename Container = std::vector>
class Stack {
public:
    Container<T> data;
};

template <int N>
struct Fibonacci {
    static constexpr int value = Fibonacci<N-1>::value + Fibonacci<N-2>::value;
};

template <>
struct Fibonacci<1> {
    static constexpr int value = 1;
};

template <>
struct Fibonacci<0> {
    static constexpr int value = 0;
};


int main() {
    Stack<int> s;

    s.data.push_back(10);
    s.data.push_back(11);
    s.data.push_back(77);

    for (int i : s.data) {
        std::cout << i << std::endl;
    }

    std::cout << Fibonacci<20>::value << std::endl;

    return 0;
}