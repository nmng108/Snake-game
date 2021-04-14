#ifndef GAME_H
#define GAME_H

#include "game_Object.h"
#include "Map.h"
#include "Texture.h"
using namespace std;

class Game {
    string WINDOW_TITLE = "Classic Snake -  by Nguyen Hai Nam";
    SDL_Window *window;
    SDL_Renderer *renderer;

    entity *SNAKE = new entity;
    Map *MAP = new Map;
    bool ingame = 1, running = 1;
    SDL_Event event;

    bool endgame_signal=0;
//    bool start=1;
public:
    Game();
    ~Game();
    void loop();
    void update();
    void draw();
    void render();
    void input();
};

#endif // GAME_H
