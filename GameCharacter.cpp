#include "GameCharacter.hpp"
#include "Game.hpp"
#include "TextureManager.hpp"

GameCharacter::GameCharacter(const char* texturesheet, const char* healthTexture, const char* AmoTexture, int x, int y)
: xpos(x), ypos(y), state(FALLING)
{
    controller = new KeyboardController(xpos, ypos, state, bullets, amo);
    objTexture = TextureManager::LoadTexture(texturesheet, Game::renderer);
    HPTexture = TextureManager::LoadTexture(healthTexture, Game::renderer);
    AMOTexture = TextureManager::LoadTexture(AmoTexture, Game::renderer);
    for(int i = 0; i < 12; i++)
    {
        runRect[i] = {11 + i*86, 408, 60,60};
    }
    fallRect ={15, 171, 60, 60};
    jumpRect ={189, 171, 60, 60};
    width = height = 60;
    HPSrcRect = {0,0,254,254};
    HPDestRect = {0,10,30,30};
    AmoSrcRect = {0, 0, 360, 360};
    AmoDestRect = {0, 40, 30, 30};
}

GameCharacter::~GameCharacter()
{}

void GameCharacter::Update()
{
    bullets.erase(remove_if(bullets.begin(), bullets.end(), [](Bullet* b) {return !b->isActive();}),bullets.end());
    destRect = {xpos, ypos, runRect[0].w, runRect[0].h};
    controller->Update();
    for(auto& b : bullets) b->Update();

}

void GameCharacter::Render()
{
    //////////////////////////////////////////sprite sheet
    if(state == IDLE) SDL_RenderCopy(Game::renderer, objTexture, &runRect[(SDL_GetTicks64()/speed)%runFrames], &destRect);
    else if(state == JUMPING) SDL_RenderCopy(Game::renderer, objTexture, &jumpRect, &destRect);
    else if(state == JUMPING2) SDL_RenderCopy(Game::renderer, objTexture, &jumpRect, &destRect);
    else if(state == FALLING) SDL_RenderCopy(Game::renderer, objTexture, &fallRect, &destRect);
    ///////////////////////////////////////////
    for(auto& b : bullets) b->Render();
    for(int i = 1; i <= health; i++)
    {
        HPDestRect.x = i*60;
        SDL_RenderCopy(Game::renderer, HPTexture, &HPSrcRect, &HPDestRect);
    }

    for(int i = 1; i <= amo; i++)
    {
        AmoDestRect.x = i*60;
        SDL_RenderCopy(Game::renderer, AMOTexture, &AmoSrcRect, &AmoDestRect);
    }
}
