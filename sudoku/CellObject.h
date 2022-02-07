#include "string"
#include <SDL2/SDL.h>
#include "SDL2/SDL_image.h"

class CellObject {
public:
    CellObject(std::string name, int x_pos, int y_pos);
    std::string name;

    int x_pos;
    int y_pos;

    SDL_Texture* texture{};
    SDL_Rect* rect{};

    void clear();
    void load_pic(SDL_Renderer* rend);
    void revert_cell(SDL_Renderer* rend);
};
