
#include "game.hpp"

#include <SDL2/SDL.h>

#include <stdexcept>
#include <iostream>

int main() try
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        throw std::runtime_error(SDL_GetError());
    }

    game g;

    g.run();
}
catch (const std::exception& e)
{
    std::cerr << "Exception occurred: " << e.what() << std::endl;
}
