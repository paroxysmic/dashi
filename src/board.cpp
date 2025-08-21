#include "board.hpp"

Board::Board() {
    for(int i=0;i<12;i++) {
        data[i] = 0;
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
    setToFEN("RNBQKBNR/PPPPPPPP/8/8/8/8/pppppppp/rnbqkbnr w KQkq - 0 1");    
}
void Board::setToFEN(std::string FEN) {
    for(int i=0;i<12;i++) {
        data[i] = 0;
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
            case 'P': data[0] |= (1ULL << pos++);
                break;
            case 'N': data[1] |= (1ULL << pos++);
                break;
            case 'B': data[2] |= (1ULL << pos++);
                break;
            case 'R': data[3] |= (1ULL << pos++);
                break;
            case 'Q': data[4] |= (1ULL << pos++);
                break;
            case 'K': data[5] |= (1ULL << pos++);
                break;
            case 'p': data[6] |= (1ULL << pos++);
                break;
            case 'n': data[7] |= (1ULL << pos++);
                break;
            case 'b': data[8] |= (1ULL << pos++);
                break;
            case 'r': data[9] |= (1ULL << pos++);
                break;
            case 'q': data[10] |= (1ULL << pos++);
                break;
            case 'k': data[11] |= (1ULL << pos++);
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
    halfmovecount = atoi(chunk.c_str());
    fenStringStream >> chunk;
    movecount = atoi(chunk.c_str());
}
void Board::debugPrint() {
    std::cout << "whitesturn: " << whitesturn << '\n';
    std::cout << "enpassanttarget: " << get_trailing_zeros(enpassanttarget) << '\n';
    std::cout << "halfmoves clock: " << halfmovecount << '\n';
    std::cout << "castling rights: " << castlingrights << '\n'; 
}

