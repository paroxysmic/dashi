#include "chess.hpp"
#include <iostream>
Board::Board() {
    for(int i=0;i<64;i++) {
        int sq = 1ULL << i;
        KNIGHT_ATTACKS[i] =  (((sq << 6) | (sq >> 10)) & ~(FILE_G | FILE_H)) | 
                    (((sq << 10) | (sq >> 6)) & ~(FILE_A | FILE_B)) |
                    (((sq << 15) | (sq >> 17)) & ~(FILE_A)) | 
                    (((sq >> 15) | (sq << 17)) & ~(FILE_H)); 
        KING_ATTACKS[i] =  (((sq << 7) | (sq >> 1) | (sq >> 9)) & ~(FILE_A)) |
                    (((sq >> 7) | (sq << 1) | (sq << 9)) & ~(FILE_H)) | 
                    (sq >> 8) | (sq << 8);
    }
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

void desc_u64(uint64_t b) {
    for(int i=0;i<8;i++) {
        for(int j=0;j<8;j++) {
            std::cout << (get_bit(b, j + (i << 3)) >> j + (i << 3)) << ' ';
        }
        std::cout << '\n'; 
    }
}
uint64_t shitty_hash(uint64_t key, uint64_t magic, int shift){
    return (key * magic) >> shift;
}




