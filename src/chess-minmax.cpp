#include "board.hpp"
#include "lookuptabs.hpp"
#include "atkgen.hpp"
#include <cstdlib>
#include <iostream> 
int main() {
    uint64_t pos = RANK_4 & FILE_E;
    uint64_t blockers = 0x4122000000224100ULL;
    uint64_t atks = 0;
    uint64_t masked_blockers = 0;
    uint64_t closest_blocker = 0;
    //NORTH-WEST CHECK
    masked_blockers = getray(0, pos) & blockers;
    closest_blocker = get_LSB(masked_blockers | HIGH);
    atks |= (getray(4, closest_blocker) | closest_blocker) & getray(0, pos);
    //NORTH-EAST CHECK
    masked_blockers = getray(2, pos) & blockers;
    closest_blocker = get_LSB(masked_blockers | HIGH);
    atks |= (getray(6, closest_blocker) | closest_blocker) & getray(2, pos);
    //SOUTH-EAST CHECK
    masked_blockers = getray(4, pos) & blockers;
    closest_blocker = get_MSB(masked_blockers | 1);
    atks |= (getray(0, closest_blocker) | closest_blocker) & getray(4, pos);
    //SOUTH-WEST CHECK
    masked_blockers = getray(6, pos) & blockers;
    closest_blocker = get_MSB(masked_blockers | 1);
    atks |= (getray(2, closest_blocker) | closest_blocker) & getray(6, pos);
    desc_u64(blockers);
    desc_u64(atks);
    return 0;
}