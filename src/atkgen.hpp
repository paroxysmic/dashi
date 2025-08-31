#ifndef _ATKGEN_H
#define _ATKGEN_H
#include "bitutil.hpp"
#include "rays.hpp"
#include "lookuptabs.hpp"
namespace Attack{
    uint64_t genPSLWhitePawnAttacks(uint64_t pos, uint64_t blockers);
    uint64_t genPSLBlackPawnAttacks(uint64_t pos, uint64_t blockers);
    uint64_t genPSLKnightAttacks(uint64_t pos, uint64_t blockers);
    uint64_t genPSLBishopAttacks(uint64_t pos, uint64_t blockers);
    uint64_t genPSLRookAttacks(uint64_t pos, uint64_t blockers);
    uint64_t genPSLQueenAttacks(uint64_t pos, uint64_t blockers);
    uint64_t genPSLKingAttacks(uint64_t pos, uint64_t blockers);
}
#endif