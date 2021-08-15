#include <iostream>

#include "Game.h"


int main() {
    Game *game = new Game();

    game->init("Sudoku", 800, 600);

    while(game->isRunning()) {
        game->handleEvents();
        game->update();
        game->render();
    }

    game->clear();

    return 0;
}