#include "game.hpp"

#include <SDL2/SDL_image.h>

#include <stdexcept>

#include <chrono>

#include <thread>

float framecount = 0;
bool shotBoolean = false;
float shotTimer = 0;
int currentShotTimer;
//void shotTimerFunction() {
   // shotTimer = 0;
   // while (shotTimer <= 5) {
     //   shotBoolean = false;
  //  }
    //shotBoolean = false;
//}

game::game()
{
    const auto display_width = 800;
    const auto display_height = 600;

    window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, display_width, display_height, SDL_WINDOW_SHOWN);
    if (!window) {
        throw std::runtime_error(SDL_GetError());
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        throw std::runtime_error(SDL_GetError());
    }   
}

game::~game()
{
    clear_texture_cache();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

void game::run()
{
    using clock = std::chrono::high_resolution_clock;

    while (is_running) {
        auto frame_start = clock::now();
        auto next_frame = frame_start + std::chrono::duration<double>(1.0/60.0);
        process_events();
        update();
        render();
        std::this_thread::sleep_until(next_frame);
        if (framecount <= 60) {
            framecount++;
            shotTimer += 0.0167;
            if (framecount == 60) {
                framecount = 0;
                //shotTimer++;
            }
        }
        if (currentShotTimer + .35 <= shotTimer) {
            shotBoolean = false;
        }
    }
}

void game::process_events()
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            is_running = false;
            break;
        default:
            break;
        }
    }
}

void game::update()
{
    auto keys = SDL_GetKeyboardState(nullptr);
    if (keys[SDL_SCANCODE_LEFT]) {
        if (player.pos.x >= 0) {
            player.pos.x -= 5;
        }
    }
    if (keys[SDL_SCANCODE_RIGHT]) {
        if (player.pos.x <= 700) {
            player.pos.x += 5;
        }
    }
    if (keys[SDL_SCANCODE_UP]) {
        if (player.pos.y >= 0) {
            player.pos.y -= 5;
        }
    }
    if (keys[SDL_SCANCODE_DOWN]) {
        if (player.pos.y <= 500) {
            player.pos.y += 5;
        }
    }
    if (keys[SDL_SCANCODE_SPACE]) {
        //if (framecount < 10) {
        if (!shotBoolean) {
            shotTimer = 0;
            currentShotTimer = shotTimer;
            player.shoot(player.pos.x, player.pos.y);
            shotBoolean = true;
            //shotTimerFunction();
        }
    }
    for (int i=0; i<player.bullets.size(); ++i) {
         if (player.bullets[i].x >= 750) {
             player.bullets.erase(player.bullets.begin() + i);
         }
    }
}

void game::render()
{
    auto pos = SDL_Rect{player.pos.x, player.pos.y, player.pos.w, player.pos.h};
    SDL_RenderClear(renderer);
    for (auto&& bullet : player.bullets) {
        auto bulletpos = SDL_Rect{bullet.x, bullet.y, 75, 75};
        bullet.x += 15;
        SDL_RenderCopy(renderer, get_texture("bullet.png"), nullptr, &bulletpos);
    }
    SDL_RenderCopy(renderer, get_texture("goodship.png"), nullptr, &pos);
    SDL_RenderPresent(renderer);
}

SDL_Texture* game::get_texture(const std::string& filename)
{
    auto& texture = texture_cache[filename];

    if (!texture) {
        auto texture_surface = IMG_Load(("assets/textures/"+filename).data());
        texture = SDL_CreateTextureFromSurface(renderer, texture_surface);
        SDL_FreeSurface(texture_surface);
    }

    return texture;
}

void game::clear_texture_cache()
{
    for (auto&& name_tex : texture_cache) {
        SDL_DestroyTexture(name_tex.second);
    }
    texture_cache.clear();
}
