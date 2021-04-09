#include "Map.h"
Map::~Map()
{
    SDL_DestroyTexture(ground_Texture);
    SDL_DestroyTexture(fruit_Texture);
    SDL_DestroyTexture(wall_Texture);
}
void Map::create_Map()
{
    base_Array.resize(array_ROW);
    for(int i=0;i<array_ROW;i++) base_Array[i].resize(array_COL);

    base_Array[0].resize(array_COL+1);

    ifstream fileInput("Resourse/Map/map1.txt");
    if(fileInput.fail()) exit(-1);

    for(int i=0; i<array_ROW;i++)
        for(int j=0;j<array_COL && !fileInput.eof();j++)  fileInput>>base_Array[i][j];
}

void Map::getFruit() //có thể thêm tham số rắn
{
    srand(time(0));
    for(int i=0;i<base_Array.size();i++)
        for(int j=0;j<base_Array[0].size();j++)
            if(base_Array[i][j]==Fruit) base_Array[i][j]=Blank;
    /**thêm xét đkiện trùng với rắn*/
    do {
        fruit.x=rand()%array_COL;
        fruit.y=rand()%array_ROW;
    }
    while(base_Array[fruit.y][fruit.x]!=Blank); //thiếu điều kiện của rắn

    base_Array[fruit.y][fruit.x] = Fruit;
}

void Map::display_score(int score, SDL_Renderer *ren)
{
    stringstream save_score;
    save_score<<"Score: "<<score;
    string tmp;
    getline(save_score, tmp);

    SDL_Color TEXT_color = {0, 204, 204, 255};
    renderText(tmp, TEXT_color, ren, 0, 620);
}
