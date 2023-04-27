#pragma once
#ifndef DropObject_h
#include <SDL.h>
#include <string>
#include <vector>

#include"State.h"
#include "Game.hpp"
#include "TextureManager.hpp"

class DropObject
{
public:
    DropObject(int speed);
    ~DropObject();
    void Update();
    void Render();
    bool isActive();
    void destroy();
    int xpos = 801, ypos;
    int width, height, dropspeed ;
    DROP dropType;
private:
    bool active;

    SDL_Texture* objTexture;
    SDL_Rect destRect, srcRect;
    int randomobject = rand() % 2;
};
#endif // DropObject_h
