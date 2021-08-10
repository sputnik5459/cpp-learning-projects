#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>


int main() {
    // TODO: make sudoku maps reading from files
    int game_map[9][9] = {
            {0, 3, 0, 6, 0, 5, 9, 0, 0},
            {0, 9, 8, 0, 3, 4, 2, 0, 0},
            {7, 0, 0, 0, 0, 0, 0, 5, 0},
            //---------------------------
            {6, 8, 0, 0, 9, 0, 4, 0, 0},
            {0, 0, 7, 5, 0, 0, 3, 9, 0},
            {0, 0, 5, 3, 0, 0, 0, 0, 8},
            //---------------------------
            {0, 0, 0, 9, 2, 6, 0, 0, 4},
            {3, 4, 9, 0, 0, 1, 6, 7, 2},
            {0, 5, 6, 0, 7, 3, 0, 8, 0}
    };

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window *win = SDL_CreateWindow("Sudoku", 100, 100, 640, 480, SDL_WINDOW_SHOWN);

    if (win == nullptr){
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr){
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    if (TTF_Init() != 0){
        SDL_Quit();
        return 1;
    }

    bool quitGameLoop = false;
    while(!quitGameLoop) {
        SDL_Event ev;

        if(SDL_PollEvent(&ev) == 0) {
            SDL_Delay(1);
            continue;
        }

        switch(ev.type) {
            case SDL_KEYDOWN:
                quitGameLoop = true;
        }
    }

    SDL_Quit();
    return 0;
}