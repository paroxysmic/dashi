#include "board.hpp"
Board::Board() {
    for(int i=0;i<12;i++) {
        bitboards[i] = 0;
    }
    whites = 0;
    blacks = 0;
    empties = -1;
    castlingrights = 0x0f;
    whitesturn = true;
    halfmovecount = 0;
    movecount = 1;
}
void Board::display() {
    //38 is for foreground, 48 is for background
    for(int i=0;i<8;i++) {
        for(int row=0;row<3;row++){
            for(int j=0;j<8;j++) {
                int r, g, b, pr, pg, pb;
                int type = -1;
                for(int k=0;k<12;k++) {
                    if (get_bit(bitboards[k], j + i * 8) != 0) {
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
    setToFEN("RNBQKBNR/PPPPPPPP/8/8/8/8/pppppppp/rnbqkbnr w KQkq - 0 1");    
}
void Board::setToFEN(std::string FEN) {
    for(int i=0;i<12;i++) {
        bitboards[i] = 0;
    }
    whites = 0;
    blacks = 0;
    empties = -1;
    castlingrights = 0;
    std::istringstream fenStringStream(FEN);
    std::string chunk;
    fenStringStream >> chunk;
    int pos = 56;
    //starts at a8 
    for(char c: chunk) {
        switch (c){
            case 'P': bitboards[0] |= (1ULL << pos++);
                break;
            case 'N': bitboards[1] |= (1ULL << pos++);
                break;
            case 'B': bitboards[2] |= (1ULL << pos++);
                break;
            case 'R': bitboards[3] |= (1ULL << pos++);
                break;
            case 'Q': bitboards[4] |= (1ULL << pos++);
                break;
            case 'K': bitboards[5] |= (1ULL << pos++);
                break;
            case 'p': bitboards[6] |= (1ULL << pos++);
                break;
            case 'n': bitboards[7] |= (1ULL << pos++);
                break;
            case 'b': bitboards[8] |= (1ULL << pos++);
                break;
            case 'r': bitboards[9] |= (1ULL << pos++);
                break;
            case 'q': bitboards[10] |= (1ULL << pos++);
                break;
            case 'k': bitboards[11] |= (1ULL << pos++);
                break;
            case '/': pos -= 16;
                break;
            default: pos += (c - '0');

        }
    }
    fenStringStream >> chunk;
    whitesturn = chunk[0] == 'w';
    fenStringStream >> chunk;
    for(char c: chunk) {
        switch(c) {
            case 'Q': castlingrights |= 0x01;
                break;
            case 'K': castlingrights |= 0x02;
                break;
            case 'q': castlingrights |= 0x04;
                break;
            case 'k': castlingrights |= 0x08;
                break;
            case '-': castlingrights = 0;
                break;
        }
    }
    fenStringStream >> chunk;
    if(chunk == "-") {
        enpassanttarget = 0;
    }
    else {    
        int ind = chunk[0] - 'a' + 8 * (chunk[1] - '1');
        enpassanttarget = 1ULL << (ind);
    }
    fenStringStream >> chunk;
    halfmovecount = std::stoi(chunk);
    fenStringStream >> chunk;
    movecount = std::stoi(chunk);
}
void Board::debugPrint() {
    std::cout << "whitesturn: " << (whitesturn ? "true!" : "false!") << '\n';
    int eptpos = get_trailing_zeros(enpassanttarget);
    std::cout << "enpassanttarget: ";
    if(enpassanttarget == 0) {
        std::cout << "none!";
    }
    else {
        std::cout << eptpos;
    }
    std::cout << "\nhalfmoves clock: " << (int) halfmovecount << '\n';
    std::cout << "fullmoves clock: " << movecount << '\n';
    std::cout << "castling rights: "; 
    char castlingRightChars[4] = {'Q', 'K', 'q', 'k'};
    for(int i=0;i<4;i++) {
        if((castlingrights >> i) & 1) { 
            std::cout << castlingRightChars[i];
        }
    }
    std::cout << '\n';
}
void Board::makeMove(Move move) {
    if(move.is_castle != 0) {
        if(move.is_castle[0]) {
            bitboards[WHITE_KING] = RANK_1 & FILE_C;
            bitboards[WHITE_ROOK] ^= ((RANK_1 & (FILE_A | FILE_D)));
        }
        if(move.is_castle[1]) {
            bitboards[WHITE_KING] = RANK_1 & FILE_G;
            bitboards[WHITE_ROOK] ^= ((RANK_1 & (FILE_F | FILE_H)));
        }
        if(move.is_castle[2]) {
            bitboards[BLACK_KING] = RANK_8 & FILE_C;
            bitboards[BLACK_ROOK] ^= ((RANK_8 & (FILE_A | FILE_D)));
        }
        if(move.is_castle[3]) {
            bitboards[BLACK_KING] = RANK_8 & FILE_G;
            bitboards[BLACK_ROOK] ^= ((RANK_1 & (FILE_F | FILE_H)));
        }
    }
    whitesturn = !whitesturn;
    castlingrights = move.end_castlingrights;
    for(int i=0;i<12;i++) {
        
    }
}
void Board::unmakeMove(Move move) {
    if(move.is_castle != 0) {
        if(move.is_castle[0]) {
            bitboards[WHITE_KING] = RANK_1 & FILE_E;
            bitboards[WHITE_ROOK] ^= ((RANK_1 & (FILE_A | FILE_D)));
        }
        if(move.is_castle[1]) {
            bitboards[WHITE_KING] = RANK_1 & FILE_E;
            bitboards[WHITE_ROOK] ^= ((RANK_1 & (FILE_F | FILE_H)));
        }
        if(move.is_castle[2]) {
            bitboards[BLACK_KING] = RANK_8 & FILE_E;
            bitboards[BLACK_ROOK] ^= ((RANK_8 & (FILE_A | FILE_D)));
        }
        if(move.is_castle[3]) {
            bitboards[BLACK_KING] = RANK_8 & FILE_E;
            bitboards[BLACK_ROOK] ^= ((RANK_8 & (FILE_F | FILE_H)));
        }
    }
    whitesturn = !whitesturn;      
    castlingrights = move.init_castlingrights;
}
