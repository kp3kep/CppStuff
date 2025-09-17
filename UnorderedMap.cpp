#include <cstdint>
#include <iostream>
#include <unordered_map>


struct hash {
    uint64_t operator()(int) const noexcept {return 1;}
};

int main() {
    std::unordered_map<int, int, hash> map;

    map[1] = 1;
    map[2] = 2;
    map[3] = 3;

    for (auto it = map.begin(); it != map.end(); ++it) {
        std::cout << it->first << " " << it->second << std::endl;
    }
    return 0;
}