#pragma once
#ifndef Bullet_h
#define Bullet_h

#include <SDL.h>
#include "TextureManager.hpp"

class Bullet
{
private:
    SDL_Texture* bulletTexture;
    bool active;
    SDL_Rect srcRect, destRect;
public:
    Bullet(int startX, int startY, const char* path);
    ~Bullet();
    void Update();
    void Render();
    bool isActive();
    void destroy();
    int xpos, ypos;
    int width, height;
};

#endif // Bullet_h

