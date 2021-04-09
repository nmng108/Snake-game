#include "Game.h"

Game::Game()
{
    initSDL(window, renderer, WIDTH_SCREEN, HEIGHT_SCREEN, WINDOW_TITLE.c_str());
    MAP.create_Map();   // đem vào hàm khởi tạo?
    MAP.ground_Texture=loadTexture("Resourse/Image/grass.png", renderer);
    MAP.wall_Texture=loadTexture("Resourse/Image/block.jpg", renderer);
    MAP.fruit_Texture=loadTexture("Resourse/Image/snake2/apple-removebg.png", renderer);
    SNAKE.draw(renderer);

}
Game::~Game()
{
    quitSDL(window, renderer);
}
void Game::loop()
{
    while(ingame) {
//        int start_time=SDL_GetTicks();
//        MAP.create_Map();   // đem vào hàm khởi tạo?
        input();
        draw();
        update();
        render();
//        int time_loop=SDL_GetTicks() - start_time;
//        if(time_loop<1000/75) SDL_Delay(1000/75-time_loop);
        input();
        SDL_Delay(200);
    }
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
                case SDLK_DOWN: SNAKE.DIRECTION = Down; cout<<"down"; break;
                case SDLK_UP: SNAKE.DIRECTION = Up; cout<<"up"; break;
                case SDLK_LEFT: SNAKE.DIRECTION = Left; cout<<"left"; break;
                case SDLK_RIGHT: SNAKE.DIRECTION = Right; cout<<"right"; break;
                case SDLK_SPACE: SNAKE.DIRECTION = Freeze; cout<<"freeze"; break;
                case SDLK_ESCAPE: ingame=0; break;
                default: break;
            }
        }
    }
}
void Game::update()
{
    if(SNAKE.eatFruit(MAP.fruit) || start == true) {
        MAP.getFruit();
        cout<<++SNAKE.score<<endl;
        start = false;
    }
    SNAKE.Move();
    if(SNAKE.CRASH(MAP.base_Array)) {
        ingame = false;
        endgame_signal = 1;
        cout<<"end";
    }
}
void Game::draw()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    MAP.base_Array[SNAKE.body[0].y][SNAKE.body[0].x] = SnakeHEAD;
    for(int i=0;i<SNAKE.body.size();i++) MAP.base_Array[SNAKE.body[i].y][SNAKE.body[i].x] = Snake;

}
void Game::render()
{
    if(endgame_signal) return;

//    renderTexture(MAP.ground_Texture, renderer, 0, 0, WIDTH_SCREEN, HEIGHT_SCREEN-100);
    for(int i=0;i<MAP.base_Array.size();i++){
        for(int j=0;j<MAP.base_Array[0].size();j++) {
//            SDL_Rect dest;
            if(MAP.base_Array[i][j]==Wall) renderTexture(MAP.wall_Texture, renderer, j*CELL_side, i*CELL_side, CELL_side, CELL_side);
            if(MAP.base_Array[i][j]==Fruit) renderTexture(MAP.fruit_Texture, renderer, j*CELL_side, i*CELL_side, CELL_side, CELL_side);
//            if(MAP.base_Array[i][j]==Blank) renderTexture(MAP.ground_Texture, renderer, j*CELL_side, i*CELL_side, CELL_side, CELL_side);
        }
    }
    SNAKE.render(renderer);

    MAP.display_score(SNAKE.score, renderer);
    SDL_RenderPresent(renderer);
}
