#include "chess.hpp"
#include <iostream>
#include <random>
#include <bitset>
#include <array>
static std::mt19937_64 rng(0xDEADBEEF); 
std::uniform_int_distribution<uint64_t> dist(0, UINT64_MAX);
uint64_t randu64() {
    return dist(rng);
    rand();
}
uint64_t shitty_hash(uint64_t key, uint64_t magic){
    //trying to extract 12 bits of entropy, so grab the 12 MSB
    //the MSB are more "entropic" bcz *any* bits can affect them
    return (key * magic) >> (64 - bitcount(key));
}
bool verify_magic(uint64_t magic, int pos, bool checkRooks) {
    Board board;
    uint64_t fullmask = checkRooks ? board.ROOK_MASKS[pos] : board.BISHOP_MASKS[pos];
    std::array<uint64_t, 4096> hashvals;
    //filling with -1 to prevent false positive collisions from zero-initializing the array
    hashvals.fill(-1);
    bool unmagic = true;
    std::vector<uint64_t> masks = gen_bit_combs(fullmask);
    for(uint64_t mask: masks) {
        uint64_t indkey = shitty_hash(mask, magic); 
        uint64_t atkbrd = checkRooks ? gen_rook_attack_board(1ULL << pos, mask) : gen_bishop_attack_board(1ULL << pos, mask);
        if(hashvals[indkey] != -1) {
            if(atkbrd != hashvals[indkey]) {
                return false;
            }
        }
        else {
            hashvals[indkey] = atkbrd;
        }
    }
    return true;
}
int main() {
    for(int i=0;i<64;++i) {
        bool unmagic = true;
        uint64_t magic = 0;
        while(unmagic) {
            magic = randu64() & randu64() & randu64();
            unmagic = !verify_magic(magic, i, false);
        }
        std::cout << magic << '\n';
    } 
} 