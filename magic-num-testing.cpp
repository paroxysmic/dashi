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
uint64_t shitty_hash(uint64_t key, uint64_t magic){
    return (key * magic) >> (64 - bitcount(key));
}
std::vector<uint64_t> gen_blocker_boards(uint64_t bitmask) {
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
    int direcs[4] = {-8, -1, 1, 8};
    uint64_t bounds[4] = {0, FILE_H, FILE_A, 0};
    uint64_t atkbrd = 0;
    for (int i=0;i<4;i++) {
        bool unblocked = true;
        uint64_t cpos = pos;
        while(unblocked) {
            cpos = direcs[i] > 0 ? cpos << direcs[i] : cpos >> -direcs[i]; 
            if (cpos & (bounds[i] | bitmask) != 0) {
                break;  
            }
            atkbrd += cpos;
        }
    }
}   
int main() {
    Board board;
    std::vector<uint64_t> magics(64, 0);
    for(int i=0;i<64;i++) {
        std::vector<uint64_t> blockerboards = gen_blocker_boards(board.ROOK_MASKS[i]);
        bool unmagic = true;
        int trials = 0;
        while(unmagic) {
            trials++;
            unmagic = false;
            magics[i] = randu64() & randu64() & randu64();  
            std::vector<uint64_t> hash(1 << bitcount(board.ROOK_MASKS[i]), 0);
            for(uint64_t board: blockerboards) {
                if(++hash[shitty_hash(board, magics[i])] != 1) {
                    unmagic = true;
                    break;
                }
            }
            if ((trials & 0xfff) == 0) {
                std::cout << trials << '\n';
            }
        }
        std::cout << "found magic " << i << "!\n";
    } 
    return 0;
}