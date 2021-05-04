#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H
#include "SDL_utils.h"
#include "Texture.h"
using namespace std;

class snake { //go straight, divert
protected:
    Direction old_DIRECTION=Freeze;
    int const velocity=1;

    struct POS_n_DIR
    {
        int x, y;
        Direction direction;
        int angle;
        bool turning;
    };
public:
    void Move();
    void reset();

    Direction DIRECTION = Freeze;
    vector <POS_n_DIR> body;
    int score = 0;
    int score_needed_to_pass_aLevel = 3;

    bool eatFruit(SDL_Point fruit); //get longer
    bool CRASH(vector<vector<int>> Map); //return 1 if happening accident
    bool levelup();
};

class entity : public snake
{
    SDL_Renderer *renderer;
    vector<SDL_Texture*> img_HEAD;
    SDL_Texture *img_BODY=nullptr,
                *img_tail=nullptr,
                *img_bend=nullptr;
//    SDL_Texture *img_=nullptr;

    int tmp_index=0;

    void rotate_body();
public:
    entity(SDL_Renderer *ren){
        renderer = ren;
        reset();
        draw();
    }
    ~entity();

    void draw();
    void render();

};
#endif // GAME_OBJECT_H
