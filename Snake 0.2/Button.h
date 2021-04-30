#ifndef BUTTON_H
#define BUTTON_H

#include "SDL_utils.h"
#include "Texture.h"

enum Mouse {
    Right_Up,
    Left_Up,
    Right_Down,
    Left_Down,
    None
};

class Button
{
    private:
        SDL_Renderer *renderer;
        vector<SDL_Texture*> button_IMG;
    public:
        Button(SDL_Renderer *ren);
        ~Button();
        bool click_signal = 0,
             chosen = 0;
        void draw(string const &filepath_keyword, int crd_y);
        void render();
        void handle_input(Mouse MOUSE, SDL_Point mouse);
        SDL_Point coordinate, Size;
};


#endif // BUTTON_H
