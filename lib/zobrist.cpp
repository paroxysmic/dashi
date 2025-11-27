#include <zobrist.hpp>

constexpr U64 splitmix64(U64 &x) {
  U64 z = (x += 0x9e3779b97f4a7c15);
  z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
  z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
  return z ^ (z >> 31);
}
constexpr std::array<std::array<U64, 64>, 12> init_zobrist(){
   std::array<std::array<U64, 64>, 12> randvals{};
   U64 seed = 676767676767;
   for(int i=0;i<12;i++) {
      for(int j=0;j<64;j++) {
         randvals[i][j] = splitmix64(seed);
      }
   }
   return randvals;
}
const std::array<std::array<U64, 64>, 12> ZOBRIST = init_zobrist();