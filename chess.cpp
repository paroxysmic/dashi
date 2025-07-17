#include "chess.hpp"
#include <iostream>
#define set_bit(b, i) ((b) |= (1ULL << (i)))
#define get_bit(b, i) ((b) & (1ULL << (i)))
#define clear_bit(b, i) ((b) &= ~(1ULL << (i)))
#define get_LSB(b) (__builtin_ctzll(b))
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
                std::cout << "\x1b[38;2;" << pr << ';' << pg << ';' << pb << ";48;2;" << r << ';' << g << ';' << b << "m   " << piece << "   ";
            }
            std::cout << "\x1b[38;2;204;204;204;48;2;12;12;12m\n";
        }
    }
    std::cout << "\x1b[38;2;204;204;204;48;2;12;12;12m\n";
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
}
void desc_u64(uint64_t b) {
    for(int i=0;i<8;i++) {
        for(int j=0;j<8;j++) {
            std::cout << (get_bit(b, j + (i << 3)) & 0x01) << ' ';
        }
        std::cout << '\n';
    }
}