#include "CellObject.h"
#include "string"
#include <iostream>
#include <map>

CellObject::CellObject(std::string name, int x_pos, int y_pos, bool is_editable) {
    this->name = name;
    this->x_pos = x_pos;
    this->y_pos = y_pos;
    this->is_editable = is_editable;
}


void CellObject::load_pic(SDL_Renderer *rend) {
    std::string filepath = "/home/ganymede/CLionProjects/cpp-learning-projects/sudoku/assets/" + this->name + ".png";
    SDL_Surface* tmpSurf = IMG_Load(filepath.c_str());
    if(!tmpSurf) {
        std::cerr << "Failed to load img: " << SDL_GetError() << std::endl;
    }

    this->texture = SDL_CreateTextureFromSurface(rend, tmpSurf);
    if (this->texture == nullptr) {
        std::cout << "Can't create texture from surface: " << SDL_GetError() << std::endl;
    }

    this->rect = new SDL_Rect();

    SDL_FreeSurface(tmpSurf);

    this->rect->h = 50;
    this->rect->w = 50;
    this->rect->x = this->x_pos;
    this->rect->y = this->y_pos;
}

void CellObject::clear() {
    SDL_DestroyTexture(this->texture);
}

void CellObject::revert_cell(SDL_Renderer* rend) {
    if (this->name.find("black") != std::string::npos) {
        this->name = this->name.replace(this->name.size() - 5, 5, "red");
        }
    else {
        this->name = this->name.replace(this->name.size() - 3, 3, "black");
    }
    this->load_pic(rend);
}

void CellObject::set_and_load_number_pic(SDL_Renderer *rend, int num) {
    std::map <int, std::string> nums = {
            {1, "one-red"}, {2, "two-red"}, {3, "three-red"}, {4, "four-red"}, {5, "five-red"},
            {6, "six-red"}, {7, "seven-red"}, {8, "eight-red"}, {9, "nine-red"}, {0, "empty-red"}
    };

    this->name = nums[num];

    this->load_pic(rend);
}


