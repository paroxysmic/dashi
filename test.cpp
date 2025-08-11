#include <cstdint>
#include "chess.hpp"
#include <iostream>
int main() {
    for(int i=0;i<64;i++) {
        std::cout << std::hex << bishopmagics[i] << '\n';
    }
    return 0;
}