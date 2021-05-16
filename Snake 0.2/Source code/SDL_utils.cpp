#include "SDL_utils.h"

//*****************************************************
// The common function for initializing, using and closing a console that using SDL2

void logSDLError(ostream& os,
                 const string &msg, bool fatal)
{
    os << msg << " Error: " << SDL_GetError() << endl;
    if (fatal) {
        SDL_Quit();
        exit(1);
    }
}

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer,
	int screenWidth, int screenHeight, const char* windowTitle)
{
    if (SDL_Init(SDL_INIT_EVERYTHING)!=0)
        logSDLError(cout, "SDL_Init", true);

    window = SDL_CreateWindow(windowTitle, SDL_WINDOWPOS_CENTERED,
       SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
    if (window == nullptr) logSDLError(cout, "CreateWindow", true);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) logSDLError(cout, "CreateRenderer", true);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, screenWidth, screenHeight);

    TTF_Init();

    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) logSDLError(cout, "mixer init", true);
}

void quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
    TTF_Quit();
    Mix_Quit();
	SDL_Quit();
}

void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if ( SDL_WaitEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(100);
    }
}

Mix_Chunk *load_SoundEffect(const string &file, const string &error_sound_type)
{
    Mix_Chunk *sound=NULL;
    sound = Mix_LoadWAV(file.c_str());
    if(sound == NULL) cout<<"Failed to load "<<error_sound_type<<" sound! Mixer Error: \n"<<Mix_GetError()<<endl;
}

Mix_Music *loadMusic(const string &file, const string &error_sound_type)
{
    Mix_Music *sound=NULL;
    sound = Mix_LoadMUS(file.c_str());
    if(sound == NULL) cout<<"Failed to load "<<error_sound_type<<" sound! Mixer Error: \n"<<Mix_GetError()<<endl;
}
