#include "Game.h"
#include "CellObject.h"

#include <fstream>
#include <map>
#include "string"


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
    genGameMap();
    std::cout << "Game successfully init" << std::endl;
    cursor[0] = 0;
    cursor[1] = 0;
}

void Game::clear() {
    SDL_DestroyWindow(win);
    SDL_DestroyRenderer(rend);
    SDL_Quit();
    for (int i = 0; i < 81; ++i) {
        SDL_DestroyTexture(textures[i]);
    }
}

void Game::handleEvents() {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch(event.type) {
        case SDL_QUIT:
            gameIsRunning = false;
            break;
            case SDL_KEYDOWN:
                /*  */
                switch (event.key.keysym.sym)
                {
                    case SDLK_a:
                    case SDLK_LEFT:
                        if (cursor[0] > 0) {
                            cursor[0] = cursor[0] - 1;
                        }
                        break;
                    case SDLK_d:
                    case SDLK_RIGHT:
                        if (cursor[0] < 8) {
                            cursor[0] = cursor[0] + 1;
                        }
                        break;
                    case SDLK_w:
                    case SDLK_UP:
                        if (cursor[1] > 0) {
                            cursor[1] = cursor[1] - 1;
                        }
                        break;
                    case SDLK_s:
                    case SDLK_DOWN:
                        if (cursor[1] < 8) {
                            cursor[1] = cursor[1] + 1;
                        }
                        break;
                }
                default:
                    break;
    }
}

void Game::update() {
    int x_pos = 0;
    int y_pos = 0;

    for (int i = 0; i < 81; ++i) {
        if (i % 9 == 0 && i != 0) {
            x_pos = 0;
            y_pos += 50;
        }

        rects[i]->w = 50;
        rects[i]->h = 50;

        rects[i]->x = x_pos;
        rects[i]->y = y_pos;

        x_pos += 50;
    }
}

void Game::render() {
    SDL_RenderClear(rend);

    for (int i = 0; i < 81; ++i) {
        SDL_RenderCopy(rend, textures[i], nullptr, rects[i]);
    }

    SDL_RenderPresent(rend);
}

bool Game::isRunning() const {
    return gameIsRunning;
}

void Game::genGameMap() {
    char filename[] = "/home/ganymede/CLionProjects/cpp-learning-projects/sudoku/gameMaps/sudoku_map1.txt";
    loadGameMapFromFile(filename, gameMap);
    drawMap();
}

void Game::loadGameMapFromFile(char* filepath, char* gameMap) {
    std::ifstream fin(filepath);
    std::filebuf* pbuf = fin.rdbuf();

    // get file size using buffer's members
    std::size_t size = pbuf->pubseekoff (0,fin.end,fin.in);
    pbuf->pubseekpos (0, fin.in);

    char* tempMap = new char[size];
    pbuf->sgetn (tempMap, size);
    fin.close();

    // TODO: figure out what to do with '\n'
    int shift = 0; // to avoid '\n'
    for(int i = 0; i < 81; ++i) {
        if (tempMap[i+shift] == '\n') {
            shift++;
            --i;
            continue;
        }
        gameMap[i] = tempMap[i+shift];
    }

    delete[] tempMap;
}

void Game::drawMap() {
    std::map <int, std::string> nums = {
            {1, "one-black"}, {2, "two-black"}, {3, "three-black"}, {4, "four-black"}, {5, "five-black"},
            {6, "six-black"}, {7, "seven-black"}, {8, "eight-black"}, {9, "nine-black"}, {0, "empty-black"}
    };
    for(int i = 0; i < 81; ++i) {
        int current_num = gameMap[i] - 48;

        std::string text_num = nums[current_num];
        std::string filepath = "/home/ganymede/CLionProjects/cpp-learning-projects/sudoku/assets/" + text_num + ".png";
        auto* cell = new CellObject();


        SDL_Surface* tmpSurf = IMG_Load(filepath.c_str());
        if(!tmpSurf) {
            std::cerr << "Failed to load img: " << SDL_GetError() << std::endl;
        }
        textures[i] = SDL_CreateTextureFromSurface(rend, tmpSurf);
        if (textures[i] == nullptr) {
            std::cout << "Can't create texture from surface: " << SDL_GetError() << std::endl;
        }
        rects[i] = new SDL_Rect();
        SDL_FreeSurface(tmpSurf);
    }
}
