#pragma once

#include <iostream>
#include <vector>

#include <SDL2/SDL.h>
#include "SDL2/SDL_image.h"

#include "CellObject.h"


class Game {
public:
    void init(const char* title, int width, int height);
    void handleEvents();
    void update();
    void render();
    void clear();
    [[nodiscard]] bool isRunning() const;

private:
    void genGameMap();
    static void loadGameMapFromFile(char* filepath, char* gameMap);
    void drawMap();
    bool gameIsRunning;
    SDL_Window *win;
    SDL_Renderer *rend;
    char gameMap[82];
    char userMap[82];
    // TODO: think about map and sizeOf iteration..
    SDL_Texture *textures[82];
    CellObject *cells[82];
    SDL_Rect *rects[82];
    int cursor[2];
};
