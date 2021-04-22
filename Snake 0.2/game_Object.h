#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H
#include "SDL_utils.h"
#include "Texture.h"
using namespace std;

class snake { //go straight, divert
protected:
    Direction old_DIRECTION=Freeze;
    int segments=2;
    int const velocity=1;

    struct POS_n_DIR
    {
        int x, y;
        Direction direction;
        int angle;
        bool turning;
    };
//    stringstream score, notice;
public:
    vector <POS_n_DIR> body;
    void Move();
    bool eatFruit(SDL_Point fruit); //get longer
    Direction DIRECTION = Freeze;
    int score = 0;
    bool CRASH(vector<vector<int>> Map); //return 1 if happening accident
};

class entity : public snake
{
    vector<SDL_Texture*> img_HEAD;
    SDL_Texture *img_BODY=nullptr,
                *img_tail=nullptr,
                *img_bend=nullptr;

    int tmp_index=0;

    void rotate_body();
public:
    entity();
    ~entity() {

    }

    void draw(SDL_Renderer *ren) {
        while(img_HEAD.size()!=3) {
            img_HEAD.push_back(loadTexture("Resourse/Image/Snake2/head2.png", ren));
            img_HEAD.push_back(loadTexture("Resourse/Image/Snake2/head2a.png", ren));
            img_HEAD.push_back(loadTexture("Resourse/Image/Snake2/head2aa.png", ren));
        }
        if(img_bend==nullptr||img_BODY==nullptr||img_tail==nullptr) {
            img_BODY = loadTexture("Resourse/Image/Snake2/body.png", ren);
            img_bend = loadTexture("Resourse/Image/Snake2/change_direction.png", ren);
            img_tail = loadTexture("Resourse/Image/Snake2/tail.png", ren);
        }
    }
    void render(SDL_Renderer *ren);

    void free() {
        for(int i=0;i<3;i++) SDL_DestroyTexture(img_HEAD[i]);
        SDL_DestroyTexture (img_bend);
        SDL_DestroyTexture (img_BODY);
        SDL_DestroyTexture (img_tail);
        img_BODY=nullptr,
        img_tail=nullptr,
        img_bend=nullptr;
    }
};
#endif // GAME_OBJECT_H
