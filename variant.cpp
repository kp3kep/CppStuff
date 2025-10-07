#include <algorithm>

template <typename... Types>
class Variant;

template<typename... Types>
const size_t get_index = 0;

template <typename T, typename... Types>
class VariantAlternative {
public:
    static constexpr size_t index = get_index<T, Types...>;

    VariantAlternative() = default;
    ~VariantAlternative() = default;
    VariantAlternative(const T& value) {
        auto* this_variant = static_cast<Variant<Types...>*>(this);
        new (this_variant->buffer) T(value);
        this_variant->active_index = index;
    }

    VariantAlternative(T&& value) {
        auto* this_variant = static_cast<Variant<Types...>*>(this);
        new (this_variant->buffer) T(std::move(value));
        this_variant->active_index = index;
    }

    void destroy() {
        auto* this_variant = static_cast<Variant<Types...>*>(this);
        if (this_variant->active_index == index) {
            reinterpret_cast<T>(this_variant)->~T();
        }
    }
};

template <typename... Types>
union VariadicUnion;

template <typename Head, typename... Tail>
union VariadicUnion<Head, Tail...> {
    Head head;
    VariadicUnion<Tail...> tail;
};

template <typename Tail>
union VariadicUnion<Tail> {
    Tail tail;
};

template <typename... Types>
struct max_sizeof;

template <typename Head, typename... Tail>
struct max_sizeof<Head, Tail...> {
    static const size_t value = std::max(sizeof(Head), max_sizeof<Tail...>::value);
};

template<typename T>
struct max_sizeof<T> {
    static constexpr size_t value = sizeof(T);
};

template <typename... Types>
constexpr size_t max_sizeof_v = max_sizeof<Types...>::value;

template <typename... Types>
class Variant : private VariantAlternative<Types, Types...>... {
//    VariadicUnion<Types...> vu;
    char buffer[max_sizeof_v<Types...>];
    size_t active_index;

    template<typename T, typename... Ts>
    friend class VariantAlternative;

public:
    using VariantAlternative<Types, Types...>::VariantAlternative...;
};

int main() {
    Variant<int, double> v(5);
}