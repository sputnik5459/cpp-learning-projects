#include "Game.h"


SDL_Texture *texture;
SDL_Rect dRect;

void Game::init(const char *title, int width, int height) {
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        win = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, false);
        rend = SDL_CreateRenderer(win, -1, 0);
        SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
        gameIsRunning = true;
    } else {
        std::cerr << "SDL Init failed" << SDL_GetError() << std::endl;
        gameIsRunning = false;
        return;
    }

    //TODO: figure out the issue with "Couldn't open"
    //SDL_Surface* tmpSurf = IMG_Load("assets/one.png");
    SDL_Surface* tmpSurf = IMG_Load("/home/ganymede/CLionProjects/cpp-learning-projects/sudoku/assets/five.png");

    if(!tmpSurf) {
        std::cerr << "Failed to load img: " << SDL_GetError() << std::endl;
    }
    texture = SDL_CreateTextureFromSurface(rend, tmpSurf);
    SDL_FreeSurface(tmpSurf);
}

void Game::clear() {
    SDL_DestroyWindow(win);
    SDL_DestroyRenderer(rend);
    SDL_Quit();
}

void Game::handleEvents() {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch(event.type) {
        case SDL_QUIT:
        case SDL_KEYDOWN:
            gameIsRunning = false;
            break;
        default:
            break;
    }
}

void Game::update() {
    dRect.w = 32;
    dRect.h = 32;
}

void Game::render() {
    SDL_RenderClear(rend);
    SDL_RenderCopy(rend, texture, nullptr, &dRect);
    SDL_RenderPresent(rend);
}

bool Game::isRunning() const {
    return gameIsRunning;
}

//void Game::loadSudokuMap(char *filePath, char gameMap[][9]) {
//    gameMap = {
//            {"030605900"},
//            {"098034200"},
//            {"700000050"},
//            {"680090400"},
//            {"007500390"},
//            {"005300008"},
//            {"000926004"},
//            {"349001672"},
//            {"056073080"}
//    };
//
//}
