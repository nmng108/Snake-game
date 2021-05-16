#include "Map.h"
Map::Map(SDL_Renderer *ren)
{
    renderer = ren;

    GIFT = new Food(ren, "Resource/Image/Diamond.png", Gift);
    FRUIT = new Food(ren, "Resource/Image/apple-removebg.png", Fruit);

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
//    list_of_Maps.clear();
    SDL_DestroyTexture(wall_Texture);
    wall_Texture = NULL;
    SDL_DestroyRenderer(renderer);
    delete GIFT;
    delete FRUIT;
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

void Map::getFood(vector<Pos_n_Dir> Snake_Body)
{
    srand(time(0));

    if((Snake_Body.size() == 2) || FRUIT->eaten) {
        FRUIT->eaten = false;
        FRUIT->appear(base_Array, Snake_Body);
        condition_to_take_bonus_score++;
    }

    if(GIFT->eaten) {
        GIFT->eaten = false;
        GIFT->position = {18, 0};
    }
    if(condition_to_take_bonus_score==4) {
        GIFT->appear(base_Array, Snake_Body);
        condition_to_take_bonus_score = 0;
    }
}

void Map::display_score(int score)
{
    SDL_Color Score_color={126,145,91,255};
    string font="Resource/Fonts/amatic/amatic-bold.ttf";
    renderText("Score: " + to_string(score), Score_color, font, 65, renderer, 10, 611);
}

void Map::draw()
{
    wall_Texture=loadTexture("Resource/Image/block.jpg", renderer);
    key_icon = loadTexture("Resource/Image/key icon1.png", renderer);
}

void Map::render()
{
    for(long unsigned int i=0;i<base_Array.size();i++){
        for(long unsigned int j=0;j<base_Array[0].size();j++) {
            if(base_Array[i][j]==Wall) renderTexture(wall_Texture, renderer, j*CELL_side, i*CELL_side, CELL_side, CELL_side);
        }
    }

    GIFT->render();
    FRUIT->render();

    SDL_SetRenderDrawColor(renderer, 0, 48, 200, 255);
    SDL_RenderDrawLine(renderer, 0, 600, 900, 600);

    renderTexture(key_icon, renderer, 0, 600);
}

void Map::reset(int level, vector<Pos_n_Dir> Snake_Body)
{
    create_Map(level);
    getFood(Snake_Body);
    condition_to_take_bonus_score = 0;
}

            /**  Food  **/
Food::Food(SDL_Renderer *ren, const string &IMG_file, object obj_type)
{
    renderer = ren;
    image = loadTexture(IMG_file, renderer);
    obj = obj_type;
}
Food::~Food()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyTexture(image);
    image = NULL;
}

void Food::render()
{
    renderTexture(image, renderer, position.x*CELL_side, position.y*CELL_side, CELL_side, CELL_side);
}

void Food::appear(vector<vector<int>> &base_Array, vector<Pos_n_Dir> Snake_Body)
{
    base_Array[position.y][position.x]=Blank;
    bool sign=0;
    do {
        position.x=rand()%array_COL;
        position.y=rand()%array_ROW;

        for(int i=0;i<Snake_Body.size();i++) {
            if(position.x==Snake_Body[i].x && position.y==Snake_Body[i].y) {
                sign = 1;
                break;
            }
            else sign = 0;
        }
    }
    while(base_Array[position.y][position.x] != Blank || sign == 1);

    base_Array[position.y][position.x] = obj;

    start_time = SDL_GetTicks();
}

bool Food::exist()
{
    if((SDL_GetTicks()-start_time) >= existence_time || eaten) {
        return false;
    }
    return true;
}
