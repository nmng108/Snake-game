#include "Menu.h"

 /** first Menu **/
first_Menu::first_Menu(SDL_Renderer *ren)
{
    renderer = ren;
    draw();
}

first_Menu::~first_Menu()
{
    SDL_DestroyTexture(start_button);
    SDL_DestroyTexture(quit_button);
    SDL_DestroyTexture(guide_button);
    SDL_DestroyRenderer(renderer);
}
void first_Menu::input(bool &running)
{
    SDL_GetMouseState(&mouse.x, &mouse.y);

    while(SDL_PollEvent(&event)) {
        if(event.type == SDL_QUIT) {
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
    if(MOUSE == Left_Down) {
        if( ( mouse.x>=start_coordinate.x && mouse.x<=(start_coordinate.x+start_size.x) )
          &&( mouse.y>=start_coordinate.y && mouse.y<=(start_coordinate.y+start_size.y) ) )  {

           start_click_signal = 1;
        }
        else start_click_signal = 0;
    }

    if(MOUSE == Left_Up && (mouse.x>=start_coordinate.x && mouse.x<=(start_coordinate.x+start_size.x))
       && (mouse.y>=start_coordinate.y && mouse.y<=(start_coordinate.y+start_size.y))) {

            if(start_click_signal == 1) {
                start_click_signal = 0;
                ingame = 1;
                cout<<mouse.x<<' '<<mouse.y<<endl;
            }
    }

    /**click in QUIT button */
    if(MOUSE == Left_Down) {
        if( ( mouse.x>=quit_coordinate.x && mouse.x<=(quit_coordinate.x+quit_size.x) )
          &&( mouse.y>=quit_coordinate.y && mouse.y<=(quit_coordinate.y+quit_size.y) ) )  {

           quit_click_signal = 1;
        }
        else quit_click_signal = 0;
    }

    if(MOUSE == Left_Up && (mouse.x>=quit_coordinate.x && mouse.x<=(quit_coordinate.x+quit_size.x))
                        && (mouse.y>=quit_coordinate.y && mouse.y<=(quit_coordinate.y+quit_size.y))) {

        if(quit_click_signal == 1) {
            quit_click_signal = 0;
            ingame = 0;
            running = 0;
            cout<<mouse.x<<' '<<mouse.y<<endl;
        }
    }
}

void first_Menu::loop(bool &ingame)
{
//    while(running) {
//        render(ren);
//        input();
//        handle_input(ingame);

//    }
}

void first_Menu::draw()
{
    start_button = loadTexture("Resourse/Image/Menu/start_button.png", renderer);
    SDL_QueryTexture(start_button, NULL, NULL, &start_size.x, &start_size.y);
    start_coordinate.x = WIDTH_SCREEN/2 - start_size.x/2;
    start_coordinate.y = OG_Y_button;
    cout<<start_coordinate.x<<' '<<start_coordinate.y<<endl;

    quit_button = loadTexture("Resourse/Image/Menu/quit_button.png", renderer);
    SDL_QueryTexture(quit_button, NULL, NULL, &quit_size.x, &quit_size.y);
    quit_coordinate.x = WIDTH_SCREEN/2 - quit_size.x/2;
    quit_coordinate.y = OG_Y_button + start_size.y + 30;
    cout<<quit_coordinate.x<<' '<<quit_coordinate.y<<endl;

}

void first_Menu::render()
{
    SDL_SetRenderDrawColor(renderer, 0 ,0 ,0 , 255);
    SDL_RenderClear(renderer);

    renderTexture(start_button, renderer, start_coordinate.x, start_coordinate.y);

    renderTexture(quit_button, renderer, quit_coordinate.x, quit_coordinate.y);

    SDL_RenderPresent(renderer);
}
void first_Menu::free()
{
//    SDL_DestroyTexture(start_button);
//    SDL_DestroyTexture(guide_button);
//    SDL_DestroyTexture(quit_button);
//    start_button=nullptr;
//    quit_button=nullptr;
//    guide_button=nullptr;
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
//    start_button = loadTexture("Resourse/Image/Menu/start_button.png", renderer);
//    SDL_QueryTexture(start_button, NULL, NULL, &start_size.x, &start_size.y);
//    start_coordinate.x = WIDTH_SCREEN/2 - start_size.x/2;
//    start_coordinate.y = OG_Y_button;
//    cout<<start_coordinate.x<<' '<<start_coordinate.y<<endl;
//
//    quit_button = loadTexture("Resourse/Image/Menu/quit_button.png", renderer);
//    SDL_QueryTexture(quit_button, NULL, NULL, &quit_size.x, &quit_size.y);
//    quit_coordinate.x = WIDTH_SCREEN/2 - quit_size.x/2;
//    quit_coordinate.y = OG_Y_button + start_size.y + 30;
//    cout<<quit_coordinate.x<<' '<<quit_coordinate.y<<endl;
//
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
//} asa

