#pragma once
#include <iostream>
#include <sstream>
#include <array>
#include "bitutil.hpp" 
#include "enums.hpp"
#include "move.hpp"
class Board{
    public:
        Board();
        void display(bool isWhite);
        void initialize();
        void debugPrint();
        void setToFEN(std::string FEN);
        std::array<U64, 12> bitboards = {0};
        U64 whites = 0;
        U64 blacks = 0;
        U64 empties = -1; 
        bool whiteInCheck = false;
        bool blackInCheck = false;   
        bool whitesturn = true;
        /*
        enpassant target is the square that 
        a double forward pawn skipped, square 
        that another pawn could capture on
        */
        U64 enpassanttarget = 0;
        /*
        castling rights is a nybble
        0b0001 - white queenside
        0b0010 - white kingside
        0b0100 - black queenside
        0b1000 - black kingside
        */
        Castle castlingrights = Castle(15);
        /* 
        half-moves since someone captured or 
        moved a pawn
        */
        U8 halfmovecount = 0;
        /*
        total moves, starts at 1
        */
        U16 movecount = 1;
};