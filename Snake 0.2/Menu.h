#ifndef MENU_H
#define MENU_H
#include "SDL_utils.h"
#include "Texture.h"
#include "Button.h"


class base_Menu
{
protected:
    Mouse MOUSE=None;
    SDL_Point mouse;
    SDL_Event event;
    SDL_Renderer *renderer;

};

class first_Menu: public base_Menu
{
        SDL_Texture *backgr_IMG=nullptr;
        SDL_Texture *guide_button=nullptr;

        Button *start_button = nullptr;
        Button *quit_button = nullptr;
        Button *highScore_button = nullptr;

        int button_OG_y_crd = 270; //optional original y coordinate for the highest button

        bool running_Menu = true;

        void draw();
    public:
        void loop(bool &run_Menu, bool &running, bool &ingame);
        void input(bool &running);
        void handle_input(bool &running, bool &ingame);
        void render();

    first_Menu(SDL_Renderer *ren);
    ~first_Menu();
};

//class second_Menu: public base_Menu
//{
//        SDL_Texture *start_button=nullptr;
//        SDL_Texture *quit_button=nullptr;
//        SDL_Texture *guide_button=nullptr;
//        SDL_Point start_size,start_coordinate;
//        bool start_click_signal=0;
//
//        SDL_Point quit_size, quit_coordinate;
//        bool quit_click_signal=0;
//
//        int OG_Y_button = 250; //optional original y coordinate for the first button
//
//
//    public:
////        bool running = false;
//        void loop(bool &ingame);
//        void input(bool &running);
//        void handle_input(bool &running, bool &ingame);
//        void draw();
//        void render();
//        void free();
//};

#endif // MENU_H
