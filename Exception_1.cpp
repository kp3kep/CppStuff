#include <iostream>

int divide(int dividend, int divisor) {
    if (divisor == 0) {
        throw std::invalid_argument("Divide by zero");
    }
    return dividend / divisor;
}

int main() {

    try {
        divide(1, 0);
    }
    catch(std::invalid_argument& err) {
        std::cerr << err.what() << std::endl;
    }


    return 0;
}