#ifndef GAME_HPP
#define GAME_HPP

#include "player.hpp"

#include <SDL2/SDL.h>

#include <unordered_map>

class game
{
public:
    game();
    ~game();

    void run();

    void process_events();
    void update();
    void render();

    SDL_Texture* get_texture(const std::string& filename);

private:
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    bool is_running = true;

    std::unordered_map<std::string, SDL_Texture*> texture_cache;

    player player;

    void clear_texture_cache();
};

#endif // GAME_HPP
