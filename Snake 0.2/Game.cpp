#include "Game.h"

Game::Game()
{
    initSDL(window, renderer, WIDTH_SCREEN, HEIGHT_SCREEN, WINDOW_TITLE.c_str());
    stMenu = new first_Menu(renderer);
    MAP = new Map (renderer);
    SNAKE = new entity(renderer);
}
Game::~Game()
{
    quitSDL(window, renderer);
//    delete MAP;
//    delete stMenu;
//    delete SNAKE;
}
void Game::loop()
{
    MAP->getFruit(*SNAKE);
    while(running) {
        run_Menu = 1;
        stMenu->loop(run_Menu, running, ingame);
//        run_first_Menu();

        while(ingame) {
            int start_time=SDL_GetTicks();

            input();
            update();
            render();

            int time_loop=SDL_GetTicks() - start_time;
            if(time_loop<175) SDL_Delay(175-time_loop);
        }

        reset();
    }
}

void Game::input()
{
    while(SDL_PollEvent(&event)) {
        if(event.type == SDL_QUIT) {
            ingame = 0;
            running = 0;
            break;
        }
        if(event.type == SDL_KEYDOWN) {
            switch(event.key.keysym.sym) {
                case SDLK_DOWN: SNAKE->DIRECTION = Down; cout<<"down\n"; break;
                case SDLK_UP: SNAKE->DIRECTION = Up; cout<<"up\n"; break;
                case SDLK_LEFT: SNAKE->DIRECTION = Left; cout<<"left\n"; break;
                case SDLK_RIGHT: SNAKE->DIRECTION = Right; cout<<"right\n"; break;
                case SDLK_SPACE: SNAKE->DIRECTION = Freeze; cout<<"freeze\n"; break;
                case SDLK_ESCAPE: ingame=0; break;
                default: break;
            }
        }
//        SNAKE->Move();
    }
}
void Game::update()
{
    SNAKE->Move();

    if(SNAKE->CRASH(MAP->base_Array)) {
        ingame = false;
        endgame_signal = 1;
        cout<<"end\n";
        return;
    }

    MAP->create_Map();
    MAP->base_Array[MAP->fruit.y][MAP->fruit.x] = Fruit;
    for(int i=0;i<SNAKE->body.size();i++) MAP->base_Array[SNAKE->body[i].y][SNAKE->body[i].x] = Snake;
    MAP->base_Array[SNAKE->body[0].y][SNAKE->body[0].x] = SnakeHEAD;

    if(SNAKE->eatFruit(MAP->fruit) ) {
//        bool sign=0;
//        do {
//            sign = 0;
            MAP->getFruit(*SNAKE);
//            for(int i=0;i<SNAKE->body.size();i++) {
//                if(MAP->fruit.x==SNAKE->body[i].x && MAP->fruit.y==SNAKE->body[i].y) {
//                    sign = 1;
//                    break;
//                }
//            }
//        }
//        while (sign == true);

        ++SNAKE->score;
//        start = false;
    }


}

void Game::render()
{
    if(endgame_signal) return;

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    MAP->render();

    SNAKE->render();

    MAP->display_score(SNAKE->score);
    SDL_RenderPresent(renderer);
}

//void Game::run_first_Menu()
//{
//    stMenu->render();
//    stMenu->input(running);
//    stMenu->handle_input(running, ingame);
//}

void Game::reset()
{
    SNAKE->reset();

    bool sign=0;
    do {
        sign = 0;
        MAP->getFruit(*SNAKE);
//        for(int i=0;i<SNAKE->body.size();i++) {
//            if(MAP->fruit.x==SNAKE->body[i].x && MAP->fruit.y==SNAKE->body[i].y) {
//                sign = 1;
//                break;
//            }
//        }
    }
    while (sign == true);

    endgame_signal = 0;
}
