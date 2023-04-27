#ifndef KEYBOARDCONTROLLER_H
#define KEYBOARDCONTROLLER_H

#include <vector>
#include "State.h"
#include "Bullet.h"

class KeyboardController
{
public:
        KeyboardController(int &_xpos, int &_ypos, JUMPSTATE &_state, std::vector<Bullet*> &_bullet, int &_amo);
        ~KeyboardController();
        void Update();
        int jumpSpeed = 5;
        int fallSpeed = 5;
private:
    int *xPos, *yPos;
    int maxjumpedpos,maxjumpedpos2;
    JUMPSTATE* state;
    std::vector<Bullet*>* bullets;
    int* amo;
    bool Jump2;
};

#endif // KEYBOARDCONTROLLER_H
