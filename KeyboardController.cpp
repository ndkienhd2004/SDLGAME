#include "KeyboardController.h"
#include "Game.hpp"

KeyboardController::KeyboardController(int &_xpos, int &_ypos, JUMPSTATE &_state, std::vector<Bullet*> &_bullet, int &_amo)
: xPos(&_xpos), yPos(&_ypos), state(&_state), bullets(&_bullet), amo(&_amo)
{}

KeyboardController::~KeyboardController(){}

void KeyboardController::Update()
{
    switch(*state)
    {
    case IDLE:
        if(Game::event.type == SDL_KEYDOWN && Game::event.key.keysym.sym == SDLK_UP)
        {
            *state = JUMPING;
        }
        else
        {
            Jump2 = 0;
            maxjumpedpos = *yPos - 150;
            //std::cout<<"IDLE"<<std::endl;
        }
        break;
    case JUMPING:
         if(Game::event.type == SDL_KEYDOWN && Game::event.key.keysym.sym == SDLK_UP && Jump2 == 0)
            {
            *state = JUMPING2;
            }
        else
        {
        if( *yPos >= maxjumpedpos )
            {
            *yPos -= jumpSpeed;
            maxjumpedpos2 = *yPos - 150;
            //std::cout<<"jumping"<<std::endl;

            }

        else{
            *state = FALLING;
            }
        }
        break;
    case JUMPING2:
        if(*yPos >= maxjumpedpos2)
        {
            Jump2 = 1;
            *yPos -= jumpSpeed;
        }
        else *state = FALLING;
        break;
    case FALLING:
        if(Game::event.type == SDL_KEYDOWN && Game::event.key.keysym.sym == SDLK_UP && Jump2 == 0)
            {
            *state = JUMPING2;
            }
        else
        {
        if(*yPos < 311){
            *yPos += fallSpeed;
            maxjumpedpos2 = *yPos - 150;
        }else{
            *state = IDLE;
        }
        }
        break;
    }
    if(Game::event.type == SDL_KEYDOWN && Game::event.key.keysym.sym == SDLK_SPACE)
    {
        if(*amo > 0 )
        {
            bullets->push_back(new Bullet(*xPos, *yPos, "Pics/bullet.png"));

            *amo -= 1;
            std::cout<<*amo<<" bullets left"<<std::endl;
        }
        else std::cout<<"runout bullet"<<std::endl;
    }

}
