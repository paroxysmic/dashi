#ifndef _CHESS_H
#define _CHESS_H
#include <iostream>
#include <sstream>
#include <cstdint>
#include <array>
#include <vector>
#include "rays.hpp"
#include "bitutil.hpp"
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
static constexpr std::array<uint64_t, 64> BISHOP_MASKS = gen_bishop_masks();
static constexpr std::array<uint64_t, 64> ROOK_MASKS = gen_rook_masks();   
class Board{
    public:
        Board();
        void display();
        void initialize();
        void debugPrint();
        void setToFEN(std::string FEN);
        uint64_t data[12] = {0};
        uint64_t whites = 0;
        uint64_t blacks = 0;
        uint64_t empties = -1;    
        bool whitesturn = 0;
        /*
        enpassant target is the square that 
        a double forward pawn skipped, square 
        that another pawn could capture on
        */
        uint64_t enpassanttarget = 0;
        /*
        castling rights is a nybble
        0x0001 - white queenside
        0x0010 - white kingside
        0x0100 - black queenside
        0x1000 - black kingside
        */
        uint8_t castlingrights = 0;
        /* 
        half-moves since someone captured or 
        moved a pawn
        */
        uint8_t halfmovecount = 0;
        /*
        total moves, starts at 1
        */
        uint16_t movecount = 1;
};
void desc_u64(uint64_t b);
#endif