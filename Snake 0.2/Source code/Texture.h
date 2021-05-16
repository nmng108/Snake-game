#ifndef TEXTURE_H
#define TEXTURE_H
#include "SDL_utils.h"
using namespace std;

SDL_Texture *loadTexture(string const &file, SDL_Renderer *ren);
SDL_Texture *loadTexture_text(string const &msg, SDL_Color color, const string &ttf_file, int text_size, SDL_Renderer *ren);
void renderText(const string &msg, SDL_Color color, const string &ttf_file, int text_size, SDL_Renderer *ren, int x, int y);
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h);
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y);
void renderTexture(const string &file, SDL_Renderer *ren, int x, int y);
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h, int angle);
void renderTexture(const string &file, SDL_Renderer *ren, int x, int y, int w, int h, int angle);

#endif // TEXTURE_H
