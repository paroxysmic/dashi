#include "make_move.hpp"
//THIS DOES NOT CHECK IF THE MOVE IS LEGAL
void makeMove(Board& board, Move move) {
    //should push onto the state stack and update everything
    //i hate threefold repetition :[
    BoardState state;
    if(move.castle.isCastle()) {
        
    }
}
//THIS DOES NOT CHECK IF THE MOVE IS LEGAL
void unmakeMove(Board& board, Move move) {
    if(move.castle.isCastle()){
        if(move.castle.isWhiteQueen()) {
            board.bitboards[WHITE_KING] = FILE_E & RANK_1;
            board.bitboards[WHITE_ROOK] ^= (FILE_A | FILE_D) & RANK_1;
            board.castlingrights.setRight(WHITE_QUEENSIDE);
        }
        if(move.castle.isWhiteKing()) {
            board.bitboards[WHITE_KING] = FILE_E & RANK_1;
            board.bitboards[WHITE_ROOK] ^= (FILE_F | FILE_H) & RANK_1;
            board.castlingrights.setRight(WHITE_KINGSIDE);
        }
        if(move.castle.isBlackQueen()) {
            board.bitboards[BLACK_KING] = FILE_E & RANK_8;
            board.bitboards[BLACK_ROOK] ^= (FILE_A | FILE_D) & RANK_8;
            board.castlingrights.setRight(BLACK_QUEENSIDE);
        }
        if(move.castle.isBlackKing()) {
            board.bitboards[BLACK_KING] = FILE_E & RANK_8;
            board.bitboards[BLACK_ROOK] ^= (FILE_F | FILE_H) & RANK_8;
            board.castlingrights.setRight(BLACK_KINGSIDE);
        }   
        return;
    }
    if(move.is_enpassant) {
        //we need to reconstruct the enpassant target
        board.enpassanttarget = move.is_white_move ? move.init_sq >> 8 : move.init_sq << 8;
        board.bitboards[move.piece_type] ^= (move.init_sq | move.end_sq);
        board.bitboards[6 - move.piece_type] ^= board.enpassanttarget;
        return;
    }
    if(move.capture_type != NONE) {
        board.bitboards[move.piece_type] ^= (move.init_sq | move.end_sq);
        board.bitboards[move.capture_type] ^= move.end_sq;
        return;
    }
    for(int i=0;i<4;i++) {
        if(move.promotion_type[i]) {
            board.bitboards[move.is_white_move ? 0 : 6] ^= move.init_sq;
            board.bitboards[move.is_white_move ? i + 1: i + 7] ^= move.end_sq;
        }
    }
    if(move.is_double_pawn_move) {
        
    }
    board.bitboards[move.piece_type] ^= (move.init_sq | move.end_sq);
    return;
}
