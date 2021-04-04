#ifndef GAME_H
#define GAME_H

#include "game_Object.h"
#include "Map.h"
#include "Texture.h"
using namespace std;

class Game {
    string WINDOW_TITLE = "Classic Snake - with cpp & SDL2 by NHN";
    SDL_Window *window;
    SDL_Renderer *renderer;

    Map MAP;
    entity SNAKE;
    bool ingame = 1, running = 1;
    SDL_Event event;
public:
    Game();
    ~Game();
    void loop();
    void update();
    void render();
    void draw();
    void input();
};

#endif // GAME_H
