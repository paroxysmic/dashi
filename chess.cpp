#include "chess.hpp"
#include <iostream>
Move::Move(uint64_t startsquare, uint64_t finalsquare) {
    startsq = startsquare;
    finalsq = finalsquare;
}
Board::Board() {
    for(int i=0;i<12;i++) {
        this->data[i] = 0;
    }
}
void Board::display() {
    //38 is for foreground, 48 is for background
    for(int i=0;i<8;i++) {
        for(int row=0;row<3;row++){
            for(int j=0;j<8;j++) {
                int r, g, b, pr, pg, pb;
                int type = -1;
                for(int k=0;k<12;k++) {
                    if (get_bit(this->data[k], j + i * 8) != 0) {
                        type = k;
                    }
                }
                char piece = row == 1 && type != -1 ? "PNBRQK"[type % 6] : ' ';
                if ((i + j) % 2 == 1) {r = 118; g = 150; b = 86;}
                else {r = 186; g = 202; b = 68;}
                if (type < 6) {pr = 255; pg = 255; pb = 255;}
                else {pr = 0; pg = 0; pb = 0;}
                std::cout << "\x1b[38;2;" << pr << ';' << pg << ';' << pb << ";48;2;" << r << ';' << g << ';' << b << "m   " << piece << "   " ;
            }
            char endc = row == 1 ? 8 - i + '0' : ' ';
            std::cout << "\x1b[38;2;204;204;204;48;2;12;12;12m" << endc << '\n';
        } 
    }
    std::cout << "\x1b[38;2;204;204;204;48;2;12;12;12m   A      B      C      D      E      F      G      H\n";
}
void Board::initialize() {
    for(int i=0;i<8;i++) {
        set_bit(this->data[0], i + 48);
        set_bit(this->data[6], i + 8);
    }
    for(int i=0;i<2;i++) {
        for(int j=0;j<2;j++) {
            set_bit(this->data[7 - 6 * i], 56 * i + 3 * j + 2);
            set_bit(this->data[8 - 6 * i], 56 * i + 5 * j + 1);
            set_bit(this->data[9 - 6 * i], 56 * i + 7 * j);
        }
        set_bit(this->data[10 - 6 * i], 56 * i + 3);
        set_bit(this->data[11 - 6 * i], 56 * i + 4);
    }
    whites = RANK_1 | RANK_2;
    blacks = RANK_7 | RANK_8;
    empties = RANK_3 | RANK_4 | RANK_5 | RANK_6;
    }
std::array<uint64_t, 64> Board::gen_bishop_masks() {
    int direcs[4] = {9, 7, -7, -9};
    uint64_t bounds[4] = {RANK_1 | FILE_H, RANK_1 | FILE_A, RANK_8 | FILE_A, RANK_8 | FILE_H};
    std::array<uint64_t, 64> masks = {0};
    for (int ind=0;ind<64;++ind) {
        for(int i=0;i<4;++i) {
            int curr = ind;
            for(int j=0;j<6;++j) {
                curr += direcs[i];
                if (((bounds[i] & (1ULL << curr)) != 0)){
                    break;
                }
                masks[i] |= (1ULL << curr);
            }
        }
    }
    return masks;
}   
std::array<uint64_t, 64> Board::gen_rook_masks() {
    int direcs[4] = {8, 1, -1, -8};
    uint64_t bounds[4] = {RANK_1 | RANK_8, FILE_A | FILE_H, FILE_A | FILE_H, RANK_1 | RANK_8};
    std::array<uint64_t, 64> masks = {0};
    for (int ind=0;ind<64;++ind) {
        for(int i=0;i<4;++i) {
            int curr = ind;
            for(int j=0;j<6;++j) {
                curr += direcs[i];
                if (((bounds[i] & (1ULL << curr)) != 0)){
                    break;
                }
                masks[i] |= (1ULL << curr);
            }
        }
    }
    return masks;
}     
uint64_t Board::getPSLPawnMoves(uint64_t pos, enum Team team) {
    uint64_t mov = ((team == BLACK) ? pos << 8 : pos >> 8) & empties;
    uint64_t atk = ((mov >> 1) & ~(FILE_A)) | ((mov << 1) & ~(FILE_H));
    uint64_t enemy = team == BLACK ? whites : blacks;
    return mov | (atk & enemy);
}
uint64_t Board::getPSLKnightMoves(uint64_t pos, enum Team team) {
    uint64_t pslm = (((pos << 6) | (pos >> 10)) & ~(FILE_G | FILE_H)) | 
                    (((pos << 10) | (pos >> 6)) & ~(FILE_A | FILE_B)) |
                    (((pos << 15) | (pos >> 17)) & ~(FILE_A)) | 
                    (((pos >> 15) | (pos << 17)) & ~(FILE_H));
    pslm &= ~(team == BLACK ? whites : blacks);
    return pslm;
}
uint64_t Board::getPSLBishopMoves(uint64_t pos, enum Team team) {
    uint64_t pslm = 0;
    uint64_t blockers = blacks & whites;
    int direcs[4] = {-9, -7, 7, 9};
    int borders[4] = {FILE_H, FILE_H, FILE_A, FILE_A};
    for(int i=0;i<4;i++) {
        uint64_t cpos = pos;
        for(int j=0;j<6;j++) {
            cpos = direcs > 0 ? cpos << direcs[i]: cpos >> -direcs[i];
            pslm &= cpos;
            if (((cpos & borders[i]) != 0) || (blockers & cpos != 0)) {
                break;
            }
        }
    }
    pslm &= ~(team == BLACK ? blacks : whites); 
    return pslm;
}
uint64_t Board::getPSLRookMoves(uint64_t pos, enum Team team) {
    uint64_t pslm = 0;
    uint64_t blockers = blacks & whites;
    int direcs[4] = {-8, -1, 1, 8};
    int borders[4] = {0, FILE_H, FILE_A, 0};
    for(int i=0;i<4;i++) {
        uint64_t cpos = pos;
        for(int j=0;j<6;j++) {
            cpos = direcs > 0 ? cpos << direcs[i]: cpos >> -direcs[i];
            pslm &= cpos;
            if (((cpos & borders[i]) != 0) || (blockers & cpos != 0)) {
                break;
            }
        }
    }
    pslm &= ~(team == BLACK ? blacks : whites); 
    return pslm;
}
uint64_t Board::getPSLQueenMoves(uint64_t pos, enum Team team) {
    return getPSLRookMoves(pos, team) & getPSLBishopMoves(pos, team);
}
uint64_t Board::getPSLKingMoves(uint64_t pos, enum Team team) {
    uint64_t pslm = (((pos << 7) | (pos >> 1) | (pos >> 9)) & ~(FILE_A)) |
                    (((pos >> 7) | (pos << 1) | (pos << 9)) & ~(FILE_H)) | 
                    (pos >> 8) | (pos << 8);
    pslm &= ~(team == BLACK ? whites : blacks);
    return pslm;
}
void desc_u64(uint64_t b) {
    for(int i=0;i<8;i++) {
        for(int j=0;j<8;j++) {
            std::cout << (get_bit(b, j + (i << 3)) >> j + (i << 3)) << ' ';
        }
        std::cout << '\n'; 
    }
}




