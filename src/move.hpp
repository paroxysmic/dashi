#ifndef _MOVE_HPP
#define _MOVE_HPP
#include "bitutil.hpp"
class Move{
    public:
        Move();
        uint8_t init_ind;   
        uint8_t end_ind;
        uint8_t init_castlingrights;
        uint8_t end_castlingrights;
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
};
#endif