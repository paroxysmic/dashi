#include "bitutil.hpp"
#include <iostream>
std::vector<uint64_t> gen_bit_combs(uint64_t bitmask) {
    int bmbc = bitcount(bitmask);                  
    std::vector<uint64_t> bits;
    std::vector<uint64_t> boards(1 << bmbc, 0);
    for(int i=0;i<64;i++) {
        if (((bitmask >> i) & 1) == 1) {
            bits.push_back(1ULL << i);
        }
    }
    for(int i=0;i<(1<<bmbc);i++) {
        for(int j=0;j<bmbc;j++) {
            if(((i >> j) & 1) == 1) {
                boards[i] |= bits[j];
            }
        }
    }
    return boards;
}
void desc_u64(uint64_t b) {
    //0 1 2 3 4 5 6 7
    //so on and so forth
    for(int i=0;i<8;++i) {
        for(int j=0;j<8;++j) {
            int ind = 56 + j - (i * 8);
            std::cout << ((b >> ind) & 1) << ' ';
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}
