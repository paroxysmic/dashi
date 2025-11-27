#include "gen_move.hpp"

std::vector<Move> genPSLMoves(Board board) {
    std::vector<Move> PSLMoves;
    int boardIndShift = board.whiteToMove ? 0 : 6;
    U64 blockers = board.whiteToMove ? board.blacks : board.whites;
    //normal move check
    for(int i=0;i<6;i++) {
        for(int j=0;j<64;j++) {
            U64 sq = 1 << j;
            U64 possmoves = 0;
            if(board.bitboards[i + boardIndShift] & sq) {
                switch(i) {
                    case PAWN:
                        if(board.whiteToMove) { possmoves = genPSLWhitePawnAttacks(sq, blockers); }
                        else { possmoves = genPSLBlackPawnAttacks(sq, blockers); }
                        break;
                    case KNIGHT:
                        possmoves = genPSLKnightAttacks(sq, blockers);
                        break;
                    case BISHOP:
                        possmoves = genPSLBishopAttacks(sq, blockers);
                        break;
                    case ROOK:  
                        possmoves = genPSLRookAttacks(sq, blockers);
                        break;
                    case QUEEN:
                        possmoves = genPSLQueenAttacks(sq, blockers);
                        break;
                    case KING:
                        possmoves = genPSLKingAttacks(sq, blockers);
                        break;
                }
                while(possmoves) {
                    U64 curr_sq = get_LSB(possmoves);
                    possmoves ^= curr_sq;
                    Move curr_move;
                    curr_move.init_sq = sq;
                    curr_move.end_sq = curr_sq;
                    curr_move.ptype = i + boardIndShift;
                    curr_move.castle = 0;
                    curr_move.enPassant = false;
                    PSLMoves.push_back(curr_move);
                }
            }
        }
    }
    //castle check
    U64 qside = 7 << (board.whiteToMove ? 1 : 57);
    U64 kside = 3 << (board.whiteToMove ? 5 : 61);
    if((qside & (board.blacks | board.whites)) == 0) {
        Move move;
        move.init_sq = -1;
        move.end_sq = -1;
        move.ptype = -1;
        move.castle = board.whiteToMove ? 1 : 4;
        move.enPassant = false;
    }
    if((kside & (board.blacks | board.whites)) == 0) {
        Move move;
        move.init_sq = -1;
        move.end_sq = -1;
        move.ptype = -1;
        move.castle = board.whiteToMove ? 2 : 8;
        move.enPassant = false;
    }
    //doublemove check
    for(int i=0;i<8;i++) {
        if(board.bitboards[0] & (1ull << (i + 8))) {
            Move move;
            move.init_sq = 1ull << (i + 8);
            move.end_sq = 1ull << (i + 24);
            move.ptype = 0;
            move.castle = 0;
            move.enPassant = false;
            PSLMoves.push_back(move);
        }
        if(board.bitboards[6] & (1ull << (i + 48))) {
            Move move;
            move.init_sq = 1ull << (i + 48);
            move.end_sq = 1ull << (i + 32);
            move.ptype = 6;
            move.castle = 0;
            move.enPassant = false;
            PSLMoves.push_back(move);
        }
    }
    //en passant check
    if(board.enpassanttarget != 0) {
        //we check which half of the board this is in
        if(board.enpassanttarget > (1ull << 32)) {
            if ((board.enpassanttarget >> 7) & ~(FILE_A) & board.bitboards[6]) {
                Move move;
                move.init_sq = (board.enpassanttarget >> 7);
                move.end_sq = board.enpassanttarget;
                move.ptype = 6;
                move.castle = 0;
                move.enPassant = false;
            }
            if ((board.enpassanttarget >> 9) & ~(FILE_H) & board.bitboards[6]) {

            }
        }
        else {

        }
    }
    return PSLMoves;
} 
std::vector<Move> genLegalMoves(Board board) {
    
}