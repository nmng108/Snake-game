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
        Button *rankReset_button = nullptr;
        Button *back_button = nullptr;

        int button_OG_y_crd = 270; //optional original y coordinate for the highest button
        vector<int> arr_score;
        bool running_1stMenu = true;

        void draw();
    public:
        first_Menu(SDL_Renderer *ren);
        ~first_Menu();

        void open(bool &run_Menu, bool &running, bool &start);
        void input(bool &running);
        void handle_input(bool &running, bool &start);
        void render();

        void process_score_log(const int &new_score, int &rank_sort);
        void display_high_score_board(bool &run_Menu, bool &running);
        bool open_high_score_board=0;
        const int number_of_score_elements = 5;
};

class second_Menu: public base_Menu
{
        SDL_Renderer *renderer;
        SDL_Texture *backgr_IMG=nullptr;

        Button *resume_button=nullptr;
        Button *replay_button=nullptr;
        Button *menu_button=nullptr;

        int button_OG_y_crd = 275; //optional original y coordinate for the first button

        bool running_2ndMenu = 1;

        void draw();
    public:
        second_Menu(SDL_Renderer *ren);
        ~second_Menu();
        void open(bool &running, bool &start, bool &ingame);
        void input(bool &running, bool &start, bool &ingame);
        void handle_input(bool &ingame);
        void render();
};

#endif // MENU_H
