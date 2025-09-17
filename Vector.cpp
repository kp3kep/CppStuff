#include <cstdint>
#include <deque>
#include <iostream>
#include <vector>
#include "Allocators.h"

// PoolAllocator
// StackAllocator
// FreeListAllocator

template <typename T, typename Alloc = std::allocator<T>>
class Vector {
    T* arr_ {nullptr};
    size_t sz_ {0};
    size_t cap_ {0};
    [[no_unique_address]] Alloc alloc_;

    template <bool IsConst>
    class base_iterator {
    public:
        using pointer_type = std::conditional_t<IsConst, const T*, T*>;
        using reference_type = std::conditional_t<IsConst, const T&, T&>;
        using value_type = T;

    private:
        pointer_type ptr;
        base_iterator(T* ptr) : ptr(ptr) {}

    public:
        base_iterator(const base_iterator&) = default;
        base_iterator& operator=(const base_iterator&) = default;

        reference_type operator*() const { return *ptr; }

        pointer_type operator->() const { return ptr; }

        base_iterator& operator++() {
            ++ptr;
            return *this;
        }

        base_iterator operator++(int) {
            base_iterator tmp { *this };
            ++ptr;
            return tmp;
        }

        base_iterator& operator--() {
            --ptr;
            return *this;
        }
    };


public:

    using iterator = base_iterator<false>;
    using const_iterator = base_iterator<true>;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    Vector& operator=(const Vector& other) {
        T* newarr = allocator_traits::allocate(alloc_, other.cap_);
        size_t i {0};
        try {
            for (; i < other.sz_; ++i) {
                allocator_traits::construct(alloc_, newarr + i, other[i]);
            }
        } catch (...) {
            for (size_t j = 0; j < sz_; ++j) {
                allocator_traits::destroy(alloc_, other.cap_);
            }
        }

    }

    iterator begin() { return {arr_}; }

    iterator end() { return {arr_ + sz_}; }

    const_iterator begin() const { return {arr_}; }

    const_iterator end() const { return {arr_ + sz_}; }

    const_iterator cbegin() const noexcept { return {arr_}; }

    const_iterator cend() const noexcept { return {arr_ + sz_}; }


    void reserve(size_t newcap) {
        if (newcap <= cap_) {
            return;
        }

        T* newarr = alloc_.allocate(newcap);

        size_t index {0};
        try {
            for (; index < sz_; ++index) {
                alloc_.construct(&newarr[index], *arr_ + index);
            }
        } catch (...) {
            if (index != 0) {
                // ReSharper disable once CppDFAUnreachableCode
                for (size_t newindex = 0; newindex < index; ++newindex) {
                    alloc_.destroy(newarr + newindex);
                }
            }
            // ReSharper disable once CppDFAUnreachableCode
            alloc_.deallocate(newarr, newcap);
            throw;
        }

        for (index = 0; index < sz_; ++index) {
            alloc_.destroy(arr_ + index);
        }
        alloc_.deallocate(arr_, cap_);

        arr_ = newarr;
        cap_ = newcap;
    }

    void push_back(const T& value) {
        if (sz_ == cap_) {
            reserve(cap_ > 0 ? 2 * cap_ : 1);
        }
        allocator_traits<Alloc>::construct(alloc_, arr_ + sz_, value);
        ++sz_;
    }

    void push_back(T&& value) {
        if (sz_ == cap_) {
            reserve(cap_ > 0 ? 2 * cap_ : 1);
        }
        allocator_traits<Alloc>::construct(alloc_, arr_ + sz_, std::move(value));
        ++sz_;
    }
};

template <>
class Vector<bool> {
    char* arr_ {nullptr};
    size_t sz_ {0};
    size_t cap_ {0};

    struct BitReference {
        char* cell;
        uint8_t index;

        void operator=(bool b) {
            if (b) {

            }
        }
    };
public:

};

int main() {

    std::vector vec {true, false, true, false, true, false, true, false};
    std::_Bit_reference b = vec[5];
    for (auto i : vec) {
        std::cout << i << '\n';
    }
    std::cout << b._M_p << '\n';

    vec.begin().operator+(5);

    return 0;
}