#include "Bats.h"

Bats::Bats(int speed)
:active(true)
{
    objTexture = TextureManager::LoadTexture("pics/bat.png", Game::renderer);
    for(int i = 0; i < 4; i++)
    {
        srcRect[i] = {i*79, 0, 79 , 79};
    }
    for(auto& t: Game::threats)
    {
        if(t->threatType == CACTUS) {ypos =  100; break;}
        else ypos =  212;
    }
    destRect = {xpos, ypos, 79/3*2, 79/3*2};
    width = destRect.w; height = destRect.h;
    batspeed = 2 + speed;
}

Bats::~Bats()
{
    SDL_DestroyTexture(objTexture);
    objTexture = NULL;
}

void Bats::Update()
{
    if(!active) return;
    if(xpos <= 0) active = false;
    xpos = xpos - batspeed;
    destRect.x = xpos;
}

void Bats::Render()
{
    if(!active) return;
    SDL_RenderCopy(Game::renderer, objTexture, &srcRect[(SDL_GetTicks64()/framespeed)%batframes], &destRect);

}

bool Bats::isActive() {return active;}
void Bats::destroy() {active = false;}
