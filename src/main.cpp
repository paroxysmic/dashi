#include "atkgen.hpp"
#include "board.hpp"

int main() {
    Board board;
    board.initialize();
    board.display(true);
    board.display(false);
    return 0;
}