#ifndef _BITMANIP_H
#define _BITMANIP_H
#include <cstdint>
#include <vector>
const uint64_t FILE_A = 0x0101010101010101ULL;
const uint64_t FILE_B = 0x0202020202020202ULL;
const uint64_t FILE_C = 0x0404040404040404ULL;
const uint64_t FILE_D = 0x0808080808080808ULL;
const uint64_t FILE_E = 0x1010101010101010ULL;
const uint64_t FILE_F = 0x2020202020202020ULL;
const uint64_t FILE_G = 0x4040404040404040ULL;
const uint64_t FILE_H = 0x8080808080808080ULL;
const uint64_t RANK_1 = 0x00000000000000FFULL;
const uint64_t RANK_2 = 0x000000000000FF00ULL;
const uint64_t RANK_3 = 0x0000000000FF0000ULL;
const uint64_t RANK_4 = 0x00000000FF000000ULL;
const uint64_t RANK_5 = 0x000000FF00000000ULL;
const uint64_t RANK_6 = 0x0000FF0000000000ULL;
const uint64_t RANK_7 = 0x00FF000000000000ULL;
const uint64_t RANK_8 = 0xFF00000000000000ULL;
constexpr int get_trailing_zeros(uint64_t v) {
    return __builtin_ctzll(v);
}
constexpr int get_leading_zeros(uint64_t v) {
    return __builtin_clzll(v);
}
constexpr uint64_t get_bit(uint64_t num, int shift) {
    return ((num >> shift) & 1);
}
constexpr uint64_t lshif(uint64_t num, int shift){
    return (shift > 0) ? num << shift : num >> -shift;
}
constexpr uint64_t rshif(uint64_t num, int shift){
    return (shift > 0) ? num >> shift : num << -shift;
}
constexpr uint64_t get_LSB(uint64_t num) {
    return get_bit(num, get_leading_zeros(num) + 1);
}
constexpr uint64_t get_MSB(uint64_t num) {
    return get_bit(num, get_trailing_zeros(num) + 1);
}
constexpr int bitcount(uint64_t num) {
    int rt = 0;
    for(int i=0;i<64;i++) {
        rt += ((num >> i) & 1);
    }
    return rt;
}
std::vector<uint64_t> gen_bit_combs(uint64_t bitmask);
void desc_u64(uint64_t b);
#endif