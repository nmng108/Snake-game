#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H
#include "SDL_utils.h"
#include "Texture.h"
using namespace std;

    struct Pos_n_Dir
    {
        int x, y;
        Direction direction;
        int angle;
        bool turning;
    };

class snake { //go straight, divert
protected:
    Direction old_DIRECTION=Freeze;

    Pos_n_Dir prev_pos={18, 0};

    const int velocity=1;
    int const score_needed_to_pass_a_Level = 5;

    Mix_Chunk *eat_Sound = NULL;
    Mix_Chunk *crash_Sound = NULL;

public:
    void Move();
    void reset();

    Direction DIRECTION = Freeze;
    vector <Pos_n_Dir> body;
    int score = 0;

    bool eatFood(SDL_Point fruit, bool &fruit_eaten, SDL_Point gift, bool &gift_eaten, Uint32 Gift_start_time); //get longer
    bool CRASH(vector<vector<int>> Map); //return 1 if happening accident
    bool levelup();
};

class entity : public snake
{
    SDL_Renderer *renderer;
    vector<SDL_Texture*> img_HEAD;
    SDL_Texture *img_BODY=NULL,
                *img_tail=NULL,
                *img_bend=NULL;

    int tmp_index=0;

    void rotate_body();

    void render_HEAD_0();
    void render_HEAD_1();
    void render_HEAD_2();
    void render_bendCELL(int i);
    void render_tail();
    void render_body(int i);
public:
    entity(SDL_Renderer *ren);
    ~entity();

    void draw();
    void render();

    void free();
int test = 69;
};
#endif // GAME_OBJECT_H
