#include "Game.h"

int main(int agrc, char* agrv[])
{
    Game *SNAKE = new Game;
    SNAKE->loop();
    delete SNAKE;
    return 0;
}
