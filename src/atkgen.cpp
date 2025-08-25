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
    //CLASSICAL APPROACH
    return 0ULL;
}
uint64_t Attack::getRookAttacks(uint64_t pos, uint64_t blockers) {
    //include the last element from the blockers, 
    //so we don't have to differentiate 
    uint64_t mask = 0;
    uint64_t masked_blockers = 0;
    //NORTH CHECK (1)
    masked_blockers = blockers & RAYS[1][get_trailing_zeros(pos)];
    
    //uint64_t lsb
    //EAST CHECK (3)
    //SOUTH CHECK (5)
    //WEST CHECK (7)

    return mask;
}
uint64_t Attack::getQueenAttacks(uint64_t pos, uint64_t blockers) {
    return Attack::getRookAttacks(pos, blockers) & Attack::getBishopAttacks(pos, blockers);
}
uint64_t Attack::getKingAttacks(uint64_t pos, uint64_t blockers) {
    uint64_t pslm = KING_ATTACKS[get_trailing_zeros(pos)];
    pslm &= ~blockers;
    return pslm;
}