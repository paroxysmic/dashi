#include "board.hpp"
#include "lookuptabs.hpp"
#include <cstdlib>
#include <iostream> 
int main() {
    Board board;
    board.initialize();
    board.display();
    return 0;
}