#include "TextureManager.hpp"
SDL_Texture *TextureManager::LoadTexture(const char *texture, SDL_Renderer *ren)
{
    SDL_Surface* tempSurface = IMG_Load(texture);
    SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, tempSurface);
    SDL_FreeSurface(tempSurface);
    return tex;
}

SDL_Texture* TextureManager::LoadText(TTF_Font* font,const char* text, SDL_Color textColor)
{
    SDL_Surface* tempSurface = NULL;
    tempSurface = TTF_RenderText_Blended(font, text, textColor);
    if(tempSurface == NULL)
    {
        std::cout << "Unable to load text! TTF_Error: " << TTF_GetError() << std::endl;
    }
    SDL_Texture* Texture = NULL;
    Texture = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
    if(Texture == NULL)
    {
        std::cout << "Unable to create text from surface! SDL_Error: " << SDL_GetError() << std::endl;
    }
    SDL_FreeSurface(tempSurface);
    return Texture;
}
