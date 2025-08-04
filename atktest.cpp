#include "chess.hpp"
#include <iostream>
int bitcount(uint64_t num) {
    int rt = 0;
    for(int i=0;i<64;i++) {
        rt += ((num >> i) & 1);
    }
    return rt;
}
uint64_t gen_rook_attack_board(uint64_t pos, uint64_t bitmask) {
    if(bitcount(pos) != 1) {
        throw std::runtime_error("rook position should be one-hot!");
    }
    uint64_t atkbrd = 0;
    int direcs[4] = {-8, -1, 1, 8};
    uint64_t borders[4] = {0, FILE_H, FILE_A, 0};
    for(int i=0;i<4;i++) {
        uint64_t cpos = pos;
        bool unblocked = true;
        while(unblocked) {
            cpos = lshif(cpos, direcs[i]);
            if((cpos == 0) || (((atkbrd | borders[i]) & cpos) != 0)) {
                unblocked = false;
            }
            if(unblocked) {
                atkbrd += cpos;
            }
        }
    }
    return atkbrd;
} 
int main() {
    uint64_t rka = (RANK_1 & FILE_C) | (RANK_3 & FILE_F);
    uint64_t pos = (RANK_3 & FILE_C);
    uint64_t atkb = gen_rook_attack_board(pos, rka);
    desc_u64(atkb);
    return 0;
}