#pragma once 
#include "bitutil.hpp"
#include "lookuptabs.hpp"
U64 genPSLWhitePawnAttacks(U64 pos, U64 blockers);
U64 genPSLBlackPawnAttacks(U64 pos, U64 blockers);
U64 genPSLKnightAttacks(U64 pos, U64 blockers);
U64 genPSLBishopAttacks(U64 pos, U64 blockers);
U64 genPSLRookAttacks(U64 pos, U64 blockers);
U64 genPSLQueenAttacks(U64 pos, U64 blockers);
U64 genPSLKingAttacks(U64 pos, U64 blockers);