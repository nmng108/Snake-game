#ifndef MAP_H
#define MAP_H

#include "SDL_utils.h"
#include "Texture.h"
#include "game_Object.h"
using namespace std;

class Food {
        Uint32 const existence_time = 3000;
        SDL_Renderer *renderer;
        SDL_Texture *image = NULL;
        object obj;

    public:
        Food(SDL_Renderer *ren, const string &IMG_file, object obj_type);
        ~Food();
        SDL_Point position = {18, 0};

        bool exist();
        bool eaten = 0;

        void appear(vector<vector<int>> &base_Array, vector<Pos_n_Dir> Snake_Body);
        void render();

        Uint32 start_time = 0;
};

class Map { //include map, wall and fruit
    SDL_Renderer *renderer;

    SDL_Texture *wall_Texture = NULL;
    SDL_Texture *key_icon = NULL;

    vector<string> list_of_Maps;

    int condition_to_take_bonus_score=0;

public:
    Map(SDL_Renderer* ren);
    ~Map();

    Food* GIFT = nullptr;
    Food* FRUIT = nullptr;

    vector<vector<int>> base_Array;

    int number_of_maps = 5;
    void create_Map(int mapList_index); //include wall(or not)

    void getFood(vector<Pos_n_Dir> Snake_Body);
    SDL_Point fruit = {18, 0};

    void draw();
    void render();
    void display_score(int score);
    void reset(int level, vector<Pos_n_Dir> Snake_Body);
};

#endif // MAP_H
