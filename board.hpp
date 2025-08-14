#ifndef _CHESS_H
#define _CHESS_H
#include <iostream>
#include <cstdint>
#include <array>
#include <vector>
#include "rays.hpp"
#include "bitutil.hpp"
extern uint64_t rookmagics[64];
extern uint64_t bishopmagics[64];
extern int bishopbitnums[64];
extern int rookbitnums[64];
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
constexpr std::array<uint64_t, 64> gen_king_attacks() {
    std::array<uint64_t, 64> kgatks = {};
    for(int i=0;i<64;i++) {
        uint64_t pos = 1ULL << i;
        kgatks[i] = (((pos << 7) | (pos >> 1) | (pos >> 9)) & ~(FILE_A)) |
                    (((pos >> 7) | (pos << 1) | (pos << 9)) & ~(FILE_H)) | 
                    (pos >> 8) | (pos << 8);
    }
    return kgatks;
}
constexpr std::array<uint64_t, 64> gen_knight_attacks() {
    std::array<uint64_t, 64> knatks = {};
    for(int i=0;i<64;i++) {
        uint64_t pos = 1ULL << i;
        knatks[i] = (((pos << 6) | (pos >> 10)) & ~(FILE_G | FILE_H)) | 
                    (((pos << 10) | (pos >> 6)) & ~(FILE_A | FILE_B)) |
                    (((pos << 15) | (pos >> 17)) & ~(FILE_A)) | 
                    (((pos >> 15) | (pos << 17)) & ~(FILE_H));
    }
    return knatks;
}
constexpr std::array<uint64_t, 64> gen_bishop_masks() {
    std::array<uint64_t, 64> masks = {0};
    for(int i=0;i<64;i++) {
        masks[i] = (RAYS[0][i] | RAYS[2][i] | RAYS[4][i] | RAYS[6][i])
        & (~(RANK_1 | RANK_8 | FILE_A | FILE_H));
    }
    return masks;
}   
constexpr std::array<uint64_t, 64> gen_rook_masks() {
    std::array<uint64_t, 64> masks = {0};
    for(int i=0;i<64;i++) {
        masks[i] =  ((RAYS[1][i] | RAYS[5][i]) & (~(RANK_1 | RANK_8))) |
                    ((RAYS[3][i] | RAYS[7][i]) & (~(FILE_A | FILE_H)));
    }
    return masks;
} 
static constexpr std::array<uint64_t, 64> KING_ATTACKS = gen_king_attacks();
static constexpr std::array<uint64_t, 64> KNIGHT_ATTACKS = gen_knight_attacks();
static constexpr std::array<uint64_t, 64> BISHOP_MASKS = gen_bishop_masks();
static constexpr std::array<uint64_t, 64> ROOK_MASKS = gen_rook_masks();   
class Board{
    public:
        Board();
        void display();
        void initialize();
        std::array<uint64_t, 12> data = {0};
        uint64_t whites = 0;
        uint64_t blacks = 0;
        uint64_t empties = -1;   
        uint64_t getPSLPawnMoves(uint64_t pos, Team team);
        uint64_t getPSLKnightMoves(uint64_t pos, Team team);
        uint64_t getPSLBishopMoves(uint64_t pos, Team team);
        uint64_t getPSLRookMoves(uint64_t pos, Team team);
        uint64_t getPSLQueenMoves(uint64_t pos, Team team);
        uint64_t getPSLKingMoves(uint64_t pos, Team team);    
};
void desc_u64(uint64_t b);
uint64_t gen_rook_attack_board(uint64_t pos, uint64_t blockers);
uint64_t gen_bishop_attack_board(uint64_t pos, uint64_t blockers);
#endif