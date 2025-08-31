#include "atkgen.hpp"
uint64_t Attack::genPSLWhitePawnAttacks(uint64_t pos, uint64_t blockers){
    uint64_t capt = ((pos << 7) & (~(FILE_A) | blockers)) | ((pos << 9) & (~(FILE_H) | blockers));
    return capt | ((pos << 8) & ~(blockers));
}
uint64_t Attack::genPSLBlackPawnAttacks(uint64_t pos, uint64_t blockers){
    uint64_t capt = ((pos >> 7) & (~(FILE_H) | blockers)) | ((pos >> 9) & (~(FILE_A) | blockers));
    return capt | ((pos >> 8) & ~(blockers));
}
uint64_t Attack::genPSLKnightAttacks(uint64_t pos, uint64_t blockers) {
    uint64_t pslm = KNIGHT_ATTACKS[get_trailing_zeros(pos)];
    pslm &= ~blockers;
    return pslm;
}
uint64_t Attack::genPSLBishopAttacks(uint64_t pos, uint64_t blockers) {
    uint64_t atks = 0;
    uint64_t masked_blockers = 0;
    uint64_t closest_blocker = 0;
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
uint64_t Attack::genPSLRookAttacks(uint64_t pos, uint64_t blockers) {
    uint64_t atks = 0;
    uint64_t masked_blockers = 0;
    uint64_t closest_blocker = 0;
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
uint64_t Attack::genPSLQueenAttacks(uint64_t pos, uint64_t blockers) {
    return Attack::genPSLRookAttacks(pos, blockers) & Attack::genPSLBishopAttacks(pos, blockers);
}
uint64_t Attack::genPSLKingAttacks(uint64_t pos, uint64_t blockers) {
    uint64_t pslm = KING_ATTACKS[get_trailing_zeros(pos)];
    pslm &= ~blockers;
    return pslm;
}