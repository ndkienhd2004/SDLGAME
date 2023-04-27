#include "ThreatObject.h"

ThreatObject::ThreatObject(int speed)
:active(true), threatspeed(speed)
{
    switch(randomobject)
    {
    case 0:
        objTexture = TextureManager::LoadTexture("pics/cactus.png", Game::renderer);
        srcRect = {0 , 0, 308, 644};
        ypos = 232;
        destRect = {xpos, ypos, 70, 140};
        threatType = CACTUS;
        break;
    case 1:
        objTexture = TextureManager::LoadTexture("pics/rock.png", Game::renderer);
        ypos = 322;
        srcRect = {0 , 0, 146, 120};
        destRect = {xpos, ypos, 60, 50};
        threatType = ROCK;
        break;
    case 2:
        objTexture= TextureManager::LoadTexture("pics/cactus2.png", Game::renderer);
        ypos = 291;
        srcRect = {0 , 0, 206, 321};
        destRect = {xpos, ypos, 50, 80};
        threatType = CACTUS2;
        break;
    }
    width = destRect.w; height = destRect.h;
}

ThreatObject::~ThreatObject()
{
    SDL_DestroyTexture(objTexture);
    objTexture = NULL;
}

void ThreatObject::Update()
{
    if(!active) return;
    if(xpos <= 0) active = false;
    xpos = xpos - threatspeed;
    destRect.x = xpos;
}

void ThreatObject::Render()
{
    if(!active) return;
    SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);

}

bool ThreatObject::isActive() {return active;}
void ThreatObject::destroy() {active = false;}
