#include "atkgen.hpp"
#include "board.hpp"

int main() {
    Board board;
    board.initialize();
    bool playing = true;    
    while(playing) {
        board.display(true);
        std::cout << "please input square to move from:\n";
        int file, rank;
        do{
            file = std::cin.get() - 'a';
            rank = std::cin.get() - '1';
        }
        while(file > 0 && file <= 8 && rank > 0 && rank <= 8);
        int ind = file + rank * 8;
        std::cout << ind << "please input square to move to:\n";
        file = std::cin.get();
        rank = std::cin.get();
        ind = file + rank * 8;
        std::cout << ind;
    }
    return 0;
}