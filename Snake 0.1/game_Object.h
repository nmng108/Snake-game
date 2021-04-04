#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H
#include <iostream>
#include <ctime>
#include <vector>
#include "SDL_utils.h"
using namespace std;
enum Direction
{
    Freeze,
    Up,
    Down,
    Left,
    Right
} ;

struct Point{
    int x, y;
};

enum object
{
    Snake,
    SnakeHEAD,
    Wall,
    Fruit,
    Blank
};

class snake {
public:
    Point HEAD;
    vector <Point> body;
     void event_handle(SDL_Event &event, bool &in_game, bool &running);
    void Move(Direction &old_DIRECTION, int column, int row);
    void update_in_array(); // undefined
    bool eatFruit(Point fruit);
    void getLonger();
    Direction DIRECTION = Freeze;
    bool CRASH(); //return 1 if happening accident
private:
    Point old_Point;
    int body_CELL=1;
};

class Map { //include map, wall and fruit
public:
    int row, column; //use in snake::move<void>

    Map(int getCOL, int getROW) {
        row = getROW; column = getCOL;
    }
    vector<vector<object>> board;
    void create_Map(); //include wall(or not)
    Point getFruit(snake SNAKE);
    Point fruit;
    vector<vector<object>> show_in_2Darray(snake SNAKE); //take fruit, snake::body+HEAD,
};

void render_with_2Darray(vector<vector<object>> MAP, int side_of_aUnit, SDL_Renderer *ren);
#endif // GAME_OBJECT_H
