#ifndef SDL_UTILS_H
#define SDL_UTILS_H

#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <ctime>
#include <fstream>
#include <sstream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#define WIDTH_SCREEN 900
#define HEIGHT_SCREEN 700

using namespace std;

const int CELL_side=50;
    const int array_COL = WIDTH_SCREEN/CELL_side;
    const int array_ROW =(HEIGHT_SCREEN-100)/CELL_side;

enum Direction
{
    Freeze,
    Up,
    Down,
    Left,
    Right,
    Turn
};
enum object
{
    Blank=0,
    Snake=1,
    SnakeHEAD=2,
    Fruit=3,
    Wall=4,
    Gift=5
};

void logSDLError(std::ostream& os,
                 const std::string &msg, bool fatal = false);

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer,
	int screenWidth, int screenHeight, const char* windowTitle) ;

void quitSDL(SDL_Window* window, SDL_Renderer* renderer);

void waitUntilKeyPressed();

Mix_Chunk *load_SoundEffect(const string &file, const string &error_sound_type);
Mix_Music *loadMusic(const string &file, const string &error_sound_type);

#endif // SDL_UTILS_H
