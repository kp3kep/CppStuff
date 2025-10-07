#include <iostream>
#include <vector>
#include <random>
#include <chrono>

int main() {
    using namespace std::chrono;
    const int N = 10'000'000; // 20 млн элементов

    std::vector<int> v1(N);
    std::vector<uint8_t> v2(N); // bool заменён на uint8_t для кеш-дружелюбности

    // Современный рандом
    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<> dist_val(0, 99);
    std::bernoulli_distribution dist_flag(0.5); // равномерное распределение

    // Заполнение
    for (int i = 0; i < N; ++i) {
        v1[i] = dist_val(gen);
        v2[i] = dist_flag(gen);
    }
    {
        auto start = high_resolution_clock::now();

        for (int i = 0; i < N - 32; ++i) {
            int& x = v1[i];
            if (v2[i])
                x += x;
            else
                x *= x;
        }

        auto duration = duration_cast<milliseconds>(high_resolution_clock::now() - start);
        std::cout << "Time1: " << duration.count() << " ms\n";
    }

    for (int i = 0; i < N; ++i) {
        v1[i] = dist_val(gen);
        v2[i] = dist_flag(gen);
    }
    {
        auto start = high_resolution_clock::now();
            // arr
        int x;
        for (int i = 0; i < N - 32; ++i) {
            x = v1[i];
            int a[2] = {x + x, x * x};
            v1[i] = a[v2[i]];
        }

        auto duration = duration_cast<milliseconds>(high_resolution_clock::now() - start);
        std::cout << "Time2: " << duration.count() << " ms\n";
    }

    for (int i = 0; i < N; ++i) {
        v1[i] = dist_val(gen);
        v2[i] = dist_flag(gen);
    }
    {
        auto start = high_resolution_clock::now();
        // formula

        uint8_t b;
        int x;

        for (int i = 0; i < N - 32; ++i) {
            x = v1[i];
            b = v2[i];
            v1[i] = b * (x + x) + (!b) * (x * x);
        }

        auto duration = duration_cast<milliseconds>(high_resolution_clock::now() - start);
        std::cout << "Time3: " << duration.count() << " ms\n";
    }
}
