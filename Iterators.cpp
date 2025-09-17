#include <iostream>
#include <vector>

template <typename InputIterator>
void find_most_often_number(InputIterator begin, InputIterator end) {
    typename std::iterator_traits<InputIterator>::value_type x = *begin;
    // ...
}

template <typename Iterator>
typename std::iterator_traits<Iterator>::difference_type
mydistance(Iterator first, Iterator last) {
    if constexpr (std::is_base_of_v<
            std::random_access_iterator_tag,
            typename std::iterator_traits<Iterator>::iterator_category
            >) {
        return last - first;
    }

    int i {0};
    for (;first != last; ++first, ++i) ;
    return i;
}

int main() {

    const std::vector<int> vec(7);

    std::cout << mydistance(vec.begin(), vec.end());

    return 0;
}