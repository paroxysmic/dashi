#ifndef _CHESS_H
#define _CHESS_H
#include <cstdint>
#include <array>
#define set_bit(b, i) ((b) |= (1ULL << (i)))
#define get_bit(b, i) ((b) & (1ULL << (i)))
#define clear_bit(b, i) ((b) &= ~(1ULL << (i)))
#define lshif(b, s) ((s > 0) ? (b << (s)) : (b >> (-s)))
#define rshif(b, s) ((s > 0) ? (b >> (s)) : (b << (-s)))
#define FILE_A 0x0101010101010101ULL
#define FILE_B 0x0202020202020202ULL
#define FILE_C 0x0404040404040404ULL
#define FILE_D 0x0808080808080808ULL
#define FILE_E 0x1010101010101010ULL
#define FILE_F 0x2020202020202020ULL
#define FILE_G 0x4040404040404040ULL
#define FILE_H 0x8080808080808080ULL
#define RANK_1 0x00000000000000FFULL
#define RANK_2 0x000000000000FF00ULL
#define RANK_3 0x0000000000FF0000ULL
#define RANK_4 0x00000000FF000000ULL
#define RANK_5 0x000000FF00000000ULL
#define RANK_6 0x0000FF0000000000ULL
#define RANK_7 0x00FF000000000000ULL
#define RANK_8 0xFF00000000000000ULL
#define FULL 0xFFFFFFFFFFFFFFFFULL
enum Team{
    WHITE = 0, 
    BLACK = 1,
    NONE = 2
};
struct Move{
    Move(uint64_t ssq, uint64_t fsq);
    uint64_t startsq;
    uint64_t finalsq;
};
class Board{
    public:
        Board();
        void display();
        void initialize();
        std::array<uint64_t, 12> data = {0};
        uint64_t whites = 0;
        uint64_t blacks = 0;
        uint64_t empties = FULL;   
        std::array<uint64_t, 64> gen_bishop_masks();
        std::array<uint64_t, 64> gen_rook_masks();
        std::array<uint64_t, 64> BISHOP_MASKS = gen_bishop_masks();
        std::array<uint64_t, 64> ROOK_MASKS = gen_rook_masks();   
        uint64_t getPSLPawnMoves(uint64_t pos, enum Team team);
        uint64_t getPSLKnightMoves(uint64_t pos, enum Team team);
        uint64_t getPSLBishopMoves(uint64_t pos, enum Team team);
        uint64_t getPSLRookMoves(uint64_t pos, enum Team team);
        uint64_t getPSLQueenMoves(uint64_t pos, enum Team team);
        uint64_t getPSLKingMoves(uint64_t pos, enum Team team);    
        
};
void desc_u64(uint64_t b);
uint64_t shitty_hash(uint64_t key, uint64_t magic);
#endif