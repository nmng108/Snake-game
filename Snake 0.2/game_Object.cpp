#include "game_Object.h"
                        /**  class snake  */
bool snake::eatFruit(SDL_Point fruit)
{
    if(DIRECTION==Freeze) return false;

    if(body[0].x==fruit.x && body[0].y==fruit.y) {
        segments++;
        return true;
    }
    return false;
}
void snake::Move()
{
    POS_n_DIR prev_pos={body[0].x, body[0].y};
//    bool change=1;  //for locating where we put snake's turning segments

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

//    if(!change) bend_CELL={12,0}; //put in the cell which is out of the board

//        for(int i=0;i<body_snake;i++) {
//            SDL_Point tmp_point = body[i];
//
//            if((body[i].y<old_pos.y) && (body[i].x==old_pos.x)) body[i].y+=velocity; //down
//            if((body[i].y>old_pos.y) && (body[i].x==old_pos.x)) body[i].y-=velocity; //up
//            if((body[i].y==old_pos.y) && (body[i].x>old_pos.x)) body[i].x-=velocity; //left
//            if((body[i].y==old_pos.y) && (body[i].x<old_pos.x)) body[i].x+=velocity; //right
//
//            old_pos = tmp_point;
//        }

    body.resize(segments);


    for(int i=1;i<body.size();i++) {
        POS_n_DIR tmp_point = body[i];
        body [i] = prev_pos;
        prev_pos = tmp_point;
    }

    old_DIRECTION=DIRECTION;
}

bool snake::CRASH(vector<vector<int>> Map)
{
    if(Map[body[0].y][body[0].x] == Wall) return 1;

    for(int i=1;i<body.size();i++) {
        if(body[0].x==body[i].x && body[0].y==body[i].y) return 1;
    }
//    if(Map[body[0].y][body[0].x]==Wall || Map[body[0].y][body[0].x]==Snake) return 1;

    return 0;
}

                        /**  class entity  */
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

void entity::render(SDL_Renderer *ren)
{
    rotate_body();

    renderTexture(img_HEAD[(tmp_index++)%3], ren, body[0].x*CELL_side, body[0].y*CELL_side, CELL_side, CELL_side,body[0].angle );

    for(int i=1;i<body.size();i++) {

        if(i==body.size()-1) renderTexture(img_tail, ren, body[i].x*CELL_side, body[i].y*CELL_side, CELL_side, CELL_side, body[i].angle);

        else if(body[i].turning==true) renderTexture(img_bend , ren, body[i].x*CELL_side, body[i].y*CELL_side, CELL_side, CELL_side, body[i].angle);

        else renderTexture(img_BODY, ren, body[i].x*CELL_side, body[i].y*CELL_side, CELL_side, CELL_side, body[i].angle);
    }
}

void entity::reset()
{
    body.resize(2);
    body[0] = {9, 6, Right, -90, false};
    body[1] = {9-1, 6, Right, 90, false};
}


entity::entity()
{
    body.resize(2);
    body[0] = {9, 6, Right, -90, false};
    body[1]={9-1, 6, Right, 90, false};
}
