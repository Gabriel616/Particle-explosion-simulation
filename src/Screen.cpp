#include "Screen.h"

using namespace scr;

Screen::Screen() : window(NULL), renderer(NULL), texture(NULL), buffer(NULL)
{
}

bool Screen::init()
{
    if ((SDL_INIT_EVERYTHING) < 0)
    {
        cout << "SDL Init failed ! " << endl;
        return false;
    }

    //window initialization
    window = SDL_CreateWindow("Particle Explosion", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (window == NULL)
        return false;

    //renderer initialization
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
        return false;

    //texture initialization
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, SCREEN_WIDTH, SCREEN_HEIGHT);
    if (texture == NULL)
        return false;

    //mem buffer initialization
    buffer = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];
    if (buffer == NULL)
        return false;

    if (SDL_UpdateTexture(texture, NULL, buffer, SCREEN_WIDTH * sizeof(Uint32)) != 0)
        return false;
    if (SDL_RenderClear(renderer) != 0)
        return false;
    if (SDL_RenderCopy(renderer, texture, NULL, NULL) != 0)
        return false;
    //Update the screen with any rendering performed since the last call
    SDL_RenderPresent(renderer);

    return true;
}

bool Screen::processEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT)
            return false;
    }
    
    return true;
}

void Screen::close()
{
    if(buffer!=NULL)
        delete[] buffer;
    if (window != NULL)
        SDL_DestroyWindow(window);
    if (renderer != NULL)
        SDL_DestroyRenderer(renderer);
    if (texture != NULL)
        SDL_DestroyTexture(texture);

    SDL_Quit();
}

Screen::~Screen() {
    this->close();
}