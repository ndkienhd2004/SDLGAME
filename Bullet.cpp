#include "Bullet.h"

Bullet::Bullet(int startX, int startY, const char* path) :active(true), xpos(startX), ypos(startY)
{
    bulletTexture = TextureManager::LoadTexture(path, Game::renderer);
    SDL_QueryTexture(bulletTexture, NULL, NULL, &width, &height);
    srcRect = {0,0,width,height};
    destRect = {startX,startY+10, width*2,height*2};
}

Bullet::~Bullet()
{
    SDL_DestroyTexture(bulletTexture);
    bulletTexture = NULL;
}

void Bullet::Update()
{
    if(!active) return;
    xpos += 10;
    destRect.x = xpos;
    if(xpos + width - 20 > SCREEN_WIDTH) active = false;
}

void Bullet::Render()
{
    if(!active) return;
    SDL_RenderCopy(Game::renderer, bulletTexture, &srcRect, &destRect);
}

bool Bullet::isActive() {
    return active;
}

void Bullet::destroy()
{
    active = false;
}
