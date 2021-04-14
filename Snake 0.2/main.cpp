#include "Game.h"

int main(int agrc, char* agrv[])
{
    Game *SNAKE_game = new Game;
    SNAKE_game->loop();
    delete SNAKE_game;
    return 0;
}
