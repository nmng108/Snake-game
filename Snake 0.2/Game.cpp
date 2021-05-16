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
//    delete MAP; //causes error when closing the program
    delete stMenu;
    delete ndMenu;
    delete SNAKE;

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
        display_level();

        while(ingame) {
            Uint32 start_time=SDL_GetTicks();

            input();

            if(pause) ndMenu->open(running, start, ingame);
            pause = 0;

            update();

            render();

            if(SNAKE->levelup()) {

                MAP->GIFT->position={18, 0};

                if( (++level) == MAP->number_of_maps) {
                    win = true;
                    ingame = start = false;
                    return;
                }
                else {
                    display_level();
                    MAP->reset(level, SNAKE->body);
                }
            }

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
                case SDLK_DOWN: SNAKE->DIRECTION = Down; break;
                case SDLK_s: SNAKE->DIRECTION = Down; break;
                case SDLK_UP: SNAKE->DIRECTION = Up; break;
                case SDLK_w: SNAKE->DIRECTION = Up; break;
                case SDLK_LEFT: SNAKE->DIRECTION = Left; break;
                case SDLK_a: SNAKE->DIRECTION = Left; break;
                case SDLK_RIGHT: SNAKE->DIRECTION = Right; break;
                case SDLK_d: SNAKE->DIRECTION = Right; break;
                case SDLK_ESCAPE: SNAKE->DIRECTION = Freeze; pause = true; cout<<"pause\n"; break;
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
void Game::update()
{
    MAP->create_Map(level);

    SNAKE->Move();

    if(SNAKE->CRASH(MAP->base_Array)) {
        ingame = start = false;
        return;
    }

    if(SNAKE->eatFood(MAP->FRUIT->position, MAP->FRUIT->eaten, MAP->GIFT->position, MAP->GIFT->eaten, MAP->GIFT->start_time) ) {
        MAP->getFood(SNAKE->body);
    }

    if(!MAP->GIFT->exist()) MAP->GIFT->position={18, 0};

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
    level = 0;
    SNAKE->reset();
    MAP->reset(level, SNAKE->body);
    ingame = true;
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

void Game::display_level()
{
    SDL_Color color = {24, 99, 0, 0};
    SDL_Texture *lv=loadTexture_text("Level " + to_string(level+1), color, "Resource/Fonts/ALler/Aller_Bd.ttf", 70, renderer);
    SDL_Point dst;
    SDL_QueryTexture(lv, NULL, NULL, &dst.x, &dst.y);

    for(int i=0;i<50;i++) {
        int s=SDL_GetTicks();

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);
        renderTexture(lv, renderer, (WIDTH_SCREEN-dst.x)/2, 300);

        SDL_RenderPresent(renderer);

        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                running = start = ingame = false;
                return;
            }
        }

        int time_loop=SDL_GetTicks() - s;
        if(time_loop<25) SDL_Delay(25-time_loop);
    }

    SDL_DestroyTexture(lv);
    lv=NULL;
}


