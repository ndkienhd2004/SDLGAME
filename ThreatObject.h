#pragma once
#ifndef ThreatObject_h
#define ThreatObject_h

#include <SDL.h>
#include <string>
#include <vector>

#include"State.h"
#include "Game.hpp"
#include "TextureManager.hpp"

class ThreatObject
{
public:
    ThreatObject(int speed);
    ~ThreatObject();
    void Update();
    void Render();
    bool isActive();
    void destroy();
    int xpos = 801, ypos;
    int width, height, threatspeed = 5;
    THREAT threatType;
private:
    bool active;

    SDL_Texture* objTexture;
    SDL_Rect destRect, srcRect;
    //int speed = 50;
    int batframes = 4;
    int randomobject = rand() % 3;

};

#endif // ThreatObject_h
