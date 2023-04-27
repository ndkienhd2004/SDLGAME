#include "DropObject.h"

DropObject::DropObject(int speed)
:active(true), dropspeed(speed)
{
    switch(randomobject)
    {
    case 0:
        objTexture = TextureManager::LoadTexture("pics/bulletdrop.png", Game::renderer);
        srcRect = {0 , 0, 360,360};
        ypos = 100;
        destRect = {xpos, ypos, 40, 40};
        dropType = BULLET;
        break;
    case 1:
        objTexture = TextureManager::LoadTexture("pics/health.png", Game::renderer);
        ypos = 100;
        srcRect = {0 , 0, 254, 254};
        destRect = {xpos, ypos, 40, 40};
        dropType = HEALTH;
        break;
    }
    width = destRect.w; height = destRect.h;
}
DropObject::~DropObject()
{
    SDL_DestroyTexture(objTexture);
    objTexture = NULL;
}

void DropObject::Update()
{
    if(!active) return;
    if(xpos <= 0) active = false;
    xpos = xpos - dropspeed;
    destRect.x = xpos;
}

void DropObject::Render()
{
    if(!active) return;
    SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);

}

bool DropObject::isActive() {return active;}
void DropObject::destroy() {active = false;}
