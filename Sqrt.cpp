#include <algorithm>
#include <bitset>
#include <cstdint>
#include <iostream>
#include <vector>

class Solution {
public:
    int mySqrt(int x) {
        if (x == 0) return 0;
        Input = x;
        FirstApprox = 1 << (getHB(x) / 2 );
        Result = FirstApprox;

        while (check())
            ;

        return Result;
    }
private:
    int Input = 0;
    int FirstApprox = 0;
    int Result = 0;

    bool check() {
        FirstApprox /= 2;
        if (Result * Result > Input) {
            Result -= FirstApprox;
            return true;
        }
        if ((Result + 1) * (Result + 1) <= Input) {
            Result += FirstApprox;
            return true;
        }
        return false;
    }

    static int getHB(unsigned x) noexcept {
        return x == 0 ? 0 : 32 - std::countl_zero(x);
    }
};

int main() {

    std::vector v = {4, 3, 2, 1};
    for (int j = 0; j < 17; ++j) {
        for (int i : v) {
            std::cout << i << ' ';
        }
        std::cout << '\n';
        std::next_permutation(v.begin(), v.end());
    }

    return 0;
}