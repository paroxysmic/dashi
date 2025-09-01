#ifndef _BOARD_H
#define _BOARD_H
#include <iostream>
#include <sstream>
#include <array>
#include "rays.hpp"
#include "bitutil.hpp" 
#include "enums.hpp"
#include "move.hpp"
class Board{
    public:
        Board();
        void display();
        void initialize();
        void debugPrint();
        void setToFEN(std::string FEN);
        void makeMove(Move move);
        void unmakeMove(Move move);
        std::vector<Move> getPSLMoves();
        uint64_t bitboards[12] = {0};
        uint64_t whites = 0;
        uint64_t blacks = 0;
        uint64_t empties = -1;    
        bool whitesturn = true;
        /*
        enpassant target is the square that 
        a double forward pawn skipped, square 
        that another pawn could capture on
        */
        uint64_t enpassanttarget = 0;
        /*
        castling rights is a nybble
        0b0001 - white queenside
        0b0010 - white kingside
        0b0100 - black queenside
        0b1000 - black kingside
        */
        uint8_t castlingrights = 0b1111;
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