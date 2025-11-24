#pragma once
#include <cstdint>
#include <vector>
#include <iostream>
typedef uint8_t U8;
typedef uint16_t U16;
typedef uint32_t U32;
typedef uint64_t U64;

const U64 FILE_A = 0x0101010101010101ULL;
const U64 FILE_B = 0x0202020202020202ULL;
const U64 FILE_C = 0x0404040404040404ULL;
const U64 FILE_D = 0x0808080808080808ULL;
const U64 FILE_E = 0x1010101010101010ULL;
const U64 FILE_F = 0x2020202020202020ULL;
const U64 FILE_G = 0x4040404040404040ULL;
const U64 FILE_H = 0x8080808080808080ULL;
const U64 RANK_1 = 0x00000000000000FFULL;
const U64 RANK_2 = 0x000000000000FF00ULL;
const U64 RANK_3 = 0x0000000000FF0000ULL;
const U64 RANK_4 = 0x00000000FF000000ULL;
const U64 RANK_5 = 0x000000FF00000000ULL;
const U64 RANK_6 = 0x0000FF0000000000ULL;
const U64 RANK_7 = 0x00FF000000000000ULL;
const U64 RANK_8 = 0xFF00000000000000ULL;
const U64 HIGH = 0x8000000000000000ULL;
constexpr int get_trailing_zeros(U64 v) { return __builtin_ctzll(v); }
constexpr int get_leading_zeros(U64 v) { return __builtin_clzll(v); }
constexpr U64 get_bit(U64 num, int shift) { return ((num >> shift) & 1); }
constexpr U64 lshif(U64 num, int shift){ return (shift > 0) ? num << shift : num >> -shift; }
constexpr U64 rshif(U64 num, int shift){ return (shift > 0) ? num >> shift : num << -shift; }
constexpr U64 get_LSB(U64 num) { return num & -num; }
constexpr U64 get_MSB(U64 num) { return num & (1ULL << (63 - get_leading_zeros(num))); }
constexpr int bitcount(U64 num) {
    int rt = 0;
    for(int i=0;i<64;i++) { rt += ((num >> i) & 1); }
    return rt;
}
inline void desc_u64(U64 b) {
    for(int i=0;i<8;++i) {
        for(int j=0;j<8;++j) {
            int ind = 56 + j - (i * 8);
            std::cout << ((b >> ind) & 1) << ' ';
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}