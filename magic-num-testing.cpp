#include "chess.hpp"
#include <iostream>
#include <random>
#include <bitset>
#include <array>
static std::mt19937_64 rng(0xDEADBEEF); 
std::uniform_int_distribution<uint64_t> dist(0, UINT64_MAX);
uint64_t randu64() {
    return dist(rng);
}
int bitcount(uint64_t num) {
    int rt = 0;
    for(int i=0;i<64;i++) {
        rt += ((num >> i) & 1);
    }
    return rt;
}
int shitty_hash(uint64_t key, uint64_t magic){
    //trying to extract 12 bits of entropy, so grab the 12 MSB
    //the MSB are more "entropic" bcz *any* bits can affect them
    return (key * magic) >> 52;
}
std::vector<uint64_t> gen_bit_combs(uint64_t bitmask) {
    int bmbc = bitcount(bitmask);                  
    std::vector<uint64_t> bits;
    std::vector<uint64_t> boards(1 << bmbc, 0);
    for(int i=0;i<64;i++) {
        if (((bitmask >> i) & 1) == 1) {
            bits.push_back(bitmask & (1 << i));
        }
    }
    for(int i=0;i<(1<<bmbc);i++) {
        for(int j=0;j<bmbc;j++) {
            if(((i >> j) & 1) == 1) {
                boards[i] += bits[j];
            }
        }
    }
    return boards;
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
            cpos = direcs[i] > 0 ? cpos << direcs[i] : cpos >> -direcs[i];
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
    Board board;
    uint64_t magic;
    std::array<uint64_t, 4096> hashkeys = {0};
    std::array<uint64_t, 4096> hashvals = {0};
    for(int i=0;i<64;i++) {
        uint64_t pos = 1ULL << i;
        uint64_t fullmask = board.ROOK_MASKS[i];
        std::vector<uint64_t> masks = gen_bit_combs(fullmask);
        for(uint64_t mask: masks) {
            //hash(atkbrd(mask0)) == hash(atkbrd(mask1)) iff atkbrd(mask0) == atkbrd(mask1)

        }
    }
    std::cout << std::bitset<64>(magic);
    return 0;
} 