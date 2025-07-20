#include "chess.hpp"
#include <iostream>
#include <random>
#include <bitset>
#include <array>
std::array<uint64_t, 64> magics = {0};
std::array<uint64_t, 64> shifts = {0};
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
uint64_t* gen_blocker_boards(const uint64_t bitmask) {
    int bmbc = bitcount(bitmask);
    int bmcopy = bitmask;
    int *boards = new int[1 << bmbc];
    int *bits = new int[bmbc];
    for(int i=0;i<bmbc;i++) {
        //obtaining the singular bits of the bitmask
        bits[i] = get_LSB(bmcopy);
        bmcopy -= bits[i];
    }
    for(int i=0;i<(1<<bmbc);i++) {
        //conv i to binary here
        boards[i] = 
    }
}
int main() {
    for(int i=0;i<64;i++) {
        magics[i] = randu64() & randu64() & randu64();
        shifts[i] = rand() % 64;
    } 
    return 0;
}