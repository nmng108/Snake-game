#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <SDL.h>
#include "SDL_utils.h"
#include "event_Handle.h"
#include "game_Object.h"

using namespace std;

string WIN_TITLE="game";
int SCREEN_HEIGHT=540;
int SCREEN_WIDTH=960;
int side_of_aUnit=20;

int Column_Board=SCREEN_WIDTH/side_of_aUnit,
    Row_Board=SCREEN_HEIGHT/side_of_aUnit;

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Event event;

Map MAP(Column_Board, Row_Board);
//int origin_x = SCREEN_WIDTH/4,
//    origin_y = SCREEN_HEIGHT/2;

Direction old_DIRECTION=Freeze;

int main(int argc, char* argv[])
{
    const int time_per_frame=1000/60;
    initSDL(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT, WIN_TITLE.c_str() );


    bool in_game=1, running = 1;

    while(running) {
        snake *SNAKE = new snake;
        MAP.fruit = MAP.getFruit(*SNAKE);

        (*SNAKE).HEAD = {Column_Board/2, Row_Board/2};
        (*SNAKE).body.push_back({Column_Board/2-1, Row_Board/2});

    int count=0;
        while(in_game) {
            int start_time=SDL_GetTicks();

            SDL_SetRenderDrawColor(renderer, 0, 0, 0,255);
            SDL_RenderClear(renderer);

            MAP.create_Map();
//            while(SDL_PollEvent(&event)) {
//                if(event.type == SDL_QUIT) {
//                    in_game = 0; running = 0;
//                    break;
//                }
//                SNAKE->event_handle(event, in_game, running);
//
//            }
            Event_Handle(in_game, running, *SNAKE);
            if(SNAKE->CRASH()) {cin>>running; break; }

            if( SNAKE->eatFruit(MAP.fruit) ) {
                SNAKE->getLonger();
                MAP.fruit = MAP.getFruit(*SNAKE);
                cout<<++count<<endl;
            }
            SNAKE->Move(old_DIRECTION, Column_Board, Row_Board);
    //        SNAKE->update_in_array();
            vector<vector<object>> update_Map = MAP.show_in_2Darray(*SNAKE);

            render_with_2Darray(update_Map, side_of_aUnit, renderer);
            SDL_RenderPresent(renderer);

            int mainloop_time = SDL_GetTicks() - start_time;  //mainloop_time is considered as time per frame  time_per_frame - mainloop_time
            if(mainloop_time < time_per_frame) ;
            SDL_Delay(115);
        }

        delete SNAKE;
    }

    quitSDL(window, renderer);
    return 0;
}
