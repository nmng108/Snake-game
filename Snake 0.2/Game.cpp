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
//    delete MAP; //cause error when closing program
    delete stMenu;
    delete SNAKE;
}

void Game::loop()
{
    while(running) {
        int level = 0;
        stMenu->open(run_Menu, running, ingame);

        ingame_loop(level);

        after_game();
    }
}

void Game::ingame_loop(int &level)
{
    reset();
    if(running) display_level(level+1);
    while(ingame) {
        int start_time=SDL_GetTicks();

        if(SNAKE->levelup()) {
            if( (++level) == MAP->number_of_maps) {
                win = true;
                ingame = false;
                endgame_signal = 1;
                return;
            }
        }

        input();
        update(level);
        render();

        int time_loop=SDL_GetTicks() - start_time;
        if(time_loop<(1000/FPS)) SDL_Delay( (1000/FPS)-time_loop );
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
                case SDLK_s: SNAKE->DIRECTION = Down; cout<<"down\n"; break;
                case SDLK_UP: SNAKE->DIRECTION = Up; cout<<"up\n"; break;
                case SDLK_w: SNAKE->DIRECTION = Up; cout<<"up\n"; break;
                case SDLK_LEFT: SNAKE->DIRECTION = Left; cout<<"left\n"; break;
                case SDLK_a: SNAKE->DIRECTION = Left; cout<<"left\n"; break;
                case SDLK_RIGHT: SNAKE->DIRECTION = Right; cout<<"right\n"; break;
                case SDLK_d: SNAKE->DIRECTION = Right; cout<<"right\n"; break;
                case SDLK_ESCAPE: ingame=0; cout<<"11\n"; break;
                default: break;
            }
        }
//        SNAKE->Move();
    }
}
void Game::update(int &level)
{
    MAP->create_Map(level);

    if(SNAKE->eatFruit(MAP->fruit) ) {
        MAP->getFruit(*SNAKE);
        ++SNAKE->score;
    }

    SNAKE->Move();

    if(SNAKE->CRASH(MAP->base_Array)) {
        ingame = false;
        endgame_signal = 1;
        cout<<"end\n";
        return;
    }

    if(SNAKE->levelup()) {

        if((++level) != MAP->number_of_maps) {
            display_level(level+1);
            MAP->getFruit(*SNAKE);
        }
    }


    if(MAP->base_Array[MAP->fruit.y][MAP->fruit.x] == Wall) MAP->getFruit(*SNAKE);
    MAP->base_Array[MAP->fruit.y][MAP->fruit.x] = Fruit;
    for(int i=0;i<SNAKE->body.size();i++) MAP->base_Array[SNAKE->body[i].y][SNAKE->body[i].x] = Snake;
    MAP->base_Array[SNAKE->body[0].y][SNAKE->body[0].x] = SnakeHEAD;
}

void Game::render()
{
    if(endgame_signal==1) {
//        if(win) renderTexture("Resource/Image/game win.png", renderer, 0, 0);
        return;
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    MAP->render();

    SNAKE->render();

    MAP->display_score(SNAKE->score);
    SDL_RenderPresent(renderer);
}

void Game::reset()
{
    SNAKE->reset();
    MAP->getFruit(*SNAKE);
    endgame_signal = win = 0;
}

void Game::after_game()
{
    if(running==false) return;

    stMenu->process_score_log(SNAKE->score);

        run_Menu=false;

    for(int i=0;i<60;i++) {
        int s=SDL_GetTicks();

        SDL_Color cr={236, 28, 36, 5+i*2};
        string font="Resource/Fonts/itckrist.ttf";
        SDL_Texture *msg=loadTexture_text("GAME OVER !", cr, "Resource/Fonts/Aller/Aller_Lt.ttf", 50, renderer);
        SDL_Point dst;
        SDL_QueryTexture(msg, NULL, NULL, &dst.x, &dst.y);
        renderTexture(msg, renderer, (WIDTH_SCREEN/2-dst.x/2), 240);
        SDL_DestroyTexture(msg);
        SDL_RenderPresent(renderer);

        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                running = false;
                return;
            }
        }

        int time_loop=SDL_GetTicks()-s;
        if(time_loop<20) SDL_Delay(20-time_loop);
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    if(!win) renderTexture("Resource/Image/game lose.png", renderer, 0, 0); //add game winning screen
    else renderTexture("Resource/Image/game win.png", renderer, 0, 0);

    string font="Resource/Fonts/itckrist.ttf";
    SDL_Color color = {229, 156, 108, 255};
    string tmp = "Your score is " + to_string(SNAKE->score);
    SDL_Texture *sc=loadTexture_text(tmp, color, font, 40, renderer);
    SDL_Point dst;
    SDL_QueryTexture(sc, NULL, NULL, &dst.x, &dst.y);
    renderTexture(sc, renderer, (WIDTH_SCREEN-dst.x)/2, 400);
    SDL_DestroyTexture(sc);

    SDL_RenderPresent(renderer);

    event.type=SDL_FIRSTEVENT;
    while(true)
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                running = false;
                return;
            }
            if(event.type == SDL_KEYDOWN) {
                run_Menu = true;
                return;
            }
        }
}

void Game::display_level(int const level)
{
    for(int i=0;i<50;i++) {
        int s=SDL_GetTicks();

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);

        string tmp="Level " + to_string(level);
        SDL_Color color = {24, 99, 0, 0};
        SDL_Texture *lv=loadTexture_text(tmp, color, "Resource/Fonts/ALler/Aller_Bd.ttf", 70, renderer);
        SDL_Point dst;
        SDL_QueryTexture(lv, NULL, NULL, &dst.x, &dst.y);
        renderTexture(lv, renderer, (WIDTH_SCREEN-dst.x)/2, 300);
        SDL_RenderPresent(renderer);

        event.type=SDL_FIRSTEVENT;
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                running = false;
                return;
            }
        }

        int time_loop=SDL_GetTicks() - s;
        if(time_loop<20) SDL_Delay(20-time_loop);
    }
}


