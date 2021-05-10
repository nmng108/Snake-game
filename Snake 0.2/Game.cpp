#include "Game.h"

Game::Game()
{
    initSDL(window, renderer, WIDTH_SCREEN, HEIGHT_SCREEN, WINDOW_TITLE.c_str());
    stMenu = new first_Menu(renderer);
    ndMenu = new second_Menu(renderer);
    MAP = new Map (renderer);
    SNAKE = new entity(renderer);

    lose_Sound = loadMusic("Resource/negative_tone.wav", "Game losing music");
    win_Sound = loadMusic("Resource/win.wav", "Game winning music");
}
Game::~Game()
{
    quitSDL(window, renderer);
    MAP->free();
    delete stMenu;
    delete ndMenu;
    SNAKE->free();
//    delete SNAKE;

    Mix_FreeMusic(lose_Sound);
    Mix_FreeMusic(win_Sound);
    lose_Sound = win_Sound = NULL;
}

void Game::loop()
{
    while(running) {
        stMenu->open(run_Menu, running, start);

        ingame_loop();

        after_game();
    }
}

void Game::ingame_loop()
{
    while(start) {
        reset();
        ingame = 1;
        int level = 0;
        display_level(level+1);

        while(ingame) {
            Uint32 start_time=SDL_GetTicks();

            input();

            if(pause) ndMenu->open(running, start, ingame);

            update(level);

            render();

            Uint32 time_loop=SDL_GetTicks() - start_time;
            if(time_loop<(1000/FPS)) SDL_Delay( (1000/FPS)-time_loop );
        }
    }
}

void Game::input()
{
    const Uint8 *keystates = SDL_GetKeyboardState(NULL);

    while(SDL_PollEvent(&event)) {
        if(event.type == SDL_QUIT) {
            running = start = ingame = 0;
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
                case SDLK_ESCAPE: SNAKE->DIRECTION = Freeze; pause = true; cout<<"pause\n"; break;
                case SDLK_SPACE: SNAKE->DIRECTION = Freeze; pause = true; cout<<"pause\n"; break;
                default: break;
            }
        }
        if(event.key.repeat) FPS=11;
        else FPS=7;
    }

    if(keystates[SDL_SCANCODE_LEFT] || keystates[SDL_SCANCODE_A]) SNAKE->DIRECTION = Left;
    if(keystates[SDL_SCANCODE_RIGHT] || keystates[SDL_SCANCODE_D]) SNAKE->DIRECTION = Right;
    if(keystates[SDL_SCANCODE_DOWN] || keystates[SDL_SCANCODE_S])SNAKE->DIRECTION = Down;
    if(keystates[SDL_SCANCODE_UP] || keystates[SDL_SCANCODE_W]) SNAKE->DIRECTION = Up;
}
void Game::update(int &level)
{
    pause = 0;

    MAP->create_Map(level);

    if(SNAKE->eatFruit(MAP->fruit) ) {
        MAP->getFruit(*SNAKE);
    }

    if(SNAKE->levelup()) {
        if( (++level) == MAP->number_of_maps) {
            win = true;
            ingame = start = false;
            return;
        }
        else {
            display_level(level+1);
            MAP->create_Map(level);
            MAP->getFruit(*SNAKE);
        }
    }

    SNAKE->Move();

    if(SNAKE->CRASH(MAP->base_Array)) {
        ingame = start = false;
        return;
    }

    if(MAP->base_Array[MAP->fruit.y][MAP->fruit.x] == Wall) MAP->getFruit(*SNAKE);
    MAP->base_Array[MAP->fruit.y][MAP->fruit.x] = Fruit;
    for(int i=0;i<SNAKE->body.size();i++) MAP->base_Array[SNAKE->body[i].y][SNAKE->body[i].x] = Snake;
    MAP->base_Array[SNAKE->body[0].y][SNAKE->body[0].x] = SnakeHEAD;
}

void Game::render()
{
    if(ingame==0) {
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
    win = false;
}

void Game::after_game()
{
    if(running==false) return;

    int rank_sort;

    stMenu->process_score_log(SNAKE->score, rank_sort);

    for(Uint8 i=0;i<60;i++) {
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
    if(!win) {
        renderTexture("Resource/Image/game lose.png", renderer, 0, 0); //add game winning screen
        if(!Mix_PlayingMusic()) Mix_PlayMusic(lose_Sound, 0);
    }
    else {
        renderTexture("Resource/Image/game win.png", renderer, 0, 0);
        if(!Mix_PlayingMusic()) Mix_PlayMusic(win_Sound, 0);
    }

    string font="Resource/Fonts/itckrist.ttf";
    SDL_Color color = {229, 156, 108, 255};
    SDL_Texture *sc=loadTexture_text("Your score is " + to_string(SNAKE->score), color, font, 45, renderer);
    SDL_Point dst;
    SDL_QueryTexture(sc, NULL, NULL, &dst.x, &dst.y);
    renderTexture(sc, renderer, (WIDTH_SCREEN-dst.x)/2, 380);
    SDL_DestroyTexture(sc);
    sc=NULL;

    switch(rank_sort)
    {
        case 0: renderTexture("Resource/Image/1st.png", renderer, 620, 360, 75, 75, 0); break;
        case 1: renderTexture("Resource/Image/2nd.png", renderer, 620, 360, 75, 75, 0); break;
        case 2: renderTexture("Resource/Image/3th.png", renderer, 620, 360, 75, 75, 0); break;
    }

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
                if(Mix_PlayingMusic()) Mix_HaltMusic();
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
                running = ingame = false;
                return;
            }
        }

        int time_loop=SDL_GetTicks() - s;
        if(time_loop<25) SDL_Delay(25-time_loop);
    }
}


