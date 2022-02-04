#include "string"
#include <SDL2/SDL.h>
#include "SDL2/SDL_image.h"

class CellObject {
public:
    CellObject(std::string name);
    std::string name;
    SDL_Texture* texture{};
    void clear();
    void load_pic();
};
