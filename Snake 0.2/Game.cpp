#include "Game.h"

Game::Game()
{
    initSDL(window, renderer, WIDTH_SCREEN, HEIGHT_SCREEN, WINDOW_TITLE.c_str());
    stMenu.draw(renderer);
    MAP->draw(renderer);
    SNAKE->draw(renderer);
}
Game::~Game()
{
    delete MAP;
    delete SNAKE;
    quitSDL(window, renderer);
}
void Game::loop()
{
    while(running) {
    //        stMenu.loop(renderer, ingame);
        run_first_Menu();

        while(ingame) {
            int start_time=SDL_GetTicks();

            input();
            draw();
            update();
            render();

            int time_loop=SDL_GetTicks() - start_time;
            if(time_loop<175) SDL_Delay(175-time_loop);
        }

        reset();
    }
    stMenu.free();
    MAP->free();
    SNAKE->free();
}

void Game::input()
{
    while(SDL_PollEvent(&event)) {
        if(event.type == SDL_QUIT) {
            ingame = 0;
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
    cout<<MAP->fruit.x<<", "<<MAP->fruit.y<<endl;
    if(SNAKE->eatFruit(MAP->fruit) ) {
        bool sign=0;
        do {
            MAP->getFruit();
            for(int i=0;i<SNAKE->body.size();i++) {
                if(MAP->fruit.x==SNAKE->body[i].x && MAP->fruit.y==SNAKE->body[i].y) {
                    sign = 1;
                    break;
                }
            }
        }
        while (sign == true);

        ++SNAKE->score;
//        start = false;
    }

    if(SNAKE->CRASH(MAP->base_Array)) {
        ingame = false;
        endgame_signal = 1;
        cout<<"end";
    }
}
void Game::draw()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    MAP->base_Array[SNAKE->body[0].y][SNAKE->body[0].x] = SnakeHEAD;
    for(int i=0;i<SNAKE->body.size();i++) MAP->base_Array[SNAKE->body[i].y][SNAKE->body[i].x] = Snake;

}
void Game::render()
{
    if(endgame_signal) return;

    MAP->render(renderer);

    SNAKE->render(renderer);

    MAP->display_score(SNAKE->score, renderer);
    SDL_RenderPresent(renderer);
}

void Game::run_first_Menu()
{
    stMenu.render(renderer);
    stMenu.input(running);
    stMenu.handle_input(running, ingame);
}

void Game::reset()
{
    SNAKE->reset();

    bool sign=0;
    do {
        MAP->getFruit();
        for(int i=0;i<SNAKE->body.size();i++) {
            if(MAP->fruit.x==SNAKE->body[i].x && MAP->fruit.y==SNAKE->body[i].y) {
                sign = 1;
                break;
            }
        }
    }
    while (sign == true);

}
