#include "Button.h"

Button::Button(SDL_Renderer *ren)
{
   renderer = ren;
   click_sound = load_SoundEffect("Resource/click.wav", "click");
}

Button::~Button()
{
    for(int i=0;i<3;i++) {
        SDL_DestroyTexture(button_IMG[i]);
        button_IMG[i] = NULL;
    }
    SDL_DestroyRenderer(renderer);
    button_IMG.clear();
    Mix_FreeChunk(click_sound);
    click_sound = NULL;
}

void Button::draw(const string &filepath_keyword, int crd_y)
{
    string filepath_1 = "Resource/Image/Menu/" + filepath_keyword + "0.png",
           filepath_2 = "Resource/Image/Menu/" + filepath_keyword + "1.png",
           filepath_3 = "Resource/Image/Menu/" + filepath_keyword + "2.png";
    button_IMG.resize(3);
    button_IMG[0] = loadTexture(filepath_1, renderer);
    button_IMG[1] = loadTexture(filepath_2, renderer);
    button_IMG[2] = loadTexture(filepath_3, renderer);

    SDL_QueryTexture(button_IMG[0], NULL, NULL, &Size.x, &Size.y);
    coordinate = {(WIDTH_SCREEN/2 - Size.x/2), crd_y};

}

void Button::handle_input(Mouse MOUSE, SDL_Point mouse)
{
    if( ( mouse.x>=coordinate.x && mouse.x<=(coordinate.x+Size.x) )
      &&( mouse.y>=coordinate.y && mouse.y<=(coordinate.y+Size.y) ) )  {
        pointed = true;

        if(MOUSE == Left_Down) {
           click_signal = true;
        }
        else if(MOUSE==Left_Up && click_signal==true) {
            click_signal = false;
            chosen = 1;
            Mix_PlayChannel(-1, click_sound, 0);
        }
        else click_signal = false;
    }
    else {
        click_signal = false;
        pointed = false;
    }
}

void Button::render()
{
    if(click_signal==true) renderTexture(button_IMG[2], renderer, coordinate.x, coordinate.y);
    else if(pointed) renderTexture(button_IMG[1], renderer, coordinate.x, coordinate.y);
    else renderTexture(button_IMG[0], renderer, coordinate.x, coordinate.y);
}
