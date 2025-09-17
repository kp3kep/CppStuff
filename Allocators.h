#pragma once
#include <cstdlib>
#include <iostream>
#include <utility>
/*
 * std::forward and std:: move implementation
 */
template<typename T>
struct is_lvalue_reference_wrapper : std::false_type {
    is_lvalue_reference_wrapper() {
        std::cout << typeid(T).name() << '\n';
    }
};

template<typename T>
struct is_lvalue_reference_wrapper<T&> : std::true_type {
    is_lvalue_reference_wrapper() {
        std::cout << typeid(T).name() << '\n';
    }
};

template <typename T>
T&& forward(std::remove_reference_t<T>& value) {
    return static_cast<T&&>(value);
}

template <typename T>
T&& forward(std::remove_reference_t<T>&& value) {
    static_assert(!std::is_lvalue_reference_v<T>);
    return static_cast<T&&>(value);
}

template <typename T>
std::remove_reference_t<T>&& move(T&& value) {
    return static_cast<std::remove_reference_t<T>&&>(value);
}

/*
 * Allocator Traits
 */
template<typename, typename, typename = void>
struct has_construct : std::false_type {};

template<typename Alloc, typename U, typename... Args>
struct has_construct<Alloc, U(Args...),
        std::void_t<
            decltype(std::declval<Alloc&>().construct(std::declval<U*>(), std::declval<Args>()...))
        >
    >
    : std::true_type {};

template <typename Alloc>
struct allocator_traits {

    template<typename U, typename... Args>
    static void construct(Alloc& alloc, U* ptr, Args&&... args) {
        if constexpr ( has_construct<Alloc, U(Args&&...)>::value ) {
            alloc.construct(ptr, std::forward<Args>(args)...);
        } else {
            new (ptr) U(args...);
        }
    }
    void allocate(Alloc& alloc, size_t n) {

    }
};



/*
 * Allocator
 */
template <typename T>
struct allocator {
    T* allocate(size_t count) {
        return operator new(count * sizeof(T));
    }

    void deallocate(T* ptr, std::size_t n) {
        operator delete(ptr);
    }

    template <typename U, typename... Args>
    void construct(U* ptr, Args&&... args) {
        new (ptr) U(args...);
    }

    template <typename U>
    void destroy(U* ptr) {
        ptr->~U();
    }

    template <typename U>
    allocator(allocator<U>) {}

    bool operator==(const allocator &) const { return true; }

    template <typename U>
    struct rebind {
        typedef allocator<U> other;
    };
};

template <typename T, typename Alloc = std::allocator<T>>
class list {
    struct BaseNode {
        BaseNode* prev;
        BaseNode* next;
    };
    struct Node : BaseNode {
        T* value;
    };

    BaseNode* fakeNode;
    size_t count;
    typename Alloc::template rebind<Node>::other alloc;

    list(const Alloc& alloc) : fakeNode(), count(), alloc(alloc) {}
};