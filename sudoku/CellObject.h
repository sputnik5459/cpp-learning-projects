#include "string"
#include <SDL2/SDL.h>
#include "SDL2/SDL_image.h"

class CellObject {
public:
    CellObject(std::string name, int x_pos, int y_pos, bool is_editable = false);
    std::string name;

    int x_pos;
    int y_pos;

    bool is_editable;

    SDL_Texture* texture{};
    SDL_Rect* rect{};

    void clear();
    void load_pic(SDL_Renderer* rend);
    void set_and_load_number_pic(SDL_Renderer* rend, int num);
    void revert_cell(SDL_Renderer* rend);
};
