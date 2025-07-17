#ifndef _CHESS_H
#define _CHESS_H
#include <stdint.h>
class Board{
    public:
        Board();
        void display();
        void initialize();
    uint64_t data[12];
    uint64_t whites;
    uint64_t blacks;
    uint64_t empties;
};
void desc_u64(uint64_t b);
#endif