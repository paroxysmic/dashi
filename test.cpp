#include <cstdint>
#include <iostream>
int main() {
    uint64_t boof  = 0xffff;
    boof >>= -2;
    std::cout << boof;
    return 0;
}