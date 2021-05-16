#include "Menu.h"

 /** first Menu **/
first_Menu::first_Menu(SDL_Renderer *ren)
{
    renderer = ren;
    start_button = new Button(ren);
    highScore_button = new Button(ren);
    quit_button = new Button(ren);
    rankReset_button = new Button(ren);
    back_button  = new Button(ren);
    draw();
}

first_Menu::~first_Menu()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyTexture(backgr_IMG);
    backgr_IMG=NULL;
    delete start_button;
    delete highScore_button;
    delete quit_button;
    delete rankReset_button;
    delete back_button;
}

void first_Menu::open(bool &run_Menu, bool &running, bool &start)
{
    running_1stMenu = run_Menu;

    while(running_1stMenu) {
        input(running);

        handle_input(running, start);

        if(open_high_score_board) display_high_score_board(run_Menu, running);
        open_high_score_board = false;

        render();
    }

    run_Menu = running_1stMenu;
}

void first_Menu::input(bool &running)
{
    SDL_GetMouseState(&mouse.x, &mouse.y);

    while(SDL_PollEvent(&event)) {
        if(event.type == SDL_QUIT) {
            running_1stMenu = false;
            running = false;
            return;
        }
        if(event.key.keysym.sym == SDLK_ESCAPE) {
            running_1stMenu = false;
            running = false;
            return;
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

void first_Menu::handle_input(bool &running, bool &start)
{
    /** click on Start */
    start_button->handle_input(MOUSE, mouse);
    if(start_button->chosen) {
        start = true;
        running_1stMenu = false;
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
        start = false;
        running = false;
        running_1stMenu = false;
        quit_button->chosen = false;
    }
}

void first_Menu::draw()
{
    backgr_IMG = loadTexture("Resource/Image/Menu/backgr.png", renderer);

    start_button->draw("start", button_OG_y_crd);
    highScore_button->draw("highScore", (start_button->coordinate.y + start_button->Size.y + 30));
    quit_button->draw("quit", (highScore_button->coordinate.y + highScore_button->Size.y + 30));
    rankReset_button->draw("reset_rank", 558);
    back_button->draw("back", 610);
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


void first_Menu::process_score_log(const int &new_score, int &rank_sort)
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

    rank_sort = 0;
    for(int i=0; i<(arr_score.size()-1); i++) {
        if(new_score <= arr_score[i]) rank_sort++;
    }

    for(int i=0; i<arr_score.size(); i++) //delete elements which are similar to each other
        for(int j=i+1; j<arr_score.size(); j++)
            if(arr_score[i]==arr_score[j]) arr_score.erase(arr_score.begin()+j);

    for(int i=0; i<arr_score.size()-1; i++){ //sort all elements decreasingly
        int iMax=i;
        for(int j=i+1; j<arr_score.size(); j++) if(arr_score[iMax]<arr_score[j]) iMax=j;
        int tmp=arr_score[i];
        arr_score[i]=arr_score[iMax];
        arr_score[iMax]=tmp;
    }

    if(arr_score.size() > number_of_score_elements) arr_score.resize(number_of_score_elements);

    score_log.open("Resource/score_log.txt", ios::out); //write to file
    for(int i=0; i<arr_score.size(); i++) score_log<<arr_score[i]<<endl;
    score_log.close();
}

void first_Menu::display_high_score_board(bool &run_Menu, bool &running)
{
    vector<SDL_Color> color = {{136, 0, 27, 255}, {176, 88, 105, 255}, {225, 139, 185, 255}, {207, 152, 231, 255}, {144, 132, 178, 255}};

    while(true) {
        renderTexture("Resource/Image/Menu/hghScr_board.png", renderer, 0, 0);

        fstream score_log("Resource/score_log.txt", ios::in);
        arr_score.resize(number_of_score_elements);
        for(int i=0; i<number_of_score_elements; i++) {

            if(!score_log.eof()) {
                score_log>>arr_score[i];
                renderText(to_string(arr_score[i]), color[i], "Resource/Fonts/Tekton-Pro-Bold.ttf", 48, renderer, 500, 233 + i*63);
            }
            else {
                arr_score[i] = 0;
                renderText(to_string(arr_score[i]), color[i], "Resource/Fonts/Tekton-Pro-Bold.ttf", 48, renderer, 500, 233 + i*63);
            }
        }
        score_log.close();

        input(running);
        if(event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE) return;

        rankReset_button->handle_input(MOUSE, mouse);
        if(rankReset_button->chosen) {
            arr_score.assign(number_of_score_elements, 0);

            score_log.open("Resource/score_log.txt", ios::out);
            for(int i=0; i<number_of_score_elements; i++) score_log<<0<<endl;
            score_log.close();

            rankReset_button->chosen = false;
        }

        back_button->handle_input(MOUSE, mouse);
        if(back_button->chosen) {
            back_button->chosen = false;
            return;
        }

        rankReset_button->render();
        back_button->render();

        SDL_RenderPresent(renderer);
    }

}

/** second Menu */
second_Menu::second_Menu(SDL_Renderer *ren)
{
    renderer = ren;

    resume_button = new Button(ren);
    replay_button = new Button(ren);

    draw();
}
second_Menu::~second_Menu()
{
    SDL_DestroyRenderer(renderer);
    delete resume_button;
    delete replay_button;
}

void second_Menu::open(bool &running, bool &start, bool &ingame)
{
    running_2ndMenu = 1;
    while(running_2ndMenu) {
        input(running, start, ingame);
        handle_input(ingame);
        render();
    }
}

void second_Menu::input(bool &running, bool &start, bool &ingame)
{
    SDL_GetMouseState(&mouse.x, &mouse.y);

    event.key.keysym.sym=SDLK_UNKNOWN;
    event.type=SDL_FIRSTEVENT;

    while(SDL_PollEvent(&event)) {
        if(event.type == SDL_QUIT) {
            running = start = ingame = running_2ndMenu = false;
            return;
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
        if(event.type == SDL_KEYDOWN)
            if(event.key.keysym.sym == SDLK_ESCAPE || event.key.keysym.sym == SDLK_SPACE) {
            running_2ndMenu = false;
            return;
            }
    }
}

void second_Menu::handle_input(bool &ingame)
{
    /**click on RESUME button */
    resume_button->handle_input(MOUSE, mouse);
    if(resume_button->chosen) {
        running_2ndMenu = false;
        resume_button->chosen = false;
        return;
    }
    /**click on REPLAY button */
    replay_button->handle_input(MOUSE, mouse);
    if(replay_button->chosen) {
        ingame = running_2ndMenu = false;
        replay_button->chosen = false;
        return;
    }
}

void second_Menu::draw()
{
    resume_button->draw("resume", button_OG_y_crd);
    replay_button->draw("replay", resume_button->coordinate.y + resume_button->Size.y + 30);
}

void second_Menu::render()
{
    SDL_SetRenderDrawColor(renderer, 0 ,0 ,0 , 255);
    SDL_RenderClear(renderer);

    resume_button->render();
    replay_button->render();

    SDL_RenderPresent(renderer);
}
