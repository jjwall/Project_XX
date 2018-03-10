#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <SDL2/SDL.h>
#include <vector>

class enemy {
public:
    enemy();

//    struct float_rect
//    {
//        float x;
//        float y;
//        float w;
//        float h;
//    };

//    float_rect pos;

    struct spawnType
    {
        float x;
        float y;
        float w;
        float h;
    };

    std::vector<spawnType> entities;

    spawnType spawn(float x, float y, float w, float h) {
        spawnType enemy;
        enemy.x = x;
        enemy.y = y;
        enemy.w = w;
        enemy.h = h;
        entities.push_back(enemy);
    }
};

#endif // ENEMY_HPP
