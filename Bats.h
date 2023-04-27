#ifndef BATS_H
#define BATS_H

#include "Game.hpp"
#include "ThreatObject.h"
#include "State.h"
#include "TextureManager.hpp"
class Bats
{
    public:
        Bats(int speed);
        ~Bats();
    void Update();
    void Render();
    bool isActive();
    void destroy();
    int xpos = 801, ypos;
    int width, height, batspeed = 7;
private:
    bool active;
    SDL_Texture* objTexture;
    int batframes = 4;
    int framespeed = 50;
    SDL_Rect destRect, srcRect[4];
    //int speed = 50;
    int randomobject = rand() % 3;
};

#endif // BATS_H
