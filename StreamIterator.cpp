#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>

template <typename T>
class optional {
    char val[sizeof(T)];
    bool initialized = false;
public:
    optional(const T& newvalue) : initialized(true) {
        new (val) T(newvalue);
    }
    optional() {}
    ~optional() {
        if (initialized) {
            reinterpret_cast<T*>(&val)->~T();
        }
    }
    bool has_value() const {
        return initialized;
    }
    operator bool() const {
        return initialized;
    }

    T& operator*() & {
        return reinterpret_cast<T&>(*val);
    }
    const T& operator*() const & {
        return reinterpret_cast<T&>(*val);
    }
    T&& operator*() && {
        return reinterpret_cast<T&>(*val);
    }
    const T&& operator*() const && {
        return reinterpret_cast<T&>(*val);
    }

    const T& value_or(const T& other) const {
        return initialized ? reinterpret_cast<T&>(*val) : other;
    }
};

template <typename T>
class IStreamIterator {
    std::istream* is = nullptr;
    T value;

public:
    using iterator_category = std::input_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;


    IStreamIterator() {}
    IStreamIterator(std::istream& in) : is(&in) {
        *is >> value;
    }
    IStreamIterator& operator++() {
        if (!(*is >> value)) {
            *this = IStreamIterator();
        }
        return *this;
    }
    T& operator*() {
        return value;
    }
    bool operator==(const IStreamIterator& other) const {
        return is == other.is;
    }
    bool operator!=(const IStreamIterator& other) const {
        return !(*this == other);
    }
};

int main() {
    std::istream_iterator<int> it(std::cin);
    std::vector<int> v(it, std::istream_iterator<int>());

    // std::copy(it, std::istream_iterator<int>(), std::back_inserter(v));

    for (int i {0}; i <  v.size(); ++i) {
        std::cout << v[i]*v[i] << ' ';
    }

    int x = 123;

    std::cout << std::hex;
    std::cout << x << '\n';
    std::cout << std::showbase;
    std::cout << x << '\n';
    std::cout << std::noboolalpha;
    std::cout << x << '\n';



    return 0;
}