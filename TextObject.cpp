#include "TextObject.hpp"

Text::Text(const char* fontFile, const char* textContent, int fontSize, float x, float y, SDL_Color textColor)
:  text(NULL)
{
    font = TTF_OpenFont(fontFile, fontSize);
    if(textContent != NULL)
    {
        text = TextureManager::LoadText(font, textContent, textColor);
        SDL_QueryTexture(text, NULL, NULL, &Width, &Height);
    }else {Width = 0; Height = 0;}
    srcRect.x = srcRect.y = 0;
    destRect.x = x;
    destRect.y = y;

    srcRect.w = destRect.w = Width;
    srcRect.h = destRect.h = Height;
}

Text::~Text()
{
    Reset();
}


void Text::Render()
{
    if(text == NULL) return;
    SDL_RenderCopy(Game::renderer, text, &srcRect, &destRect);
}

void Text::Reset()
{
    TTF_CloseFont(font);
    SDL_DestroyTexture(text);
    font = NULL;
    text = NULL;
}

int Text::getWidth()
{
    return Width;
}

int Text::getHeight()
{
    return Height;
}
