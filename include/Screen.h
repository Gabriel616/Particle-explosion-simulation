#include <iostream>
#include <SDL.h>

using namespace std;

namespace scr
{
    class Screen
    {
    public:
        const static int SCREEN_HEIGHT = 600;
        const static int SCREEN_WIDTH = 800;

    public:
        SDL_Window* window;
        SDL_Renderer* renderer;
        SDL_Texture* texture;
        Uint32* buffer;
       
    public:
        Screen();
        bool init();
        bool processEvents();
        void update();
        void close();
        void setPixel(int x, int y, Uint8 red, Uint8 blue, Uint8 Green );
        void clearScreen();
      

        ~Screen();
    };
}
