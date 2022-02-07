#include "Game.h"

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
    cur_cursor[0] = 0;
    cur_cursor[1] = 0;
    last_cursor[0] = -1;
    last_cursor[1] = -1;
}

void Game::clear() {
    for (int i = 0; i < 81; ++i) {
        cells[i]->clear();
    }
    SDL_DestroyWindow(win);
    SDL_DestroyRenderer(rend);
    SDL_Quit();
}

void Game::handleEvents() {
    int cur_cell_pos = cur_cursor[0] + (cur_cursor[1] * 9);

    SDL_Event event;
    SDL_PollEvent(&event);
    switch(event.type) {
        case SDL_QUIT:
            gameIsRunning = false;
            break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    case SDLK_a:
                    case SDLK_LEFT:
                        if (cur_cursor[0] > 0) {
                            last_cursor[0] = cur_cursor[0];
                            last_cursor[1] = cur_cursor[1];
                            cur_cursor[0] = cur_cursor[0] - 1;
                        }
                        break;


                    case SDLK_d:
                    case SDLK_RIGHT:
                        if (cur_cursor[0] < 8) {
                            last_cursor[0] = cur_cursor[0];
                            last_cursor[1] = cur_cursor[1];
                            cur_cursor[0] = cur_cursor[0] + 1;
                        }
                        break;


                    case SDLK_w:
                    case SDLK_UP:
                        if (cur_cursor[1] > 0) {
                            last_cursor[0] = cur_cursor[0];
                            last_cursor[1] = cur_cursor[1];
                            cur_cursor[1] = cur_cursor[1] - 1;
                        }
                        break;


                    case SDLK_s:
                    case SDLK_DOWN:
                        if (cur_cursor[1] < 8) {
                            last_cursor[0] = cur_cursor[0];
                            last_cursor[1] = cur_cursor[1];
                            cur_cursor[1] = cur_cursor[1] + 1;
                        }
                        break;

                    case SDLK_1:
                        if (cells[cur_cell_pos]->is_editable) {
                            cells[cur_cell_pos]->set_and_load_number_pic(rend, 1);
                        }
                        break;

                    case SDLK_2:
                        if (cells[cur_cell_pos]->is_editable) {
                            cells[cur_cell_pos]->set_and_load_number_pic(rend, 2);
                        }
                        break;

                    case SDLK_3:
                        if (cells[cur_cell_pos]->is_editable) {
                            cells[cur_cell_pos]->set_and_load_number_pic(rend, 3);
                        }
                        break;

                    case SDLK_4:
                        if (cells[cur_cell_pos]->is_editable) {
                            cells[cur_cell_pos]->set_and_load_number_pic(rend, 4);
                        }
                        break;

                    case SDLK_5:
                        if (cells[cur_cell_pos]->is_editable) {
                            cells[cur_cell_pos]->set_and_load_number_pic(rend, 5);
                        }
                        break;

                    case SDLK_6:
                        if (cells[cur_cell_pos]->is_editable) {
                            cells[cur_cell_pos]->set_and_load_number_pic(rend, 6);
                        }
                        break;

                    case SDLK_7:
                        if (cells[cur_cell_pos]->is_editable) {
                            cells[cur_cell_pos]->set_and_load_number_pic(rend, 7);
                        }
                        break;

                    case SDLK_8:
                        if (cells[cur_cell_pos]->is_editable) {
                            cells[cur_cell_pos]->set_and_load_number_pic(rend, 8);
                        }
                        break;

                    case SDLK_9:
                        if (cells[cur_cell_pos]->is_editable) {
                            cells[cur_cell_pos]->set_and_load_number_pic(rend, 9);
                        }
                        break;

                    case SDLK_0:
                        if (cells[cur_cell_pos]->is_editable) {
                            cells[cur_cell_pos]->set_and_load_number_pic(rend, 0);
                        }
                        break;
                }
                default:
                    break;
    }
}

void Game::update() {
    if (cur_cursor[0] != last_cursor[0] || cur_cursor[1] != last_cursor[1]) {

        if (last_cursor[0] >= 0 && last_cursor[1] >= 0) {
            int last_cell_pos = last_cursor[0] + (last_cursor[1] * 9);
            cells[last_cell_pos]->revert_cell(rend);
        }

        int cur_cell_pos = cur_cursor[0] + (cur_cursor[1] * 9);
        cells[cur_cell_pos]->revert_cell(rend);
        last_cursor[0] = cur_cursor[0];
        last_cursor[1] = cur_cursor[1];
    }
}

void Game::render() {
    SDL_RenderClear(rend);

    for (int i = 0; i < 81; ++i) {
        SDL_RenderCopy(rend, cells[i]->texture, nullptr, cells[i]->rect);
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
    pbuf->pubseekpos(0, fin.in);

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

    int x_pos = 0, y_pos = 0;
    bool is_editable;

    for(int i = 0; i < 81; ++i) {
        if (i % 9 == 0 && i != 0) {
            x_pos = 0;
            y_pos += 50;
        }

        int current_num = gameMap[i] - 48;

        if (current_num == 0) {
            is_editable = true;
        }
        else {
            is_editable = false;
        }

        std::string text_num = nums[current_num];

        auto* cell = new CellObject(text_num, x_pos, y_pos, is_editable);
        cell->load_pic(rend);
        cells[i] = cell;

        x_pos += 50;
    }
}
