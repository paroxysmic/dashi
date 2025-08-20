#ifndef _ATKGEN_H
#define _ATKGEN_H
#include "bitutil.hpp"
#include "rays.hpp"
#include "board.hpp"
#include "lookuptabs.hpp"
namespace Attack{
    uint64_t getWhitePawnAttacks(uint64_t pos, uint64_t blockers);
    uint64_t getBlackPawnAttacks(uint64_t pos, uint64_t blockers);
    uint64_t getKnightAttacks(uint64_t pos, uint64_t blockers);
    uint64_t getBishopAttacks(uint64_t pos, uint64_t blockers);
    uint64_t getRookAttacks(uint64_t pos, uint64_t blockers);
    uint64_t getQueenAttacks(uint64_t pos, uint64_t blockers);
    uint64_t getKingAttacks(uint64_t pos, uint64_t blockers);
}
#endif