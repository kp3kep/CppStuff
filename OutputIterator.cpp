#include <algorithm>
#include <iostream>
#include <vector>

bool even(int x) {
    return x % 2 == 0;
}

template <typename Container>
class back_insert_iterator {
    Container& container;
public:
    back_insert_iterator(Container& c) : container(c) {}

    back_insert_iterator& operator=(const typename Container::value_type& value) {
        container.push_back(value);
        return *this;
    }

    back_insert_iterator& operator++() {
        return *this;
    }

    back_insert_iterator operator++(int) {
        return *this;
    }

    back_insert_iterator& operator*() {
        return *this;
    }
};

// *it++ = *it2++;

template <typename Container>
back_insert_iterator<Container> mback_inserter(Container& container) {
    return {container};
}

int main() {

    int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<int> v;

    std::copy_if(a, a + 10, mback_inserter(v), even);

    for (auto i : v) {
        std::cout << i << " ";
    }

    return 0;
}