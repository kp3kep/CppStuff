#include <iostream>

template<typename T>
struct UniquePtr {
    T* ptr;
    explicit UniquePtr(T* ptr) : ptr(ptr) {}
    UniquePtr(const UniquePtr& other) = delete;
    UniquePtr& operator=(const UniquePtr& other) = delete;
    // UniquePtr(UniquePtr&& other) noexcept : ptr(other.ptr) {
    //     other.ptr = nullptr;
    // }
    ~UniquePtr() { delete ptr; }

    T& operator*() const { return *ptr; }
};

template<typename T>
struct SharedPtr {

};

void g(int y) {
    if (y == 0) {
        throw std::invalid_argument("zero");
    }
}

void f(int x) {
    int* p = new int(x);
    g(*p);
    delete p;
}

int main() {
    f(5);

    return 0;
}