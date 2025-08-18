#include "board.hpp"
uint64_t rookmagics[64] = {0x5080002840008011, 0xd60001000200a80, 0x2800100120001a, 0x480120410000800, 0x2050201001000400, 0x20010c048c0200, 
    0x2e000800458100, 0x8100005823000082, 0x1410900080061302, 0x20a4128008440221, 0x90020423201040, 0x802880030008010, 0x8000400440010200, 
    0x2080a0111024008, 0xc000400041040088, 0x4220088000a241, 0x48410010208001, 0x4440210009008010, 0xa40400e004820320, 0x9040400883000, 
    0x6002a00800420140, 0x32018021010400, 0xc96005000c40809, 0xa000400880a040, 0x1080004040204208, 0x54400004200220, 0xc020010008081010, 
    0x4ec04010c1041000, 0x4120840800980041, 0x2000010180040042, 0x10010200c0008200, 0x8248c400c0002880, 0xc488060800095, 0x800200389080040, 
    0x2002100510400, 0x148091050080200, 0x4002002042000403, 0x4000c8400150200, 0x80200100c880060, 0x88040200040, 0xa1002082042010, 0x2500041982800, 
    0x80809060044400, 0x4000b00286210080, 0x2080200560001, 0x10043091000a010, 0x480024c001100808, 0x4090a0080060404, 0x1109104080001100, 
    0x402019001001e4a0, 0x80004c020001100, 0x114048004080082, 0x205000408b01100, 0x2058a0414210080, 0x8a100400421100, 0x881000080422300,
    0x1200820020410116, 0x88819020a0042, 0x80d004402202, 0x400013020040a09a, 0x31200600482, 0x2000085100402, 0x10808805021004, 0x30012081004412};
uint64_t bishopmagics[64] = {0x4400080048020a6, 0x2004004024000c40, 0x8848000108042020, 0x4004102008020000, 0x20852005008000, 0x50008000064, 
    0xc400940088, 0x501800204022200, 0xa00108400540, 0x880002090308, 0x10200c2408802400, 0x924090008080000, 0x130840210040421, 0xc39020840, 
    0x820001008000801, 0x4041100141200, 0x48800210040220, 0x400020a20128, 0x2020040028010908, 0x100080410801008, 0x1200850404094153, 
    0x6080102802003c10, 0x881000511480110, 0x89208a000680200, 0xc029014108028101, 0x128008202001, 0x10014434002012, 0x40100022c8080,
    0x4004010004410000, 0x42020906840a222, 0x2000080404202, 0x101060004e0042a9, 0x20080402101000, 0x80a412200030022, 0x4128800a0080051, 
    0x80c0908820110010, 0x8001409028018440, 0x8d100400400, 0x404404490008024, 0x2000620401020008, 0x83044008126006, 0x202220500208080, 
    0x100000d4880881, 0x8000004088821201, 0x8005008014020050, 0x801082802109, 0x2120004003000004, 0x8421b1404010881, 0x200000a010220109, 
    0x2200008010a008, 0x220040400, 0x410242440009200, 0x820006020402000, 0x620c00aa0a940001, 0x40a1008504820800, 0x8000100041080040, 
    0x8080a40108500, 0x2000000022bc0380, 0x8080400200040201, 0x180020800, 0xa010801000c00, 0x21120000a411039c, 0x100001118109a0c0, 0x808500840031402};
int bishopbitnums[64] = {6, 5, 5, 5, 5, 5, 5, 6, 
    5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 7, 7, 7, 7, 5, 5, 
    5, 5, 7, 9, 9, 7, 5, 5, 5, 5, 7, 9, 9, 7, 5, 5, 
    5, 5, 7, 7, 7, 7, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 
    6, 5, 5, 5, 5, 5, 5, 6};
int rookbitnums[64] = {12, 11, 11, 11, 11, 11, 11, 12, 
 11, 10, 10, 10, 10, 10, 10, 11, 11, 10, 10, 10, 10, 10, 10, 11, 
 11, 10, 10, 10, 10, 10, 10, 11, 11, 10, 10, 10, 10, 10, 10, 11, 
 11, 10, 10, 10, 10, 10, 10, 11, 11, 10, 10, 10, 10, 10, 10, 11, 
 12, 11, 11, 11, 11, 11, 11, 12};
Move::Move(uint64_t startsquare, uint64_t finalsquare) {
    startsq = startsquare;
    finalsq = finalsquare;
}
Board::Board() {
    for(int i=0;i<12;i++) {
        data[i] = 0;
    }
}
void Board::display() {
    //38 is for foreground, 48 is for background
    for(int i=0;i<8;i++) {
        for(int row=0;row<3;row++){
            for(int j=0;j<8;j++) {
                int r, g, b, pr, pg, pb;
                int type = -1;
                for(int k=0;k<12;k++) {
                    if (get_bit(data[k], j + i * 8) != 0) {
                        type = k;
                    }
                }
                char piece = row == 1 && type != -1 ? "PNBRQK"[type % 6] : ' ';
                if ((i + j) % 2 == 1) {r = 118; g = 150; b = 86;}
                else {r = 186; g = 202; b = 68;}
                if (type < 6) {pr = 255; pg = 255; pb = 255;}
                else {pr = 0; pg = 0; pb = 0;}
                std::cout << "\x1b[38;2;" << pr << ';' << pg << ';' << pb << ";48;2;" << r << ';' << g << ';' << b << "m   " << piece << "   " ;
            }
            char endc = row == 1 ? 8 - i + '0' : ' ';
            std::cout << "\x1b[38;2;204;204;204;48;2;12;12;12m" << endc << '\n';
        } 
    }
    std::cout << "\x1b[38;2;204;204;204;48;2;12;12;12m   A      B      C      D      E      F      G      H\n";
}
void Board::initialize() {
    data[0] = RANK_7;
    data[6] = RANK_2;
    data[1] = RANK_8 & (FILE_B | FILE_G);
    data[7] = RANK_1 & (FILE_B | FILE_G);
    data[2] = RANK_8 & (FILE_C | FILE_F);
    data[8] = RANK_1 & (FILE_C | FILE_F);
    data[3] = RANK_8 & (FILE_A | FILE_H);
    data[9] = RANK_1 & (FILE_A | FILE_H);
    data[4] = RANK_8 & FILE_D;
    data[10] = RANK_1 & FILE_E;
    data[5] = RANK_8 & FILE_E;
    data[11] = RANK_1 & FILE_D;
    whites = RANK_1 | RANK_2;
    blacks = RANK_7 | RANK_8;
    empties = RANK_3 | RANK_4 | RANK_5 | RANK_6;
    }
uint64_t Board::getPSLPawnMoves(uint64_t pos, enum Team team) {
    uint64_t mov = ((team == BLACK) ? pos << 8 : pos >> 8) & empties;
    uint64_t atk = ((mov >> 1) & ~(FILE_A)) | ((mov << 1) & ~(FILE_H));
    uint64_t enemy = team == BLACK ? whites : blacks;
    return mov | (atk & enemy);
}
uint64_t Board::getPSLKnightMoves(uint64_t pos, enum Team team) {
    uint64_t pslm = KNIGHT_ATTACKS[get_trailing_zeros(pos)];
    pslm &= ~(team == BLACK ? whites : blacks);
    return pslm;
}
uint64_t Board::getPSLBishopMoves(uint64_t pos, enum Team team) {
    //CLASSICAL APPROACH
    return 0ULL;
}
uint64_t Board::getPSLRookMoves(uint64_t pos, Team team) {
    uint64_t mask = 0;
    uint64_t blockers = ~empties;
    //NORTH CHECK (1)
    uint64_t masked_blockers = blockers & RAYS[1][get_trailing_zeros(pos)];
    //uint64_t lsb
    //EAST CHECK (3)
    //SOUTH CHECK (5)
    //WEST CHECK (7)
    uint64_t true_blockers = (team == BLACK) ? blacks : whites;
    mask &= ~true_blockers;
    return mask;
}
uint64_t Board::getPSLQueenMoves(uint64_t pos, enum Team team) {
    return getPSLRookMoves(pos, team) & getPSLBishopMoves(pos, team);
}
uint64_t Board::getPSLKingMoves(uint64_t pos, enum Team team) {
    uint64_t pslm = KING_ATTACKS[get_trailing_zeros(pos)];
    pslm &= ~(team == BLACK ? whites : blacks);
    return pslm;
}
uint64_t gen_rook_attack_board(uint64_t pos, uint64_t blockers) {
    uint64_t atkbrd = 0;
    int direcs[4] = {-8, -1, 1, 8};
    uint64_t borders[4] = {0, FILE_H, FILE_A, 0};
    for(int i=0;i<4;i++) {
        uint64_t cpos = pos;
        while(true) {
            cpos = lshif(cpos, direcs[i]);
            if(borders[i] & cpos || cpos == 0) {
                break;
            }
            atkbrd |= cpos;
            if(cpos & blockers) {
                break;
            }
        }
    }
    return atkbrd;
}   
uint64_t gen_bishop_attack_board(uint64_t pos, uint64_t blockers) {
    uint64_t atkbrd = 0;
    int direcs[4] = {-9, -7, 7, 9};
    uint64_t borders[4] = {FILE_H, FILE_H, FILE_A, FILE_A};
    for(int i=0;i<4;i++) {
        uint64_t cpos = pos;
        while(true) {
            cpos = lshif(cpos, direcs[i]);
            if(borders[i] & cpos || cpos == 0) {
                break;
            }
            atkbrd |= cpos;
            if(cpos & blockers) {
                break;
            }
        }
    }
    return atkbrd;
} 


