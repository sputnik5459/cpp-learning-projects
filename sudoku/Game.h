#pragma once

#include <iostream>

#include <SDL2/SDL.h>
#include "SDL2/SDL_image.h"


class Game {
public:
    void init(const char* title, int width, int height);
    void handleEvents();
    void update();
    void render();
    void clear();
    bool isRunning() const;

private:
    bool gameIsRunning;
    SDL_Window *win;
    SDL_Renderer *rend;
};
