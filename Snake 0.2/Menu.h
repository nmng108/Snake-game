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
//        SDL_Texture *highScore_IMG=nullptr;

        Button *start_button = nullptr;
        Button *quit_button = nullptr;
        Button *highScore_button = nullptr;

        int button_OG_y_crd = 270; //optional original y coordinate for the highest button
        vector<int> arr_score;
        bool running_Menu = true;

        void draw();
    public:
        void open(bool &run_Menu, bool &running, bool &ingame);
        void input(bool &running);
        void handle_input(bool &running, bool &ingame);
        void render();

        void process_score_log(const int &new_score);
        void display_high_score_board(bool &run_Menu, bool &running);
        bool open_high_score_board=0;

        first_Menu(SDL_Renderer *ren);
        ~first_Menu();
};

//class second_Menu: public base_Menu
//{
//        SDL_Texture *backgr_IMG=nullptr;
//        Button *resume_button=nullptr;
//        Button *replay_button=nullptr;
//        Button *quit_button=nullptr;
////        SDL_Texture *guide_button=nullptr;
//
//        int button_OG_y_crd = 250; //optional original y coordinate for the first button
//
//    public:
//        void loop(bool &ingame);
//        void input(bool &running);
//        void handle_input(bool &running, bool &ingame);
//        void draw();
//        void render();
//        void free();
//};

#endif // MENU_H
