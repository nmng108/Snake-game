#include "Menu.h"

 /** first Menu **/
first_Menu::first_Menu(SDL_Renderer *ren)
{
    renderer = ren;
    start_button = new Button(ren);
    quit_button = new Button(ren);
    draw();
}

first_Menu::~first_Menu()
{
//    SDL_DestroyTexture(start_button);
//    SDL_DestroyTexture(quit_button);
//    SDL_DestroyTexture(guide_button);
    SDL_DestroyRenderer(renderer);
    delete start_button, quit_button;
}

void first_Menu::loop(bool &run_Menu, bool &running, bool &ingame)
{
    running_Menu = run_Menu;

    while(running_Menu) {
        render();
        input(running);
        handle_input(running, ingame);
    }
}

void first_Menu::input(bool &running)
{
    SDL_GetMouseState(&mouse.x, &mouse.y);

    while(SDL_PollEvent(&event)) {
        if(event.type == SDL_QUIT) {
            running_Menu = 0;
            running = false;
            break;
        }
        if(event.key.keysym.sym == SDLK_ESCAPE) {
            running_Menu = 0;
            running = false;
            break;
        }
        if(event.type == SDL_MOUSEBUTTONDOWN) {
            if (event.button.button == SDL_BUTTON_LEFT) {
                MOUSE = Left_Down;
            }
        }
        if(event.type == SDL_MOUSEBUTTONUP){
            if(event.button.button == SDL_BUTTON_LEFT) {
                MOUSE = Left_Up;
            }
        }
    }
}

void first_Menu::handle_input(bool &running, bool &ingame)
{
    /**click in START button */
    start_button->handle_input(MOUSE, mouse);
    if(start_button->chosen) {
        ingame = 1;
        running_Menu = 0;
        start_button->chosen = false;
    }

    /**click in QUIT button */
    quit_button->handle_input(MOUSE, mouse);
    if(quit_button->chosen) {
        ingame = 0;
        running = 0;
        running_Menu = 0;
        quit_button->chosen = false;
    }
}

void first_Menu::draw()
{
    backgr_IMG = loadTexture("Resourse/Image/Menu/backgr.png", renderer);

    start_button->draw("start_button", button_OG_y_crd);

    quit_button->draw("quit_button", (start_button->coordinate.y + start_button->Size.y + 30));
}

void first_Menu::render()
{
    SDL_SetRenderDrawColor(renderer, 0 ,0 ,0 , 255);
    SDL_RenderClear(renderer);
    renderTexture(backgr_IMG, renderer, 0, 0);

    start_button->render();

    quit_button->render();

    SDL_RenderPresent(renderer);
}

/** second Menu */

//void second_Menu::input(bool &running)
//{
//    SDL_GetMouseState(&mouse.x, &mouse.y);
//    SDL_Event event;
//
//    while(SDL_PollEvent(&event)) {
//        if(event.type == SDL_QUIT) {
//            running = false;
//            break;
//        }
//        if(event.type == SDL_MOUSEBUTTONDOWN) {
//            if (event.button.button == SDL_BUTTON_LEFT) {
//                MOUSE = Left_Down;
//            }
//        }
//        if(event.type == SDL_MOUSEBUTTONUP){
//            if(event.button.button == SDL_BUTTON_LEFT) {
//                MOUSE = Left_Up;
//                cout<<mouse.x<<' '<<mouse.y<<endl;
//
//            }
//        }
//    }
//}
//
//void second_Menu::handle_input(bool &running, bool &ingame)
//{
//    /**click in START button */
//    if(MOUSE == Left_Down) {
//        if( ( mouse.x>=start_coordinate.x && mouse.x<=(start_coordinate.x+start_size.x) )
//          &&( mouse.y>=start_coordinate.y && mouse.y<=(start_coordinate.y+start_size.y) ) )  {
//
//           start_click_signal = 1;
//        }
//        else start_click_signal = 0;
//    }
//
//    if(MOUSE == Left_Up && (mouse.x>=start_coordinate.x && mouse.x<=(start_coordinate.x+start_size.x))
//       && (mouse.y>=start_coordinate.y && mouse.y<=(start_coordinate.y+start_size.y))) {
//
//            if(start_click_signal == 1) {
//                start_click_signal = 0;
//                ingame = 1;
//                cout<<mouse.x<<' '<<mouse.y<<endl;
//            }
//    }
//
//    /**click in QUIT button */
//    if(MOUSE == Left_Down) {
//        if( ( mouse.x>=quit_coordinate.x && mouse.x<=(quit_coordinate.x+quit_size.x) )
//          &&( mouse.y>=quit_coordinate.y && mouse.y<=(quit_coordinate.y+quit_size.y) ) )  {
//
//           quit_click_signal = 1;
//        }
//        else quit_click_signal = 0;
//    }
//
//    if(MOUSE == Left_Up && (mouse.x>=quit_coordinate.x && mouse.x<=(quit_coordinate.x+quit_size.x))
//                        && (mouse.y>=quit_coordinate.y && mouse.y<=(quit_coordinate.y+quit_size.y))) {
//
//        if(quit_click_signal == 1) {
//            quit_click_signal = 0;
//            ingame = 0;
//            running = 0;
//            cout<<mouse.x<<' '<<mouse.y<<endl;
//        }
//    }
//}
//
//void second_Menu::loop(SDL_Renderer *renderer, bool &ingame)
//{
//    while(running) {
//        render(renderer);
//        input();
//        handle_input(ingame);
//
//    }
//}
//
//void second_Menu::draw(SDL_Renderer *renderer)
//{
//}
//
//void second_Menu::render(SDL_Renderer *renderer)
//{
//    SDL_SetRenderDrawColor(renderer, 0 ,0 ,0 , 255);
//    SDL_RenderClear(renderer);
//
//    renderTexture(start_button, renderer, start_coordinate.x, start_coordinate.y);
//
//    renderTexture(quit_button, renderer, quit_coordinate.x, quit_coordinate.y);
//
//    SDL_RenderPresent(renderer);
//}
//void second_Menu::free()
//{
//    SDL_DestroyTexture(start_button);
//    SDL_DestroyTexture(guide_button);
//    SDL_DestroyTexture(quit_button);
//    start_button=nullptr;
//    quit_button=nullptr;
//    guide_button=nullptr;
//
//}
