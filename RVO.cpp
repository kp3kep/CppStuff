#include <iostream>
#include <vector>

struct S {
    S() {
        std::cout << "Created\n";
    }
    S(char ch) : ch(ch) {
        std::cout << "Created " << ch << "\n";
    }
    S(const S& other) : ch(other.ch) {
        std::cout << "Copied " << ch << "\n";
    }
    S(S&&  other) : ch(other.ch) {
        std::cout << "Moved " << ch << "\n";
    }
    ~S() = default;

    char ch;
};

// RVO
S f1(S&& a) {
    return a;
}
// NO RVO
S f2(S a) {
    return std::move(a);
}
// NRVO
S f3() {
    S a = S();
    return a;
}

// RVO работает через вложенные функции
S g() {
    return S();
}

S f4() {
    S a = g();
    return a;
}

int main() {

    S s = f4();
    // S t1 = S('1');
    // S s1 = f1(std::move(t1));
    // //
    // S t2 = S('2');
    // S s2 = f2(t2);
    // //
    // S s3 = f3();
    return 0;
}