#include "Texture.h"

SDL_Texture *loadTexture(string const &file, SDL_Renderer *ren)
{
    SDL_Texture *tex = NULL;
    SDL_Surface *sur_tmp = IMG_Load(file.c_str());
    if(sur_tmp==nullptr) cout<<"IMG_Load Error! Cannot load: "<<file<<endl;
    else {
        tex = SDL_CreateTextureFromSurface(ren, sur_tmp);
        SDL_FreeSurface(sur_tmp);
        if(tex==nullptr) cout<<"CreateTextureFromSurface Error! Cannot load: "<<file<<endl;
    }

    return tex;
}

SDL_Texture *loadTexture_text(string const &msg, SDL_Color color, const string &ttf_file, int text_size, SDL_Renderer *ren)
{
    TTF_Font *font = TTF_OpenFont(ttf_file.c_str(), text_size);
    SDL_Surface *suf= TTF_RenderText_Solid(font, msg.c_str(), color);
    SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, suf);
    TTF_CloseFont(font);
    SDL_FreeSurface(suf);
    return tex;
}
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h)
{
	SDL_Rect dest;
	dest.x = x;
	dest.y = y;
    dest.w = w;
    dest.h = h;

	SDL_RenderCopy(ren, tex, NULL, &dest);
}

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y)
{
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);

	SDL_RenderCopy(ren, tex, NULL, &dst);
}

void renderText(const string &msg, SDL_Color color, const string &ttf_file, int text_size, SDL_Renderer *ren, int x, int y)
{
    TTF_Font *font = TTF_OpenFont(ttf_file.c_str(), text_size);
    SDL_Surface *suf= TTF_RenderText_Solid(font, msg.c_str(), color);
    SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, suf);
    TTF_CloseFont(font);
    SDL_Rect rect;
    rect.h = suf->h;
    rect.w = suf->w;
    rect.x = x;
    rect.y = y;
    SDL_FreeSurface(suf);
    SDL_RenderCopy(ren, tex, NULL, &rect);
    SDL_DestroyTexture(tex);
}

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h, int angle)
{
	SDL_Rect dest;
	dest.x = x;
	dest.y = y;
    dest.w = w;
    dest.h = h;

	SDL_RenderCopyEx(ren, tex, NULL, &dest, angle, nullptr, SDL_FLIP_NONE);
}

void renderTexture(const string &file, SDL_Renderer *ren, int x, int y)
{
    SDL_Texture *tex=loadTexture(file, ren);
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);

	SDL_RenderCopy(ren, tex, NULL, &dst);
	SDL_DestroyTexture(tex);
}

//void render_a_part_of_Texture(SDL_Texture *tex, SDL_Renderer *ren, int src_x, int src_y, SDL_Rect dst)
//{
//
//	SDL_Rect src;
//	src.x = src_x;
//	src.y = src_y;
//	SDL_QueryTexture(tex, NULL, NULL, &src.w, &src.h);
//
//	SDL_RenderCopy(ren, tex, &src, &dst);
//}
