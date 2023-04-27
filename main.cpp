#include "Game.hpp"
#include "Settings.h"
Game *game = nullptr;
int main(int argc, char *argv[])
{
    const int FPS = 120;
    const int framedelay = 1000 / FPS;

    Uint32 framestart;
    int frametime;

    game = new Game();
    game->init("damu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    while(game->running())
    {
        framestart = SDL_GetTicks();
        game->handleEvents();
        game->update();
        game->render();

        frametime = SDL_GetTicks()-framestart;
        if(framedelay > frametime)
        {
            SDL_Delay(framedelay - frametime) ;
        }
    }
    game->clean();
    return 0;
}
