#ifndef MENU_H
#define MENU_H
#include "SDL_utils.h"
#include "Texture.h"

class base_Menu
{
protected:
    enum Mouse {
    Right_Up,
    Left_Up,
    Right_Down,
    Left_Down,
    None
    };
    Mouse MOUSE=None;
    SDL_Point mouse;

};

class first_Menu: public base_Menu
{
    SDL_Texture *start_button=nullptr;
    SDL_Texture *quit_button=nullptr;
    SDL_Texture *guide_button=nullptr;

    SDL_Point start_size,start_coordinate;
    bool start_click_signal=0;

    SDL_Point quit_size, quit_coordinate;
    bool quit_click_signal=0;

    int OG_Y_button = 250; //optional original y coordinate for the first button


public:
//    bool running = false;
    void loop(SDL_Renderer *ren, bool &ingame);
    void input(bool &running);
    void handle_input(bool &running, bool &ingame);
    void draw(SDL_Renderer *ren);
    void render(SDL_Renderer *ren);
    void free();

    first_Menu();
//    ~first_Menu();
};

#endif // MENU_H
