#include <cstdint>
#include "chess.hpp"
#include <iostream>
int main() {
    Board board;
    int maxbit = 0;
    for(int i=0;i<64;++i) {
        std::cout << bitcount(board.BISHOP_MASKS[i]) << '\n';
    }
    return 0;
}