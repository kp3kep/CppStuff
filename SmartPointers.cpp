#include <iostream>

#pragma once
#undef _GLIBCXX_HAVE_ATOMIC_LOCK_POLICY
#define __GTHREADS 1

#include <memory>

/// UNIQUE PTR
/// @tparam T pointer type
/// @tparam Deleter
template<typename T, typename Deleter = std::default_delete<T>>
class unique_ptr {
    T* ptr = nullptr;
    [[no_unique_address]] Deleter del;

public:
    unique_ptr() = default;
    explicit unique_ptr(T* ptr) : ptr(ptr) {}
    ~unique_ptr() {
        del(ptr);
    }
    unique_ptr(const unique_ptr& other) = delete;
    unique_ptr& operator=(const unique_ptr& other) = delete;

    unique_ptr(unique_ptr&& other) noexcept : ptr(other.ptr), del(other.del) {
        other.ptr = nullptr;
        other.del = std::default_delete<T>();
    }
    unique_ptr& operator=(unique_ptr&& other) noexcept {
        if (this != &other) {
            del(ptr);
            ptr = other.ptr;
            del = other.del;
            other.ptr = nullptr;
            other.del = std::default_delete<T>();
        }
        return *this;
    }

    T& operator*() const {
        return *ptr;
    }
    T* operator->() const {
        return ptr;
    }
    T* get() const {
        return ptr;
    }
};

/// SHARED PTR
/// @tparam T  pointer type
///
template<typename T>
class shared_ptr {
private:
    T* ptr = nullptr;
    size_t* count = nullptr;

    struct ControlBlock {
        T value;
        size_t count;
    };

    template<typename U, typename... Args>
    friend shared_ptr<U> make_shared(Args&&... args);

public:
    shared_ptr() = default;
    explicit shared_ptr(T* ptr) : ptr(ptr), count(new size_t(1)) {
        std::cout << "shared_ptr construct " << *count << '\n';
    }
    shared_ptr(const shared_ptr& other) : ptr(other.ptr), count(other.count) {
        if (!count)
            return;

        ++(*count);
        std::cout << "shared_ptr copy construct " << *count << '\n';
    }
    shared_ptr(shared_ptr&& other) noexcept : ptr(other.ptr), count(other.count) {
        other.ptr = nullptr;
        other.count = nullptr;
        if (!count)
            return;
        std::cout << "shared_ptr move construct " << *count << '\n';
    }
    shared_ptr& operator=(const shared_ptr& other) {
        if (this != &other) {
            ptr = other.ptr;
            count = other.count;
            if (!count)
                return *this;
            ++(*count);
            std::cout << "shared_ptr copy assignment " << *count << '\n';
        }
        return *this;
    }
    shared_ptr& operator=(shared_ptr&& other) noexcept {
        if (this != &other) {
            ptr = other.ptr;
            count = other.count;
            other.ptr = nullptr;
            other.count = nullptr;
            if (!count)
                return *this;
            std::cout << "shared_ptr move assignment " << *count << '\n';
        }
        return *this;
    }

    ~shared_ptr() {
        if (!count || !ptr) {
            std::cout << "shared_ptr destructor empty\n";
            return;
        }

        if (*count > 1) {
            std::cout << "shared_ptr destruct " << *count << '\n';
            --(*count);
        } else {
            std::cout << "shared_ptr destruct " << *count << " last\n";
            delete count;
            delete ptr;
        }
    }

    T& operator*() const {
        return *ptr;
    }
    T* operator->() const {
        return ptr;
    }
    T* get() const {
        return ptr;
    }
};

template<typename T, typename... Args>
unique_ptr<T> make_unique(Args&&... args) {
    return unique_ptr<T>(new T(std::forward<Args>(args)...));
}

template<typename T, typename... Args>
shared_ptr<T> make_shared(Args&&... args) {
    return unique_ptr<T>(new T(std::forward<Args>(args)...));
}

/// WEAK PTR
/// @tparam T  pointer type
///

void* operator new(size_t n) {
    std::cout << n << std::endl;
    return malloc(n);
}

struct myclass : __gnu_cxx::__mutex
{
protected:
    // This policy is used when atomic builtins are not available.
    // The replacement atomic operations might not have the necessary
    // memory barriers.
    enum { _S_need_basdasd = 1 };
};

struct S {
    long long a;
    long long b;

    ~S() {
        std::cout << "~S()\n";
    }
};



int main() {

    std::shared_ptr ptr = std::make_shared<S>();

    ptr->a = 77;
    ptr->b = 88;
    std::cout << "sizeof S " << sizeof(S) << std::endl << std::endl;
    std::cout << "sizeof Mutex " << sizeof(__gnu_cxx::__mutex) << std::endl << std::endl;

    using mytype = std::_Sp_counted_ptr_inplace<S, std::allocator<void>, __gnu_cxx::__default_lock_policy>;
    using ControlBlock = std::__shared_count<>;

    S& ss = reinterpret_cast<S&>(ptr);
    std::_Sp_counted_base<>* hp = reinterpret_cast<std::_Sp_counted_base<>*>(ss.b);

    mytype* wtf = dynamic_cast<mytype*>(hp);
    auto q = wtf;

    std::cout << "typeid Control Block " << typeid(mytype).name() << std::endl;
    std::cout << "sizeof Control Block " << sizeof(mytype) << std::endl;

    std::aligned_storage<>;

    std::weak_ptr weak_ptr(ptr);

    // auto p = std::shared_ptr<int>(new int(77));
    //
    // auto p2 = p;
    //
    // const auto p3 = p2;
    //
    // p2 = std::make_shared<int>(55);
    //
    // std::cout << std::endl;
    // auto my_sp = shared_ptr<int>();
    //
    // std::weak_ptr<int> my_wp = p2;
    //
    // auto p4 = std::move(p);
    //
    // std::cout << p.get() << std::endl;
    // std::cout << *p2 << std::endl;
    // std::cout << *p3 << std::endl;
    // std::cout << *p4 << std::endl;


    return 0;
}