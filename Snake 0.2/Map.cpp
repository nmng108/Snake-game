#include "Map.h"
Map::Map(SDL_Renderer *ren)
{
    renderer = ren;

    list_of_Maps.resize(number_of_maps);
    for(int i=0;i<number_of_maps;i++) {
        string tmp="Resource/Map/map" + to_string(i) + ".txt";
        list_of_Maps[i] = tmp;
    }
    this->create_Map(0);

    draw();
}
Map::~Map()
{
}
void Map::create_Map(int mapList_index)
{
    base_Array.resize(array_ROW);
    for(int i=0;i<array_ROW;i++) base_Array[i].resize(array_COL);

    ifstream InputFile(list_of_Maps[mapList_index]);
    if(InputFile.fail()) exit(-1);

    for(int i=0; i<array_ROW;i++)
        for(int j=0;j<array_COL && !InputFile.eof();j++)  InputFile>>base_Array[i][j];
    InputFile.close();
}

void Map::getFruit(entity SNAKE)
{
    srand(time(0));

//    SDL_Point tmp={fruit.x, fruit.y};

    base_Array[fruit.y][fruit.x]=Blank;
    bool sign=0;
    do {
        fruit.x=rand()%array_COL;
        fruit.y=rand()%array_ROW;

        for(int i=0;i<SNAKE.body.size();i++) {
            if(fruit.x==SNAKE.body[i].x && fruit.y==SNAKE.body[i].y) {
                sign = 1;
                break;
            }
            else sign = 0;
        }
    }
    while(base_Array[fruit.y][fruit.x] != Blank || sign == 1);

//    base_Array[tmp.y][tmp.x] = Blank;
//    base_Array[fruit.y][fruit.x] = Fruit;
}

void Map::display_score(int score)
{
    string tmp = "Score: " + to_string(score);

    SDL_Color Score_color={126,145,91,255};
    string font="Resource/Fonts/amatic/amatic-bold.ttf";
    renderText(tmp, Score_color, font, 60, renderer, 10, 620);
}

void Map::draw()
{
    wall_Texture=loadTexture("Resource/Image/block.jpg", renderer);
    fruit_Texture=loadTexture("Resource/Image/snake2/apple-removebg.png", renderer);
}

void Map::render()
{
    for(long unsigned int i=0;i<base_Array.size();i++){
        for(long unsigned int j=0;j<base_Array[0].size();j++) {
            if(base_Array[i][j]==Wall) renderTexture(wall_Texture, renderer, j*CELL_side, i*CELL_side, CELL_side, CELL_side);
            if(base_Array[i][j]==Fruit) renderTexture(fruit_Texture, renderer, j*CELL_side, i*CELL_side, CELL_side, CELL_side);
        }
    }
    SDL_SetRenderDrawColor(renderer, 0, 48, 200, 255);
    SDL_RenderDrawLine(renderer, 0, 600, 900, 600);
}

void Map::free()
{
    SDL_DestroyRenderer(renderer);
//    list_of_Maps.clear();
    SDL_DestroyTexture(fruit_Texture);
    SDL_DestroyTexture(wall_Texture);
    fruit_Texture = wall_Texture = NULL;
}
