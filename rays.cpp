#include "rays.hpp"
#include <string>
#include <iostream>
constexpr std::array<std::array<uint64_t, 64>, 8> gen_rays(){
    //rays start at northwest and move clockwise
    int direcs[8] = {7, 8, 9, 1, -7, -8, -9, -1};
    uint64_t blockers[8] = {FILE_H, 0, FILE_A, FILE_A, FILE_A, 0, FILE_H, FILE_H};
    std::array<std::array<uint64_t, 64>, 8> rays = {0};
    for(int i=0;i<64;++i) {
        uint64_t pos = 1ULL << i;
        for(int j=0;j<8;++j) {
            uint64_t ray = 0;
            int direc = direcs[j];
            bool unblocked = true;
            uint64_t cpos = pos;
            uint64_t blocker = blockers[j];
            while(unblocked) {
                cpos = lshif(cpos, direc);
                if((cpos == 0) || ((blocker & cpos) != 0)) {
                    break;
                }
                if(unblocked) {
                    ray |= cpos;
                }
            }
            rays[j][i] = ray;
        }
    }
    return rays;
}
int main() {
    std::array<std::array<uint64_t, 64>, 8> rays = gen_rays();
    for(int i=0;i<8;i++) {
        std::string buf = "{";
        for(int j=0;j<64;j++) {
            buf += std::to_string(rays[i][j]);
            if(j != 63) {
                buf += ',';
            }
        }
        buf += "}\n";
        std::cout << buf;
    }
    return 0;
}