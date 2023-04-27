#pragma once
#ifndef TextObject_h
#define TextObject_h

#include <SDL.h>
#include <SDL_ttf.h>
#include "TextureManager.hpp"

class Text
{
public:
    Text() {}
    Text(const char* fontFile, const char* textContent, int fontSize, float x, float y, SDL_Color textColor);
    ~Text();
    void Render();
    void Reset();
    int getWidth();
    int getHeight();
private:
    int Width, Height;
    SDL_Rect srcRect, destRect;
    SDL_Texture* text;
    TTF_Font* font;
};

#endif // TextObject_h
