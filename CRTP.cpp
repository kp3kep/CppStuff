#include <iostream>

// Базовый шаблон, параметризованный потомком
template <typename Derived>
struct Base {
    void interface() {
        // общий код до
        static_cast<Derived*>(this)->implementation(); // "виртуальный" вызов
        // общий код после
    }

    // реализация по умолчанию, если Derived не переопределит
    void implementation() {
        std::cout << "Base implementation\n";
    }
};

// Потомок
struct DerivedA : Base<DerivedA> {
    void implementation() {
        std::cout << "Derived A implementation\n";
    }
};

struct DerivedB : Base<DerivedB> {
    void implementation() {
        std::cout << "Derived B implementation\n";
    }
};

struct DerivedC : Base<DerivedC> {
};

template <typename T>
void f(Base<T> base) {
    base.interface();
    std::cout << sizeof(base) << '\n';
}

int main() {
    DerivedA a;
    DerivedB b;
    DerivedC c;

    f(a); // вызовет Derived A::implementation
    f(b); // вызовет Derived B::implementation
    f(c); // вызовет Base implementation
}