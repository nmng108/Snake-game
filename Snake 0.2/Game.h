#ifndef GAME_H
#define GAME_H

#include "game_Object.h"
#include "Map.h"
#include "Texture.h"
#include "Menu.h"
using namespace std;

class Game {
    string WINDOW_TITLE = "Classic Snake -  by Nguyen Hai Nam";
    SDL_Window *window;
    SDL_Renderer *renderer;

    first_Menu stMenu;
    entity *SNAKE = new entity;
    Map *MAP = new Map;
    bool ingame = 0, running = 1;
    SDL_Event event;

    bool endgame_signal=0;
//    bool start=1;
public:
    Game();
    ~Game();
    void run_first_Menu();
    void loop();
    void update();
    void draw();
    void render();
    void input();
    void reset();
};

#endif // GAME_H
