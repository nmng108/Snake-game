#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H
#include "SDL_utils.h"
#include "Texture.h"
using namespace std;

class snake { //go straight, divert
public:
    SDL_Point HEAD = {9*CELL_side, 6*CELL_side};
    vector <SDL_Point> body;
    void Move(int WIDTH, int HEIGHT);
    bool eatFruit(SDL_Point fruit); //get longer
    Direction DIRECTION = Freeze;
    int score=0;
    bool CRASH(vector<vector<int>> Map); //return 1 if happening accident
protected:
    Direction old_DIRECTION=Freeze;
    int body_snake=1;
    int const velocity=CELL_side;
    SDL_Point old_CELL, bend_CELL;
//    stringstream score, notice;
};

class entity : public snake
{
    vector<SDL_Texture*> img_HEAD;
    SDL_Texture *img_BODY=nullptr,
                *img_tail=nullptr,
                *img_bendCELL=nullptr;

    int tmp_index=0;
    enum state
    {
    horizontal=0,
    vertical=90
    };

public:
    entity();
    ~entity() {
        for(int i=0;i<3;i++) SDL_DestroyTexture(img_HEAD[i]);
        SDL_DestroyTexture (img_bendCELL);
        SDL_DestroyTexture (img_BODY);
        SDL_DestroyTexture (img_tail);
    }
    void draw(SDL_Renderer *ren) {
        while(img_HEAD.size()!=3) {
            img_HEAD.push_back(loadTexture("Resourse/Image/Snake1/head.png", ren));
            img_HEAD.push_back(loadTexture("Resourse/Image/Snake1/head2.png", ren));
            img_HEAD.push_back(loadTexture("Resourse/Image/Snake1/head3.png", ren));
        }
        if(img_bendCELL==nullptr||img_BODY==nullptr||img_tail==nullptr) {
            img_BODY = loadTexture("Resourse/Image/Snake1/body.png", ren);
            img_bendCELL = loadTexture("Resourse/Image/Snake1/changeDirection1.png", ren);
            img_tail = loadTexture("Resourse/Image/Snake1/tail.png", ren);
        }
    }
    void render(SDL_Renderer *ren);
};
#endif // GAME_OBJECT_H
