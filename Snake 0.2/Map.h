#ifndef MAP_H
#define MAP_H

#include "SDL_utils.h"
#include "Texture.h"
#include "game_Object.h"
using namespace std;



class Map { //include map, wall and fruit
    SDL_Renderer *renderer;
    SDL_Texture *ground_Texture=nullptr,
                *fruit_Texture=nullptr,
                *wall_Texture=nullptr;

public:
    //use in snake::move<void>
    Map(SDL_Renderer* ren);
    ~Map();
    vector<vector<int>> base_Array;

    void choose_Map();    // ***
    void create_Map(); //include wall(or not)

    void getFruit();
    SDL_Point fruit = {18, 0};

    void draw();
    void render();
    void display_score(int score);

    void free() {
//        SDL_DestroyTexture(ground_Texture);
//        SDL_DestroyTexture(fruit_Texture);
//        SDL_DestroyTexture(wall_Texture);
//        ground_Texture=nullptr,
//        fruit_Texture=nullptr,
//        wall_Texture=nullptr;
    }

//    vector<vector<object>> show_in_2Darray(snake SNAKE); //take fruit, snake::body+HEAD,
};

#endif // MAP_H
