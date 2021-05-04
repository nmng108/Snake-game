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

    const double FPS = 7;

    SDL_Event event;

    bool ingame = 0, running = 1, run_Menu = 1;
    bool endgame_signal = 0, win=0, game_continue = 1;

    void ingame_loop(int &level);
    void update(int &level);
    void render();
    void input();
    void reset();
    void display_level(int const level);
    void after_game();

public:
    Game();
    ~Game();
    void loop();
};

#endif // GAME_H
