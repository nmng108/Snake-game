#include "Map.h"
Map::Map(SDL_Renderer *ren)
{
    renderer = ren;
    this->create_Map();
    draw();
}
Map::~Map()
{
//    SDL_DestroyTexture(ground_Texture);
//    SDL_DestroyTexture(fruit_Texture);
//    SDL_DestroyTexture(wall_Texture);
    SDL_DestroyRenderer(renderer);
}
void Map::create_Map()
{
    base_Array.resize(array_ROW);
    for(int i=0;i<array_ROW;i++) base_Array[i].resize(array_COL);

    ifstream fileInput("Resourse/Map/map1.txt");
    if(fileInput.fail()) exit(-1);

    for(int i=0; i<array_ROW;i++)
        for(int j=0;j<array_COL && !fileInput.eof();j++)  fileInput>>base_Array[i][j];

}

void Map::getFruit(entity SNAKE) //có thể thêm tham số rắn
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
    stringstream save_score;
    save_score<<"Score: "<<score;
    string tmp;
    getline(save_score, tmp);
    save_score.clear();

//    string tmp = "Score: " + to_string(score);

    SDL_Color TEXT_color = {0, 204, 204, 255};
    renderText(tmp, TEXT_color, renderer, 0, 620);
}

void Map::draw()
{
//    ground_Texture=loadTexture("Resourse/Image/grass.png", renderer);
    wall_Texture=loadTexture("Resourse/Image/block.jpg", renderer);
    fruit_Texture=loadTexture("Resourse/Image/snake2/apple-removebg.png", renderer);
}

void Map::render()
{
//    renderTexture(MAP->ground_Texture, renderer, 0, 0, WIDTH_SCREEN, HEIGHT_SCREEN-100);
    for(long unsigned int i=0;i<base_Array.size();i++){
        for(long unsigned int j=0;j<base_Array[0].size();j++) {
            if(base_Array[i][j]==Wall) renderTexture(wall_Texture, renderer, j*CELL_side, i*CELL_side, CELL_side, CELL_side);
            if(base_Array[i][j]==Fruit) renderTexture(fruit_Texture, renderer, j*CELL_side, i*CELL_side, CELL_side, CELL_side);
        }
    }
}
