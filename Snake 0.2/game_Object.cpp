#include "game_Object.h"

                        /**  class snake  */
bool snake::eatFruit(SDL_Point fruit) //runs before move() and both run before updating base_Map
{
    if(DIRECTION==Freeze) return false;

    if(body[0].x==fruit.x && body[0].y==fruit.y) {
        body.resize(body.size()+1);
        score++;

        Mix_PlayChannel(-1, eat_Sound, 0);

        return true;
    }
    return false;
}
void snake::Move()
{
    POS_n_DIR prev_pos={body[0].x, body[0].y};

    if(DIRECTION==Left && old_DIRECTION==Freeze) DIRECTION=Freeze;

    if(DIRECTION==Freeze) return;

    while(true) {
        if(DIRECTION==Up && old_DIRECTION!=Down) {
            body[0].angle=180;
            body[0].y = ( body[0].y - velocity + array_ROW ) % array_ROW;

            if(old_DIRECTION==Right) {
                prev_pos.direction = DIRECTION;
                prev_pos.turning = true;
                prev_pos.angle = 90;
            }
            else if(old_DIRECTION==Left) {
                prev_pos.direction = DIRECTION;
                prev_pos.turning = true;
                prev_pos.angle = 180;
            }
            else {
                prev_pos.direction = DIRECTION;
                prev_pos.turning = false;
            }
            break;
        }
        else if(DIRECTION==Down && old_DIRECTION!=Up) {
            body[0].angle=0;
            body[0].y = (body[0].y + velocity)%(array_ROW);

            if(old_DIRECTION == Left) {
                prev_pos.direction = DIRECTION;
                prev_pos.turning = true;
                prev_pos.angle = 270;
            }
            else if(old_DIRECTION == Right) {
                prev_pos.direction = DIRECTION;
                prev_pos.turning = true;
                prev_pos.angle = 0;
            }
            else {
                prev_pos.direction = DIRECTION;
                prev_pos.turning = false;
            }
            break;
        }
        else if(DIRECTION==Right && old_DIRECTION != Left) {
            body[0].angle= -90;
            body[0].x = (body[0].x + velocity) %array_COL;

            if(old_DIRECTION == Down) {
                prev_pos.direction = DIRECTION;
                prev_pos.turning = true;
                prev_pos.angle = 180;
            }
            else if(old_DIRECTION == Up) {
                prev_pos.direction = DIRECTION;
                prev_pos.turning = true;
                prev_pos.angle = 270;
            }
            else {
                prev_pos.direction = DIRECTION;
                prev_pos.turning = false;
            }
            break;
        }
        else if(DIRECTION==Left && old_DIRECTION!=Right) {
            body[0].angle= 90;
            body[0].x = (body[0].x - velocity + array_COL) % array_COL;

            if(old_DIRECTION == Down) {
                prev_pos.direction = DIRECTION;
                prev_pos.turning = true;
                prev_pos.angle = 90;
            }
            else if(old_DIRECTION == Up) {
                prev_pos.direction = DIRECTION;
                prev_pos.turning = true;
                prev_pos.angle = 0;
            }
            else {
                prev_pos.direction = DIRECTION;
                prev_pos.turning = false;
            }
            break;
        }
        else { DIRECTION = old_DIRECTION; }
    }

    for(int i=1;i<body.size();i++) {
        POS_n_DIR tmp_point = body[i];
        body [i] = prev_pos;
        prev_pos = tmp_point;
    }

    old_DIRECTION=DIRECTION;
}

bool snake::CRASH(vector<vector<int>> Map)
{
    if(Map[body[0].y][body[0].x] == Wall) {
        Mix_PlayChannel(-1, crash_Sound, 0);
        return 1;
    }

    for(int i=1;i<body.size();i++) {
        if(body[0].x==body[i].x && body[0].y==body[i].y) {
            Mix_PlayChannel(-1, crash_Sound, 0);
            return 1;
        }
    }
//    if(Map[body[0].y][body[0].x]==Wall || Map[body[0].y][body[0].x]==Snake) return 1;

    return 0;
}

void snake::reset()
{
    body.resize(2);
    score = 0;
    DIRECTION = Right;
    old_DIRECTION = Right;
    body[0] = {9, 6, Right, -90, false};
    body[1]={9-1, 6, Right, 90, false};
}

bool snake::levelup()
{
    if( body.size() == (2+score_needed_to_pass_a_Level) ) {
        int tmp_score=score;
        reset();
        score=tmp_score;
        DIRECTION = Freeze;
        return true;
    }
    return false;
}

                        /**  class entity  */
entity::entity(SDL_Renderer *ren)
{
    renderer = ren;
//    draw();
    reset();
    eat_Sound = load_SoundEffect("Resource/eat.wav", "eat");
    crash_Sound = load_SoundEffect("Resource/crash.wav", "Crash sound");
}

//entity::~entity()
//{
//}

void entity::free()
{
    Mix_FreeChunk(eat_Sound);
    Mix_FreeChunk(crash_Sound);
    eat_Sound = crash_Sound = NULL;
    SDL_DestroyRenderer(renderer);
}

//void entity::draw() {
//    while(img_HEAD.size()<3) {
//        img_HEAD.push_back(loadTexture("Resource/Image/Snake2/head2.png", renderer));
//        img_HEAD.push_back(loadTexture("Resource/Image/Snake2/head2z.png", renderer));
//        img_HEAD.push_back(loadTexture("Resource/Image/Snake2/head2zz.png", renderer));
//    }
//    img_BODY = loadTexture("Resource/Image/Snake2/body.png", renderer);
//    img_bend = loadTexture("Resource/Image/Snake2/change_direction.png", renderer);
//    img_tail = loadTexture("Resource/Image/Snake2/tail.png", renderer);
//}

void entity::rotate_body()
{
    for(int i=1;i<body.size()-1 && body[i].turning != true;i++) { //for all
        if(body[i].direction==Right) body[i].angle=90;
        if(body[i].direction==Left) body[i].angle=270;
        if(body[i].direction==Up) body[i].angle=0;
        if(body[i].direction==Down) body[i].angle=180;

    }
//tail:
//    if(body[body.size()-1].turning == true) {
        switch (body[body.size()-1].direction)
        {
            case Down: body[body.size()-1].angle = 180; break;
            case Up: body[body.size()-1].angle = 0; break;
            case Left: body[body.size()-1].angle = 270; break;
            case Right: body[body.size()-1].angle = 90; break;
        }
//    }
//    else {
//        switch (body[body.size()-1].direction)
//        {
//            case Down: body[body.size()-1].angle = 180; break;
//            case Up: body[body.size()-1].angle = 0; break;
//            case Left: body[body.size()-1].angle = 270; break;
//            case Right: body[body.size()-1].angle = 90; break;
//        }
//    }
}

void entity::render()
{
    rotate_body();

    tmp_index = (tmp_index+1)%3;
    switch(tmp_index)
    {
        case 0: render_HEAD_0(); break;
        case 1: render_HEAD_1(); break;
        case 2: render_HEAD_2(); break;
    }

    for(int i=1;i<body.size();i++) {

        if(i==body.size()-1) render_tail();

        else if(body[i].turning==true) render_bendCELL(i);

        else render_body(i);
    }
}

void entity::render_body(int i)
{
    renderTexture("Resource/Image/Snake2/body.png", renderer, body[i].x*CELL_side, body[i].y*CELL_side, CELL_side, CELL_side, body[i].angle);
}
void entity::render_bendCELL(int i)
{
    renderTexture("Resource/Image/Snake2/change_direction.png", renderer, body[i].x*CELL_side, body[i].y*CELL_side, CELL_side, CELL_side, body[i].angle);
}
void entity::render_tail()
{
    renderTexture("Resource/Image/Snake2/tail.png", renderer, body[body.size()-1].x*CELL_side, body[body.size()-1].y*CELL_side, CELL_side, CELL_side, body[body.size()-1].angle);
}
void entity::render_HEAD_0()
{
    renderTexture("Resource/Image/Snake2/head2.png", renderer, body[0].x*CELL_side, body[0].y*CELL_side, CELL_side, CELL_side,body[0].angle);
}
void entity::render_HEAD_1()
{
    renderTexture("Resource/Image/Snake2/head2z.png", renderer, body[0].x*CELL_side, body[0].y*CELL_side, CELL_side, CELL_side,body[0].angle);
}
void entity::render_HEAD_2()
{
    renderTexture("Resource/Image/Snake2/head2zz.png", renderer, body[0].x*CELL_side, body[0].y*CELL_side, CELL_side, CELL_side,body[0].angle);
}
