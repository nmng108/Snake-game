#ifndef MAP_H
#define MAP_H

#include "SDL_utils.h"
#include "Texture.h"
using namespace std;



class Map { //include map, wall and fruit
    int col=WIDTH_SCREEN/CELL_side;
    int row =(HEIGHT_SCREEN-100)/CELL_side;
public:
    //use in snake::move<void>
//    Map();
    ~Map();
    SDL_Texture *ground_Texture, *fruit_Texture, *wall_Texture;
    vector<vector<int>> base_Array;
    void choose_Map();
    void create_Map(); //include wall(or not)
    void getFruit();
    SDL_Point fruit;
//    vector<vector<object>> show_in_2Darray(snake SNAKE); //take fruit, snake::body+HEAD,
};

#endif // MAP_H
