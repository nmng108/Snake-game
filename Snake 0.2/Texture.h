#ifndef TEXTURE_H
#define TEXTURE_H
#include "SDL_utils.h"
using namespace std;

SDL_Texture *loadTexture(string const &file, SDL_Renderer *ren);
void renderText(const string &msg, SDL_Color color, SDL_Renderer *ren, int x, int y);
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h);
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y);
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h, int angle);
const SDL_Color Score_color={126,48,91,255};

void render_a_part_of_Texture(SDL_Texture *tex, SDL_Renderer *ren, int src_x, int src_y, SDL_Rect dst);

#endif // TEXTURE_H
