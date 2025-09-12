#ifndef _MOVE_HPP
#define _MOVE_HPP
#include "bitutil.hpp"
class Move{
    public:
        Move();
        uint64_t init_sq;   
        uint64_t end_sq;
        uint8_t init_castlingrights;
        uint8_t end_castlingrights;
        uint8_t piece_type;
        /*
        if capture_type is 0, the move is not a capture
        otherwise, it start with pawn - 1 and increases
        according to piece value
        */
        uint8_t capture_type;
        /*
        uses same four bits as castlingrights
        but this describes if it's a castle
        is_castle[0] - white queenside
        is_castle[1] - white kingside
        is_castle[2] - black queenside
        is_castle[3b] - black kingside
        */
        bool is_castle[4];
        bool is_enpassant;
        bool is_white_move;
};
#endif