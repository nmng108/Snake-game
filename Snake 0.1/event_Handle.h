#ifndef EVENT_HANDLE_H
#define EVENT_HANDLE_H
#include <iostream>
#include "SDL_utils.h"
#include "game_Object.h"

using namespace std;

void Event_Handle(bool &in_game, bool &running, snake &SNAKE);
enum Mouse {
    DOWN_LEFT,
    DOWN_RIGHT,
    UP_LEFT,
    UP_RIGHT,
    NOTHING
};

#endif // EVENT_HANDLE_H
