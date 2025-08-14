#include <cstdint>
#include "chess.hpp"
#include <iostream>
int main() {
    std::cout << get_leading_zeros(0ULL) << ' ' << get_trailing_zeros(0ULL);
    return 0;
}