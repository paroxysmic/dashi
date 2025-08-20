#include <cstdint>
#include <random>
uint64_t randu64();
uint64_t shitty_hash(uint64_t key, uint64_t magic);
bool verify_magic(uint64_t magic, int pos, bool checkRooks);