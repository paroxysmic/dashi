#include "board.hpp"
#include "lookuptabs.hpp"
#include "atkgen.hpp"
#include <cstdlib>
#include <iostream> 
int main() {
    uint64_t pos = RANK_5 & FILE_E;
    uint64_t blockers = (RANK_5) & (FILE_C | FILE_G);
    //east check
    uint64_t masked_blockers = blockers & RAYS[3][get_trailing_zeros(pos)];
    uint64_t closest_blocker = get_LSB(blockers);
    desc_u64(closest_blocker);
    return 0;
}