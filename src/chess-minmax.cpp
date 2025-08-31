#include "board.hpp"
#include "atkgen.hpp"
int main() {
    Board board;
    board.initialize();
    board.display();
    board.debugPrint();
    return 0;
}