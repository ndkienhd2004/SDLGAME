#pragma once
#include "Game.hpp"
//#include<SDL_ttf.h>

class GameObject
{
public:
    GameObject();
    //GameObject(const char*& texturesheet, int& x, int& y, SDL_Rect& _srcRect);
    ~GameObject();

    void virtual Update();
    void virtual Render();
    int changeYPos(int jumpheight) { ypos += jumpheight;}
    int getYPos() {return ypos;}
private:
    int xpos;
    int ypos;

    SDL_Texture* objTexture;
    SDL_Rect srcRect, destRect;
};

