#include "game_Object.h"
                        /**  class snake  */
bool snake::eatFruit(SDL_Point fruit)
{
    fruit.x*=CELL_side;
    fruit.y*=CELL_side;

    if(DIRECTION==Freeze) return false;

    else if(((HEAD.x+CELL_side)>fruit.x && HEAD.x<=fruit.x && HEAD.y==fruit.y)|| //right
       (HEAD.x<(fruit.x+CELL_side) && HEAD.x>=fruit.x && HEAD.y==fruit.y && DIRECTION==Left)|| //left
       ((HEAD.y+CELL_side)>fruit.y && HEAD.y<=fruit.y && HEAD.x==fruit.x && DIRECTION==Down)|| //down
       (HEAD.y<(fruit.y+CELL_side) && HEAD.y>=fruit.y && HEAD.x==fruit.x && DIRECTION==Up)  ) {//up

        body_snake++;
        body.resize(body_snake);
        return true;
    }
    return false;
}
void snake::Move(int WIDTH, int HEIGHT)
{
    SDL_Point old_pos=HEAD;
    bool change=1;

    if(DIRECTION==Left && old_DIRECTION==Freeze) DIRECTION=Freeze;

    if(DIRECTION==Freeze) return;

    body[0] = {HEAD.x-CELL_side, HEAD.y};
    while(true) {
        if(DIRECTION==Up && old_DIRECTION!=Down) {
            bend_CELL.y = HEAD.y;
            HEAD.y = ( HEAD.y - velocity +(HEIGHT-100) )%(HEIGHT-100);

            if(old_DIRECTION==Right) {
//                int present_CELL_x=int(HEAD.x/CELL_side);
                int present_pos_x = int(HEAD.x/CELL_side) * CELL_side;

                if(CELL_side*0.2 >= (HEAD.x%CELL_side) ) bend_CELL.x = HEAD.x = present_pos_x;
                else bend_CELL.x = HEAD.x = present_pos_x + CELL_side;
            }
            if(old_DIRECTION==Left) {
                int present_CELL_x, present_pos_x;
                if( HEAD.x%CELL_side==0 ) {
//                    present_CELL_x = int(HEAD.x/CELL_side);
                    present_pos_x = int(HEAD.x/CELL_side)*CELL_side;
                }
                else {
//                    present_CELL_x = HEAD.x/CELL_side + 1;
                    present_pos_x = int(HEAD.x/CELL_side+1)*CELL_side;
                }

                if( HEAD.x >= present_pos_x - 0.2*CELL_side ) bend_CELL.x = HEAD.x = present_pos_x;
                else bend_CELL.x = HEAD.x = present_pos_x - CELL_side;
            }
            break;
        }
        else if(DIRECTION==Down && old_DIRECTION!=Up) {
            bend_CELL.y = HEAD.y;
            HEAD.y = (HEAD.y + velocity)%(HEIGHT-100);

            if(old_DIRECTION == Left) {
                int present_CELL_x, present_pos_x;
                if( HEAD.x%CELL_side==0 ) {
//                    present_CELL_x = HEAD.x/CELL_side;
                    present_pos_x = int(HEAD.x/CELL_side)*CELL_side;
                }
                else {
//                    present_CELL_x = HEAD.x/CELL_side + 1;
                    present_pos_x = int(HEAD.x/CELL_side+1)*CELL_side;
                }

                if( HEAD.x >= present_pos_x - 0.2*CELL_side ) bend_CELL.x = HEAD.x = present_pos_x;
                else bend_CELL.x = HEAD.x = present_pos_x - CELL_side;
            }
            if(old_DIRECTION == Right) {
//                int present_CELL_x=HEAD.x/CELL_side;
                int present_pos_x = int(HEAD.x/CELL_side) * CELL_side;

                if(CELL_side*0.2 >= (HEAD.x%CELL_side) ) bend_CELL.x = HEAD.x = present_pos_x;
                else bend_CELL.x = HEAD.x = present_pos_x + CELL_side;
            }
            break;
        }
        else if(DIRECTION==Right && old_DIRECTION!=Left) {
            HEAD.x = (HEAD.x + velocity)%WIDTH;

            if(old_DIRECTION == Down) {
//                int present_CELL_y = HEAD.y/CELL_side;
                int present_pos_y = int(HEAD.y/CELL_side) * CELL_side;

                if(CELL_side*0.2 >= (HEAD.y%CELL_side) ) bend_CELL.y = HEAD.y = present_pos_y;
                else bend_CELL.y = HEAD.y = present_pos_y + CELL_side;
            }
            if(old_DIRECTION == Up) {
                int present_CELL_y, present_pos_y;
                if( HEAD.y%CELL_side==0 ) {
//                    present_CELL_y = HEAD.y/CELL_side;
                    present_pos_y = int(HEAD.y/CELL_side)*CELL_side;
                }
                else {
//                    present_CELL_y = HEAD.y/CELL_side + 1;
                    present_pos_y = int(HEAD.y/CELL_side+1)*CELL_side;
                }

                if( HEAD.y >= present_pos_y - 0.2*CELL_side ) bend_CELL.y = HEAD.y = present_pos_y;
                else bend_CELL.y = HEAD.y = present_pos_y - CELL_side;
            }
            break;
        }
        else if(DIRECTION==Left && old_DIRECTION!=Right) {
            HEAD.x = (HEAD.x - velocity + WIDTH) % WIDTH;

            if(old_DIRECTION == Down) {
//                int present_CELL_y = HEAD.y/CELL_side;
                int present_pos_y = int(HEAD.y/CELL_side) * CELL_side;

                if(CELL_side*0.2 >= (HEAD.y%CELL_side) ) bend_CELL.y = HEAD.y = present_pos_y;
                else bend_CELL.y = HEAD.y = present_pos_y + CELL_side;
            }
            if(old_DIRECTION == Up) {
                int present_CELL_y, present_pos_y;
                if( HEAD.y%CELL_side==0 ) {
//                    present_CELL_y = HEAD.y/CELL_side;
                    present_pos_y = int(HEAD.y/CELL_side)*CELL_side;
                }
                else {
//                    present_CELL_y = HEAD.y/CELL_side + 1;
                    present_pos_y = int(HEAD.y/CELL_side+1)*CELL_side;
                }

                if( HEAD.y >= present_pos_y - 0.2*CELL_side ) bend_CELL.y = HEAD.y = present_pos_y;
                else bend_CELL.y = HEAD.y = present_pos_y - CELL_side;
            }
            break;
        }
        else if(DIRECTION==Freeze) {break;}
        else {DIRECTION = old_DIRECTION; change = false;}
    }

    if(!change) bend_CELL={12,0};

    if(DIRECTION!=Freeze) {
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

        for(int i=0;i<body.size();i++) {
            SDL_Point tmp_point = body[i];
            body [i] = old_pos;
            old_pos = tmp_point;
        }
    }

    old_DIRECTION=DIRECTION; // đưa xuống hàm render để xử lí ảnh trước
}

bool snake::CRASH(vector<vector<int>> Map)
{
    if(HEAD.y%CELL_side!=0) {
        if(DIRECTION==Up) {
            if(Map[int(HEAD.y/CELL_side)][HEAD.x]==Wall) {DIRECTION =Freeze; return 1;}

//            vector<SDL_Point> BODYcoordinates_inMap;
            for(int i=0;i<body_snake;i++)
//                BODYcoordinates_inMap.push_back({int(body[i].y/CELL_side), int(body[i].x/CELL_side)});
                if(int(body[i].y/CELL_side)==int(HEAD.y/CELL_side) && abs(HEAD.x-body[i].x)<CELL_side) {DIRECTION =Freeze; return 1;}
        }
        if(DIRECTION==Down) {
            if(Map[int(HEAD.y/CELL_side)+1][HEAD.x]==Wall) {DIRECTION =Freeze; return 1;}

            for(int i=0;i<body_snake;i++)
                if(body[i].y<(HEAD.y+CELL_side) && int(body[i].x/CELL_side)==HEAD.x/CELL_side) {DIRECTION =Freeze; return 1;}
        }
    }
    if(HEAD.x%CELL_side != 0) {
        if(DIRECTION==Left) {
            if(Map[HEAD.y][int(HEAD.x/CELL_side)]==Wall) {DIRECTION =Freeze; return 1;}

            for(int i=0;i<body.size();i++)
                if( int(body[i].y/CELL_side)==HEAD.y/CELL_side && (body[i].x+CELL_side)<HEAD.x) {DIRECTION =Freeze; return 1;}
        }
        if(DIRECTION==Right) {
            if(Map[HEAD.y][int(HEAD.x/CELL_side)+1]==Wall) {DIRECTION =Freeze; return 1;}

            for(int i=0;i<body.size();i++)
                if( abs(body[i].y-HEAD.y)<CELL_side && body[i].x<(HEAD.x+CELL_side) ) {DIRECTION =Freeze; return 1;}
        }
    }
    return 0;
}

                        /**  class entity  */
void entity::render(SDL_Renderer *ren)
{
    renderTexture(img_HEAD[(tmp_index++)%3], ren, HEAD.x, HEAD.y, CELL_side, CELL_side);

    for(int i=0;i<body.size();i++) {
        if(i==body.size()-1) renderTexture(img_tail, ren, body[i].x, body[i].y, CELL_side, CELL_side);

        else if(body[i].x==bend_CELL.x && body[i].y==bend_CELL.y) renderTexture(img_bendCELL, ren, body[i].x, body[i].y, CELL_side, CELL_side);

        else renderTexture(img_BODY, ren, body[i].x, body[i].y, CELL_side, CELL_side);
    }
}
entity::entity()
{
    body.resize(1);
    body[0]={9*CELL_side-1, 6*CELL_side};
}
