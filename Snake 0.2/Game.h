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

    first_Menu* stMenu = nullptr;
    entity *SNAKE = nullptr;
    Map *MAP = nullptr;

    const int FPS = 1000/9;

    bool ingame = 0, running = 1, run_Menu = 1;
    SDL_Event event;

    bool endgame_signal=0;

public:
    Game();
    ~Game();
    void run_first_Menu();
    void loop();
    void update();
    void render();
    void input();
    void reset();
};

#endif // GAME_H
