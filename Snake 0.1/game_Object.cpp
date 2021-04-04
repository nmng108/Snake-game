#include "game_Object.h"
                        /**  class snake  */
void snake::event_handle(SDL_Event &event, bool &in_game, bool &running)
{
    if((event).type == SDL_KEYDOWN) {
        switch( (event).key.keysym.sym ) {
            case SDLK_UP:
            {
                DIRECTION = Up;
                break;
            }
            case SDLK_DOWN: DIRECTION = Down; break;
            case SDLK_LEFT: DIRECTION = Left; break;
            case SDLK_RIGHT: DIRECTION = Right; break;
            case SDLK_ESCAPE: in_game = false; running =0; break;
            default: DIRECTION = Freeze; break;
        }
    }
}

void snake::Move(Direction &old_DIRECTION, int column, int row)
{
    old_Point = HEAD;
    while(true) {
        if(DIRECTION == Right && old_DIRECTION != Left ) {
            HEAD.x = (HEAD.x + 1)% column;
            old_DIRECTION = DIRECTION; break;
        }
        else if(DIRECTION == Left && old_DIRECTION != Right) {
            HEAD.x = (column + HEAD.x -1) % column;
            old_DIRECTION = DIRECTION;  break;
        }
        else if(DIRECTION == Down && old_DIRECTION != Up) {
            HEAD.y = (HEAD.y + 1) % row;
            old_DIRECTION = DIRECTION;  break;
        }
        else if(DIRECTION == Up && old_DIRECTION != Down) {
            HEAD.y = (row + HEAD.y - 1) % row;
            old_DIRECTION = DIRECTION;  break;
        }
        else if(DIRECTION==Freeze) {
            old_DIRECTION = DIRECTION; break;
        }
        else DIRECTION = old_DIRECTION;
    } /* cout<<HEAD.x<<" "<<HEAD.y<<endl; */
//    body.resize(body_CELL);
    if(DIRECTION != Freeze)
        for(int i=0;i<body.size();i++) {
            Point tmp_point = body[i];
            body [i] = old_Point;
            old_Point = tmp_point;
        }
}

bool snake::eatFruit(Point fruit)
{
    if(fruit.x == HEAD.x && fruit.y == HEAD.y) return 1;
    else return 0;
}

void snake::getLonger()
{
    body_CELL++;
    body.resize(body_CELL);
}

bool snake::CRASH() {
    for(int i=0;i<body.size();i++){
        if( (HEAD.x==body[i].x && HEAD.y==body[i].y) ) {cout<<"happened"<<endl; DIRECTION =Freeze; return 1;}
    }
    return 0;
}
                        /**  class Map */
void Map::create_Map()
{
    board.resize(row);
    for(int i=0;i<row;i++) board[i].assign(column, Blank);
}

Point Map::getFruit(snake SNAKE)
{
    srand(time(0));

    Point fruit;
    bool loop = false;
    do {
        fruit.x = rand()% column;
        fruit.y = rand()% row;

        for(int i=0;i<SNAKE.body.size();i++) {
            if((fruit.x == SNAKE.body[i].x && fruit.y == SNAKE.body[i].y) ||
                    (fruit.x == SNAKE.HEAD.x && fruit.y == SNAKE.HEAD.y)) {
                loop = true;
                break;
            }
        }
    }
    while(loop);
    return fruit;
}

vector<vector<object>> Map::show_in_2Darray(snake SNAKE)
{
    board[SNAKE.HEAD.y][SNAKE.HEAD.x] = SnakeHEAD;
    for(int i=0;i<SNAKE.body.size();i++) {
        board [SNAKE.body[i].y][SNAKE.body[i].x] = Snake;
    }
    board[fruit.y][fruit.x] = Fruit;
    return board;
}

void render_with_2Darray(vector<vector<object>> MAP, int side_of_aUnit, SDL_Renderer *ren)
{
    for(int i=0;i<MAP.size();i++) {
        for(int j=0;j<MAP[0].size();j++)
        {
            SDL_Rect rect;
            if(MAP[i][j]== Snake) {
                SDL_SetRenderDrawColor(ren,55, 129, 81,255);
                rect.x = side_of_aUnit * j;
                rect.y = side_of_aUnit * i;
                rect.h = side_of_aUnit;
                rect.w = side_of_aUnit;
                SDL_RenderFillRect (ren,&rect);
            }
            if(MAP[i][j]==Fruit) {
                SDL_SetRenderDrawColor(ren,164, 10, 73,255);
                rect.x = side_of_aUnit * j;
                rect.y = side_of_aUnit * i;
                rect.h = side_of_aUnit;
                rect.w = side_of_aUnit;
                SDL_RenderFillRect (ren,&rect);
            }
            if(MAP[i][j]==SnakeHEAD) {
                SDL_SetRenderDrawColor(ren,13, 20, 145,255);
                rect.x = side_of_aUnit * j;
                rect.y = side_of_aUnit * i;
                rect.h = side_of_aUnit;
                rect.w = side_of_aUnit;
                SDL_RenderFillRect (ren,&rect);

            }
        }
    }
}

