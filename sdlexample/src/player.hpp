#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SDL2/SDL.h>
#include <vector>

class player
{
public:
    player();

    struct float_rect
    {
        float x;
        float y;
        float w;
        float h;
    };

    float_rect pos;

    struct shootType
    {
        float x;
        float y;
    };

    //shot shots;
    std::vector<shootType> bullets;

    shootType shoot(float x, float y) {
        //x = pos.x;
        //y = pos.y;
        shootType bullet;
        bullet.x = x + 100;
        bullet.y = y + 17;
        bullets.push_back(bullet);
        //shots.x = x + 50;
        //shots.y = y + 50;

        return{bullet.x,bullet.y};
    }

    //pos.x = 5.5;

    //float_rect.x = 1.5f;
                    //1.5f, 50.5f, 50.5f);

    //SDL_Rect pos = {100,100,50,50};
};

#endif // PLAYER_HPP
