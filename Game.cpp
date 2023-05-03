#include "Game.hpp"
#include "TextureManager.hpp"
#include "GameObject.hpp"
#include "GameCharacter.hpp"
#include "ThreatObject.h"
#include "DropObject.h"
#include "Bats.h"
#include "State.h"
#include "TextObject.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

GameCharacter *player = nullptr;
std::vector<ThreatObject*> Game::threats;
std::vector<Bats*> Game::bats;
std::vector<DropObject*> Game::drops;
SDL_Texture* scrollingBackground;
SDL_Rect srcRect;
SDL_Rect destRect1, destRect2;
SDL_Event Game::event;
SDL_Renderer* Game::renderer = nullptr;




Game::Game()
{}
Game::~Game()
{}



void Game::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    int flags = 0;
    if(fullscreen) flags = SDL_WINDOW_FULLSCREEN;

    if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        cout<< "subsystem iinitialised" << endl;
        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags | SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if(window) cout<<"window created" <<endl;

    renderer = SDL_CreateRenderer(window,-1,0);
    if(renderer)
    {
        SDL_SetRenderDrawColor(renderer,255,255,255,255);
        if(TTF_Init() < 0){
            cout << "Unable to initialize TTF! TTF_Error: " << TTF_GetError() << endl;
        }
        cout << "renderer created" <<endl;
    }
    isRunning = true;
    }
    else {
        isRunning = false;
    }
    player = new GameCharacter("pics/khua.png", "pics/health.png","pics/bulletdrop.png", 150,0);
    //threats.push_back(new ThreatObject());

    scrollingBackground = TextureManager::LoadTexture("pics/background.png", renderer);
    SDL_QueryTexture(scrollingBackground, NULL, NULL, &srcRect.w, &srcRect.h);
    srcRect.x = 0;
    srcRect.y = 0;
    destRect1 = {0,0,srcRect.w, srcRect.h};
    destRect2 = {0,0,srcRect.w, srcRect.h};
    srand(time(0));

    // Set scoreText
    SDL_Color White = {255,255,255};
    scoreText = new Text("font/CastoroTitling-Regular.ttf", "Your score: 0", 18, 600,100, White);
}
void Game::handleEvents()
{
    SDL_PollEvent(&event);
    switch (event.type)
    {
    case SDL_QUIT:
        isRunning = false;
        break;
    default:
        break;
    }
}
void Game::update()
{
    if(SDL_GetTicks64() > nextTimeIncreaseScore)
    {
        score += 1;
        nextTimeIncreaseScore = SDL_GetTicks64() + 1000;
    }

    if(SDL_GetTicks64() > nextTimeIncreaseSpeed)
    {
        gameSpeed += 1;
        nextTimeIncreaseSpeed = SDL_GetTicks64() + 15000;
    }

    // set text
    SDL_Color Black = {0,0,0};
    string scoreToString = "Your score: " + to_string(score);
    scoreText->Reset();
    scoreText = new Text("font/CastoroTitling-Regular.ttf", scoreToString.c_str(), 18, 600,50, Black);
    ////////////////////

    //delete obj
    threats.erase(remove_if(threats.begin(), threats.end(), [](ThreatObject* threat) {return !threat->isActive();}),threats.end());
    bats.erase(remove_if(bats.begin(), bats.end(), [](Bats* Bat) {return !Bat->isActive();}),bats.end());
    drops.erase(remove_if(drops.begin(), drops.end(), [](DropObject* d) {return !d->isActive();}),drops.end());
    // Random OBJ
    int randomObj = rand()%5;

    if(randomObj == 0)
    {
        if(SDL_GetTicks64() > nextTimeSpawnDrop)
        {
            drops.push_back(new DropObject(gameSpeed));
            nextTimeSpawnDrop = SDL_GetTicks64() + rand()%6000 + 1000;
        }
    }else
    {
        if(SDL_GetTicks64() > nextTimeSpawn)
        {
            threats.push_back(new ThreatObject(gameSpeed));
            nextTimeSpawn = SDL_GetTicks64() + spawnSpeed;
        }

        if(SDL_GetTicks64() > nextTimeSpawnBat)
        {
            bats.push_back(new Bats(gameSpeed));
            nextTimeSpawnBat = SDL_GetTicks64() + rand()%6000 + 1000;
        }
    }



    int i = 0;
    // Update background
    destRect1.x = destRect1.x - gameSpeed;
    destRect2.x = destRect1.x + destRect1.w;
    if(destRect1.x + destRect1.w<= 0)
    {
        destRect1 = {0,0,srcRect.w, srcRect.h};
        destRect2 = {0,0,srcRect.w, srcRect.h};
    }
    ///////////////////
    player->Update();
    for(auto& t : threats) t->Update();
    for(auto& Bat : bats) Bat->Update();
    for(auto& d : drops) d->Update();
    //collision
    for(auto& b : player->bullets)
    {
        for(auto& t : threats)
        {
            if(t->xpos + t->width >= b->xpos &&
               b->xpos + b->width >= t->xpos &&
               t->ypos + t->height >= b->ypos &&
               b->ypos + b->height >= t->ypos
               )
            {
                cout<<"ban khua"<<endl;
                t->destroy();
                b->destroy();
            }
        }

        for(auto& Bat : bats)
        {
              if(Bat->xpos + Bat->width >= b->xpos &&
               b->xpos + b->width >= Bat->xpos &&
               Bat->ypos + Bat->height >= b->ypos &&
               b->ypos + b->height >= Bat->ypos
               )
            {
                cout<<"ban khua"<<endl;
                Bat->destroy();
                b->destroy();
            }
        }
    }

    for(auto& t : threats)
        if(t->xpos + t->width - 15 >= player->xpos &&
            player->xpos + player->width -15 >= t->xpos &&
            t->ypos + t->height -15 >= player->ypos &&
            player->ypos + player->height -15 >= t->ypos
            )
            {
                t->destroy();
                player->health = player->health - 1;

                cout<<"dam khua"<<endl;
                if(player->health == 0)
                {
                    std::string HScore;
                    std::fstream myfile("highsc.txt", std::ios::in | std::ios::out);
                    std::getline(myfile,HScore);
                    myfile.close();

                    if(score > stoi(HScore))
                    {
                            HScore = std::to_string(score);
                    }
                    std::ofstream writeFile("highsc.txt");
                    writeFile << HScore;
                    writeFile.close();
                    SDL_Delay(3000);
                    isRunning = 0;
                }
            }

    for(auto& Bat : bats)
        if(Bat->xpos + Bat->width - 15 >= player->xpos &&
            player->xpos + player->width -15 >= Bat->xpos &&
            Bat->ypos + Bat->height -15 >= player->ypos  &&
            player->ypos + player->height -15>= Bat->ypos
            )
            {
                Bat->destroy();
                player->health = player->health - 1;
                //player->destroy();
                cout<<"dam khua"<<endl;
                if(player->health == 0)
                {
                    SDL_Delay(3000);
                    isRunning = 0;
                }
            }
     for(auto& d : drops)
        if(d->xpos + d->width - 15 >= player->xpos &&
            player->xpos + player->width -15 >= d->xpos &&
            d->ypos + d->height -15 >= player->ypos  &&
            player->ypos + player->height -15>= d->ypos
            )
            {
                d->destroy();
                if(d->dropType == BULLET)
                player->amo = player->amo + 1;
                else  player->health = player->health + 1;
            }
}
void Game::render()
{
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, scrollingBackground, &srcRect, &destRect1);
    SDL_RenderCopy(renderer, scrollingBackground, &srcRect, &destRect2);
    player->Render();
    for(auto& t : threats)
    {
        t->Render();
    }
    for(auto& Bat : bats) Bat->Render();
    for(auto& d : drops) d->Render();
    scoreText->Render();
    SDL_RenderPresent(renderer);
}
void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}
