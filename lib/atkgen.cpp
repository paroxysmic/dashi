#include "atkgen.hpp"
U64 genPSLWhitePawnAttacks(U64 pos, U64 blockers){
    U64 capt = ((pos << 7) & (~(FILE_A) | blockers)) | ((pos << 9) & (~(FILE_H) | blockers));
    return capt | ((pos << 8) & ~(blockers));
}
U64 genPSLBlackPawnAttacks(U64 pos, U64 blockers){
    U64 capt = ((pos >> 7) & (~(FILE_H) | blockers)) | ((pos >> 9) & (~(FILE_A) | blockers));
    return capt | ((pos >> 8) & ~(blockers));
}
U64 genPSLKnightAttacks(U64 pos, U64 blockers) {
    U64 pslm = KNIGHT_ATTACKS[get_trailing_zeros(pos)];
    pslm &= ~blockers;
    return pslm;
}
U64 genPSLBishopAttacks(U64 pos, U64 blockers) {
    U64 atks = 0;
    U64 masked_blockers = 0;
    U64 closest_blocker = 0;
    //NORTH-WEST CHECK
    masked_blockers = blockers & getray(0, pos);
    closest_blocker = get_LSB(masked_blockers | HIGH);
    atks |= getray(0, pos) ^ getray(0, closest_blocker);
    //NORTH-EAST CHECK
    masked_blockers = blockers & getray(2, pos);
    closest_blocker = get_LSB(masked_blockers | HIGH);
    atks |= getray(2, pos) ^ getray(2, closest_blocker);
    //SOUTH-EAST CHECK
    masked_blockers = blockers & getray(4, pos);
    closest_blocker = get_MSB(masked_blockers | 1ULL);
    atks |= getray(4, pos) ^ getray(4, closest_blocker);
    //SOUTH-WEST CHECK
    masked_blockers = blockers & getray(6, pos);
    closest_blocker = get_MSB(masked_blockers | 1ULL);
    atks |= getray(6, pos) ^ getray(6, closest_blocker);
    return atks;
}
U64 genPSLRookAttacks(U64 pos, U64 blockers) {
    U64 atks = 0;
    U64 masked_blockers = 0;
    U64 closest_blocker = 0;
    //NORTH CHECK
    masked_blockers = blockers & getray(1, pos);
    closest_blocker = get_LSB(masked_blockers | HIGH);
    atks |= getray(1, pos) ^ getray(1, closest_blocker);
    //EAST CHECK
    masked_blockers = blockers & getray(3, pos);
    closest_blocker = get_LSB(masked_blockers | HIGH);
    atks |= getray(3, pos) ^ getray(3, closest_blocker);
    //SOUTH CHECK
    masked_blockers = blockers & getray(5, pos);
    closest_blocker = get_MSB(masked_blockers | 1ULL);
    atks |= getray(5, pos) ^ getray(5, closest_blocker);
    //WEST CHECK
    masked_blockers = blockers & getray(7, pos);
    closest_blocker = get_MSB(masked_blockers | 1ULL);
    atks |= getray(7, pos) ^ getray(7, closest_blocker);
    return atks;
}
U64 genPSLQueenAttacks(U64 pos, U64 blockers) {
    return genPSLRookAttacks(pos, blockers) & genPSLBishopAttacks(pos, blockers);
}
U64 genPSLKingAttacks(U64 pos, U64 blockers) {
    U64 pslm = KING_ATTACKS[get_trailing_zeros(pos)];
    pslm &= ~blockers;
    return pslm;
}

