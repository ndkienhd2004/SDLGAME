#pragma once
#include "Game.hpp"
#include <SDL_ttf.h>
class TextureManager
{
public:
    static SDL_Texture *LoadTexture(const char* filename, SDL_Renderer* ren);
    static SDL_Texture *LoadText(TTF_Font* font,const char* text, SDL_Color textColor);
};
