#include<SDL.h>
#ifndef Game_hpp
#define Game_hpp
#include<iostream>
#include <string>
#include <algorithm>
#include <vector>
#include<SDL_image.h>
#include "Settings.h"

class ThreatObject;
class Bats;
class DropObject;
class Text;

class Game {
public:
        Game();
        ~Game();
    void init(const char *title, int xpos, int ypos, int SCREEN_WIDTH, int SCREEN_HEIGHT, bool fullscreen);
    void handleEvents();
    void update();
    void render();
    void clean();

    bool running(){return isRunning;};
    static SDL_Event event;
    static SDL_Renderer *renderer;

    static std::vector<ThreatObject*> threats;
    static std::vector<Bats*> bats;
    static std::vector<DropObject*> drops;
private:
        bool isRunning;
        SDL_Window *window;
        int cnt = 0;
        Text* scoreText;
        int score = 0;
        Uint64 nextTimeSpawn = 1000;
        int spawnSpeed = 2000;
        Uint64 nextTimeSpawnBat = 5000;
        Uint64 nextTimeSpawnDrop = 15000;
        Uint64 nextTimeIncreaseSpeed = 15000;
        Uint64 nextTimeIncreaseScore = 0;
        int gameSpeed = 4;
};
#endif
