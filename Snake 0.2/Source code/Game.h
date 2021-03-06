#ifndef GAME_H
#define GAME_H

#include "game_Object.h"
#include "Map.h"
#include "Texture.h"
#include "Menu.h"
using namespace std;

class Game {
    string WINDOW_TITLE = "Snake Game - made with SDL2 by Nguyen Hai Nam";
    SDL_Window *window;
    SDL_Renderer *renderer;

    first_Menu* stMenu = nullptr;
    second_Menu* ndMenu = nullptr;
    entity *SNAKE = nullptr;
    Map *MAP = nullptr;

    double FPS = 7; //considered as snake's velocity, change to 11 when press & hold moving key
    int level = 0;

    SDL_Event event;

    Mix_Music *lose_Sound = NULL,
              *win_Sound = NULL;

    bool ingame = 0, running = 1, run_Menu = 1;
    bool win=0, start = 0, pause = 0;

    void ingame_loop();
    void update();
    void render();
    void input();
    void reset();
    void display_level();
    void after_game();

public:
    Game();
    ~Game();
    void loop();
};

#endif // GAME_H
