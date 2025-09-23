#pragma once
#include "bitutil.hpp"
class Castle{
    public:
        Castle(int type) {
            castle_type[0] = type & 1;
            castle_type[1] = (type >> 1) & 1;
            castle_type[2] = (type >> 2) & 1;
            castle_type[3] = (type >> 3) & 1;
        }
        bool isWhiteKing() { return castle_type[0]; }
        bool isWhiteQueen() { return castle_type[1]; }
        bool isBlackKing() { return castle_type[2]; }
        bool isBlackQueen() { return castle_type[3]; }
        bool isCastle() {return castle_type[0] | castle_type[1] | castle_type[2] | castle_type[3];}
        void setRight(CastleType right) { castle_type[right] = true; }
        void clearRight(CastleType right) { castle_type[right] = false; }
    private:
        bool castle_type[4];
};
class Move{
    public:
        Move();
        U64 init_sq;   
        U64 end_sq;
        Castle init_castlingrights;
        Castle end_castlingrights;
        Castle castle;
        PieceType piece_type;
        /*
        if capture_type is 0, the move is not a capture
        otherwise, it start with pawn - 1 and increases
        according to piece value
        */
        PieceType capture_type;
        bool is_enpassant;
        bool is_double_pawn_move;
        bool is_white_move;
        bool promotion_type[4];
};