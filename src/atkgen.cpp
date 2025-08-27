#include "atkgen.hpp"
uint64_t Attack::getWhitePawnAttacks(uint64_t pos, uint64_t blockers){
    uint64_t capt = ((pos << 7) & (~(FILE_A) | blockers)) | ((pos << 9) & (~(FILE_H) | blockers));
    return capt | (pos << 8);
}
uint64_t Attack::getBlackPawnAttacks(uint64_t pos, uint64_t blockers){
    uint64_t capt = ((pos >> 7) & (~(FILE_H) | blockers)) | ((pos >> 9) & (~(FILE_A) | blockers));
    return capt | (pos >> 8);
}
uint64_t Attack::getKnightAttacks(uint64_t pos, uint64_t blockers) {
    uint64_t pslm = KNIGHT_ATTACKS[get_trailing_zeros(pos)];
    pslm &= ~blockers;
    return pslm;
}
uint64_t Attack::getBishopAttacks(uint64_t pos, uint64_t blockers) {
    uint64_t atks = 0;
    uint64_t masked_blockers = 0;
    uint64_t closest_blocker = 0;
    //NORTH-WEST CHECK
    masked_blockers = (blockers & getray(0, pos)) | HIGH;
    closest_blocker = get_MSB(masked_blockers);
    atks |= (closest_blocker | getray(4, closest_blocker)) & getray(0, pos);
    //NORTH-EAST CHECK
    masked_blockers = (blockers & getray(2, pos)) | HIGH;
    closest_blocker = get_MSB(masked_blockers);
    atks |= (closest_blocker | getray(6, closest_blocker)) & getray(2, pos);
    //SOUTH-EAST CHECK
    masked_blockers = (blockers & getray(4, pos)) | 1;
    closest_blocker = get_LSB(masked_blockers);
    atks |= (closest_blocker | getray(0, closest_blocker)) & getray(4, pos);
    //SOUTH-WEST CHECK
    masked_blockers = (blockers & getray(6, pos)) | HIGH;
    closest_blocker = get_LSB(masked_blockers);
    atks |= (closest_blocker | getray(2, closest_blocker)) & getray(6, pos);
    return atks;
}
uint64_t Attack::getRookAttacks(uint64_t pos, uint64_t blockers) {
    uint64_t atks = 0;
    uint64_t masked_blockers = 0;
    uint64_t closest_blocker = 0;
    //NORTH CHECK
    masked_blockers = (blockers & getray(1, pos)) | HIGH;
    closest_blocker = get_LSB(masked_blockers);
    atks |= (closest_blocker | getray(5, closest_blocker)) & getray(1, pos);
    //EAST CHECK
    masked_blockers = (blockers & getray(3, pos)) | HIGH;
    closest_blocker = get_LSB(masked_blockers);
    atks |= (closest_blocker | getray(7, closest_blocker)) & getray(3, pos);
    //SOUTH CHECK
    masked_blockers = (blockers & getray(5, pos)) | 1;
    closest_blocker = get_MSB(masked_blockers);
    atks |= (closest_blocker | getray(1, closest_blocker)) & getray(5, pos);
    //WEST CHECK
    masked_blockers = (blockers & getray(7, pos)) | 1;
    closest_blocker = get_MSB(masked_blockers);
    atks |= (closest_blocker | getray(3, closest_blocker)) & getray(7, pos);
    return atks;
}
uint64_t Attack::getQueenAttacks(uint64_t pos, uint64_t blockers) {
    return Attack::getRookAttacks(pos, blockers) & Attack::getBishopAttacks(pos, blockers);
}
uint64_t Attack::getKingAttacks(uint64_t pos, uint64_t blockers) {
    uint64_t pslm = KING_ATTACKS[get_trailing_zeros(pos)];
    pslm &= ~blockers;
    return pslm;
}