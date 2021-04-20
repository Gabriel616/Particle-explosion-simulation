#include "Screen.h"
#include <iomanip>

using namespace scr;

Screen::Screen() : window(NULL), renderer(NULL), texture(NULL), buffer_initial(NULL), buffer_blur(NULL)
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
    window = SDL_CreateWindow(
        "Particle Explosion",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH, SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN);

    if (window == NULL)
        return false;

    //renderer initialization
    renderer = SDL_CreateRenderer(
        window,
        -1, 
        SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
        return false;
    SDL_RendererInfo info;
   
    SDL_GetRendererInfo(renderer, &info);
    std::cout << "Renderer name: " << info.name << std::endl;
    std::cout << "Texture formats: " << std::endl;
    for (Uint32 i = 0; i < info.num_texture_formats; i++)
    {
        std::cout << SDL_GetPixelFormatName(info.texture_formats[i]) << std::endl;
    }
    //texture initialization
    texture = SDL_CreateTexture(
        renderer, 
        SDL_PIXELFORMAT_RGBA8888, 
        SDL_TEXTUREACCESS_STREAMING,
        SCREEN_WIDTH, SCREEN_HEIGHT);
    if (texture == NULL)
        return false;

    //first call to check functionality 
    buffer_initial = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];
    buffer_blur = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];
   
    if (buffer_initial == NULL)
        return false;

    if (SDL_UpdateTexture(texture, NULL, buffer_initial, SCREEN_WIDTH * sizeof(Uint32)) != 0)
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

void Screen::update() {
    SDL_UpdateTexture(this->texture, NULL, buffer_initial, SCREEN_WIDTH * sizeof(Uint32));
    SDL_RenderClear(this->renderer);
    SDL_RenderCopy(this->renderer, this->texture, NULL, NULL);
    SDL_RenderPresent(this->renderer);
}

void Screen::setPixel(int x, int y, Uint8 red, Uint8 green,  Uint8 blue ) {
    if (x<0 ||   x >= scr::Screen::SCREEN_WIDTH || y<0|| y >= scr::Screen::SCREEN_HEIGHT)
        return;
    Uint32 color = 0;

    //shift with 8 bits, then add the color to form an RGB corespondant
    color += red;
    color <<= 8;
    
    color += green;
    color <<= 8;
    
    color += blue;
    color <<= 8;
    
    color += 0xFF; //finally add the alpha value

    buffer_initial[(y * SCREEN_WIDTH) + x] = color; //indexing the screen matrix using the 1d array method
}

void Screen::clearScreen() {
    //setting the whole screen to black
    memset(buffer_initial, 0, scr::Screen::SCREEN_HEIGHT * scr::Screen::SCREEN_WIDTH * sizeof(Uint32));
    //memset(buffer_blur, 0, scr::Screen::SCREEN_HEIGHT * scr::Screen::SCREEN_WIDTH * sizeof(Uint32));

   }

void Screen::boxBlur() {
    Uint32* temp;
    temp = buffer_initial;
    buffer_initial = buffer_blur;
    buffer_blur = temp;

    //iterating through all the pixels
    for (int y = 0; y < scr::Screen::SCREEN_HEIGHT; y++) {
        for (int x = 0; x < scr::Screen::SCREEN_WIDTH;x++) {
            //defining the box 

            int redTotal = 0;
            int blueTotal = 0;
            int greenTotal = 0;
            for (int row = -1; row <= 1; row++) {
                for (int col = -1; col <= 1; col++) {
                    int xcurrent = x + row;
                    int ycurrent = y + col;

                    if (xcurrent >= 0 && xcurrent < SCREEN_WIDTH && ycurrent >= 0 && ycurrent < SCREEN_HEIGHT) {

                        Uint32  color = buffer_blur[ycurrent * scr::Screen::SCREEN_WIDTH + xcurrent];
                        Uint8 red = color >> 24; //shift with 24 bites to obtain the red 
                        Uint8 blue = color >> 16;
                        Uint8 green = color >> 8;

                        redTotal += red;
                        blueTotal += blue;
                        greenTotal += green;
                    }
                }
            }
            Uint8 red = redTotal / 9;
            Uint8 blue = blueTotal / 9;
            Uint8 green = greenTotal / 9;

            setPixel(x, y, red, green, blue);
        }
    }
}


void Screen::close()
{
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