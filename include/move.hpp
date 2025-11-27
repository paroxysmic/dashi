#pragma once
#include "bitutil.hpp"
struct Move{
    U64 init_sq;   
    U64 end_sq;
    U8 ptype;
    U8 castle;
    bool enPassant;
}; 