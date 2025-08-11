#ifndef _CHESS_H
#define _CHESS_H
#include <cstdint>
#include <array>
#include <vector>
#define set_bit(b, i) ((b) |= (1ULL << (i)))
#define get_bit(b, i) ((b) & (1ULL << (i)))
#define clear_bit(b, i) ((b) &= ~(1ULL << (i)))
constexpr uint64_t lshif(uint64_t num, int shift){
    return (shift > 0) ? num << shift : num >> -shift;
}
#define rshif(b, s) ((s > 0) ? (b >> (s)) : (b << (-s)))
constexpr uint64_t FILE_A = 0x0101010101010101ULL;
constexpr uint64_t FILE_B = 0x0202020202020202ULL;
constexpr uint64_t FILE_C = 0x0404040404040404ULL;
constexpr uint64_t FILE_D = 0x0808080808080808ULL;
constexpr uint64_t FILE_E = 0x1010101010101010ULL;
constexpr uint64_t FILE_F = 0x2020202020202020ULL;
constexpr uint64_t FILE_G = 0x4040404040404040ULL;
constexpr uint64_t FILE_H = 0x8080808080808080ULL;
constexpr uint64_t RANK_1 = 0x00000000000000FFULL;
constexpr uint64_t RANK_2 = 0x000000000000FF00ULL;
constexpr uint64_t RANK_3 = 0x0000000000FF0000ULL;
constexpr uint64_t RANK_4 = 0x00000000FF000000ULL;
constexpr uint64_t RANK_5 = 0x000000FF00000000ULL;
constexpr uint64_t RANK_6 = 0x0000FF0000000000ULL;
constexpr uint64_t RANK_7 = 0x00FF000000000000ULL;
constexpr uint64_t RANK_8 = 0xFF00000000000000ULL;
extern uint64_t rookmagics[64];
extern uint64_t bishopmagics[64];
enum Team{
    WHITE = 0, 
    BLACK = 1,
    NONE = 2 
};
struct Move{
    Move(uint64_t ssq, uint64_t fsq);
    uint64_t startsq;
    uint64_t finalsq;
};
constexpr std::array<uint64_t, 64> gen_king_attacks() {
    std::array<uint64_t, 64> kgatks = {};
    for(int i=0;i<64;i++) {
        uint64_t pos = 1ULL << i;
        kgatks[i] = (((pos << 7) | (pos >> 1) | (pos >> 9)) & ~(FILE_A)) |
                    (((pos >> 7) | (pos << 1) | (pos << 9)) & ~(FILE_H)) | 
                    (pos >> 8) | (pos << 8);
    }
    return kgatks;
}
constexpr std::array<uint64_t, 64> gen_knight_attacks() {
    std::array<uint64_t, 64> knatks = {};
    for(int i=0;i<64;i++) {
        uint64_t pos = 1ULL << i;
        knatks[i] = (((pos << 6) | (pos >> 10)) & ~(FILE_G | FILE_H)) | 
                    (((pos << 10) | (pos >> 6)) & ~(FILE_A | FILE_B)) |
                    (((pos << 15) | (pos >> 17)) & ~(FILE_A)) | 
                    (((pos >> 15) | (pos << 17)) & ~(FILE_H));
    }
    return knatks;
}
constexpr std::array<uint64_t, 64> gen_bishop_masks() {
    std::array<uint64_t, 64> masks = {0};
    int direcs[8] = {-1, -1, -1, 1, 1, -1, 1, 1 };
    for(int i=0;i<64;i++) {
        int row = i & 7;
        int col = i >> 3;
        uint64_t atkbrd = 0;
        for(int j=0;j<4;j++) {
            int r = row;
            int c = col;
            bool unblocked = true;
            while(unblocked) {
                r += direcs[j * 2];
                c += direcs[j * 2 + 1];
                unblocked = !((r > 6) || (r < 1) || (c > 6) || (c < 1));
                if(unblocked) {
                    atkbrd += 1ULL << (r + c * 8);
                }
            }
        }
        masks[i] = atkbrd;
    }
    return masks;
}   
constexpr std::array<uint64_t, 64> gen_rook_masks() {
    std::array<uint64_t, 64> masks = {};
    uint64_t files[8] = {FILE_A, FILE_B, FILE_C, FILE_D, FILE_E, FILE_F, FILE_G, FILE_H};
    uint64_t ranks[8] = {RANK_1, RANK_2, RANK_3, RANK_4, RANK_5, RANK_6, RANK_7, RANK_8};
    for(int i=0;i<8;i++) {
        for(int j=0;j<8;j++) {
            masks[i + j * 8] = (files[i] & ~(RANK_1 | RANK_8)) ^ (ranks[j] & ~(FILE_A | FILE_H));
            masks[i + j * 8] &= ~(files[i] & ranks[j]);
        } 
    }
    return masks;
} 
class Board{
    public:
        Board();
        void display();
        void initialize();
        std::array<uint64_t, 12> data = {0};
        uint64_t whites = 0;
        uint64_t blacks = 0;
        uint64_t empties = -1;   
        static constexpr std::array<uint64_t, 64> KING_ATTACKS = gen_king_attacks();
        static constexpr std::array<uint64_t, 64> KNIGHT_ATTACKS = gen_knight_attacks();
        static constexpr std::array<uint64_t, 64> BISHOP_MASKS = gen_bishop_masks();
        static constexpr std::array<uint64_t, 64> ROOK_MASKS = gen_rook_masks();   
        uint64_t getPSLPawnMoves(uint64_t pos, enum Team team);
        uint64_t getPSLKnightMoves(uint64_t pos, enum Team team);
        uint64_t getPSLBishopMoves(uint64_t pos, enum Team team);
        uint64_t getPSLRookMoves(uint64_t pos, enum Team team);
        uint64_t getPSLQueenMoves(uint64_t pos, enum Team team);
        uint64_t getPSLKingMoves(uint64_t pos, enum Team team);    
        
};
void desc_u64(uint64_t b);
uint64_t shitty_hash(uint64_t key, uint64_t magic);
uint64_t gen_rook_attack_board(uint64_t pos, uint64_t blockers);
uint64_t gen_bishop_attack_board(uint64_t pos, uint64_t blockers);
int get_trailing_bits(uint64_t v);
int bitcount(uint64_t num);
std::vector<uint64_t> gen_bit_combs(uint64_t bitmask);
#endif