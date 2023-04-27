#pragma once
#ifndef GameCharacter_hpp
#define GameCharacter_hpp

#include <SDL.h>
#include <string>
#include <vector>

#include "Game.hpp"
#include "State.h"
#include "KeyboardController.h"
#include "Bullet.h"

class GameCharacter
{
public:
    GameCharacter(const char* texturesheet, const char* healthTexture, const char* AmoTexture, int x, int y);
    ~GameCharacter();
    void Update();
    void Render();
    std::vector<Bullet*> bullets;
    int xpos, ypos;
    int width, height;
    int health = 3;
    int amo=3;
private:
    JUMPSTATE state;
    int runFrames = 12;
    KeyboardController* controller;
    SDL_Texture* objTexture;
    SDL_Rect destRect;
    SDL_Rect runRect[12], jumpRect, fallRect;
    int speed = 50;
    SDL_Texture* HPTexture;
    SDL_Texture* AMOTexture;
    SDL_Rect HPSrcRect, HPDestRect;
    SDL_Rect AmoSrcRect, AmoDestRect;
    bool isJumping;
};

#endif // GameCharacter_hpp
