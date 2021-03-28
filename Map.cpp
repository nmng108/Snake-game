#include "Map.h"
Map::~Map()
{
    SDL_DestroyTexture(ground_Texture);
    SDL_DestroyTexture(fruit_Texture);
    SDL_DestroyTexture(wall_Texture);
}
void Map::create_Map()
{
    base_Array.resize(row);
    for(int i=0;i<row;i++) base_Array[i].resize(col);

    ifstream fileInput("Resourse/Map/map1.txt");
    if(fileInput.fail()) exit(-1);

    for(int i=0; i<row;i++)
        for(int j=0;j<col && !fileInput.eof();j++)  fileInput>>base_Array[i][j];
}

void Map::getFruit() //có thể thêm tham số rắn
{
    srand(time(0));
    for(int i=0;i<base_Array.size();i++)
        for(int j=0;j<base_Array[0].size();j++)
            if(base_Array[i][j]==Fruit) base_Array[i][j]=Blank;
    /**thêm xét đkiện trùng với rắn*/
    do {
        fruit.x=rand()%col;
        fruit.y=rand()%row;
    }
    while(base_Array[fruit.y][fruit.x]!=Blank); //thiếu điều kiện của rắn

    base_Array[fruit.y][fruit.x] = Fruit;
}

