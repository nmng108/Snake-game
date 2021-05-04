#include "Menu.h"

 /** first Menu **/
first_Menu::first_Menu(SDL_Renderer *ren)
{
    renderer = ren;
    start_button = new Button(ren);
    highScore_button = new Button(ren);
    quit_button = new Button(ren);
    draw();
}

first_Menu::~first_Menu()
{
    SDL_DestroyRenderer(renderer);
    delete start_button;
    delete highScore_button;
    delete quit_button;
}

void first_Menu::open(bool &run_Menu, bool &running, bool &ingame)
{
    running_Menu = run_Menu;
    while(running_Menu) {
        if(open_high_score_board) display_high_score_board(run_Menu, running);
        else {
            render();
            input(running);
            handle_input(running, ingame);
        }
    }
}

void first_Menu::input(bool &running)
{
    SDL_GetMouseState(&mouse.x, &mouse.y);

    event.key.keysym.sym=SDLK_UNKNOWN;
    event.type=SDL_FIRSTEVENT;

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
    /** click on Start */
    start_button->handle_input(MOUSE, mouse);
    if(start_button->chosen) {
        ingame = true;
        running_Menu = false;
        start_button->chosen = false;
    }

    /** click on High Score */
    highScore_button->handle_input(MOUSE, mouse);
    if(highScore_button->chosen) {
        open_high_score_board = true;
        highScore_button->chosen = false;
    }

    /** click on Quit */
    quit_button->handle_input(MOUSE, mouse);
    if(quit_button->chosen) {
        ingame = false;
        running = false;
        running_Menu = false;
        quit_button->chosen = false;
    }
}

void first_Menu::draw()
{
    backgr_IMG = loadTexture("Resource/Image/Menu/backgr.png", renderer);

    start_button->draw("start", button_OG_y_crd);
    highScore_button->draw("highScore", (start_button->coordinate.y + start_button->Size.y + 30));
    quit_button->draw("quit", (highScore_button->coordinate.y + highScore_button->Size.y + 30));
}

void first_Menu::render()
{
    if(!open_high_score_board)
    {
        renderTexture(backgr_IMG, renderer, 0, 0);
        start_button->render();
        highScore_button->render();
        quit_button->render();
    }
    SDL_RenderPresent(renderer);
}


void first_Menu::process_score_log(const int &new_score)
{
    fstream score_log("Resource/score_log.txt", ios::in);
    arr_score.clear();
    while(!score_log.eof()) { //read the last number twice???
        int tmp;
        score_log>>tmp;
        arr_score.push_back(tmp);
    }
    score_log.close();

    arr_score[arr_score.size()-1]=new_score;

    for(int i=0;i<arr_score.size();i++)
        for(int j=i+1;j<arr_score.size();j++)
            if(arr_score[i]==arr_score[j]) arr_score.erase(arr_score.begin()+j);

    for(int i=0;i<arr_score.size()-1;i++){
        int iMax=i;
        for(int j=i+1;j<arr_score.size();j++) if(arr_score[iMax]<arr_score[j]) iMax=j;
        int tmp=arr_score[i];
        arr_score[i]=arr_score[iMax];
        arr_score[iMax]=tmp;
    }

    score_log.open("Resource/score_log.txt", ios::out);
    if(arr_score.size() > 10) arr_score.resize(10);
    for(int i=0;i<arr_score.size();i++) score_log<<arr_score[i]<<endl;
    score_log.close();
}

void first_Menu::display_high_score_board(bool &run_Menu, bool &running)
{
    renderTexture("Resource/Image/hghScr_board.png", renderer, 0, 0);
    vector<SDL_Color> color = {{136, 0, 27, 255}, {176, 88, 105, 255}, {225, 139, 185, 255}, {207, 152, 231, 255}, {144, 132, 178, 255}};

    ifstream score_log("Resource/score_log.txt");
    arr_score.resize(5);
    for(int i=0; (i<5) && !score_log.eof(); i++) {
        score_log>>arr_score[i];
        renderText(to_string(arr_score[i]), color[i], "Resource/Fonts/Tekton-Pro-Bold.ttf", 48, renderer, 500, 233 + i*63);
    }
    score_log.close();

    SDL_RenderPresent(renderer);
    while(true)
        if(SDL_WaitEvent(&event)) {
            if(event.type == SDL_QUIT) {
                open_high_score_board = 0;
                running = false;
                running_Menu = false;
                return;
            }
            if(event.type == SDL_KEYDOWN) {
                open_high_score_board = 0;
                return;
            }
        }


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
//
//    /**click in QUIT button */
//}
//
//void second_Menu::loop(SDL_Renderer *renderer, bool &ingame)
//{
//    while(running) {
//        render(renderer);
//        input();
//        handle_input(ingame);
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
//    SDL_RenderPresent(renderer);
//}
