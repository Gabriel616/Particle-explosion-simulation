#include <iostream>
#include <SDL.h>
//#include "Screen.h"
#include "Particle.h"
#include "Swarm.h"
#include <iomanip>

using namespace std;
using namespace scr;


int main(int argc, char* argv[])
{
	Screen sc1;
	if (!sc1.init())
		cout << "Initialization failed !!!" << endl;
	else
		cout << "Initialization succesfull !" << endl;
	
	//particle initialization
	srand((unsigned int)time(NULL));
	Swarm sw;

	//performance counters init
	unsigned int frames = 0;
	Uint64 start = SDL_GetPerformanceCounter();
	
	//game loop
	while (true)
	{
		int elapsed = SDL_GetTicks();

		//update particles
		sw.updateSwarm(elapsed);
		//sc1.clearScreen();

		//generate colors
		unsigned char red = (unsigned char)((1 + sin(elapsed * 0.0002)) * 128);
		unsigned char blue = (unsigned char)((1 + sin(elapsed * 0.0003)) * 128);
		unsigned char green = (unsigned char)((1 + sin(elapsed * 0.0001)) * 128);

		//draw particles
		for (int i = 0; i < Swarm::NUMBER_OF_PARTICLES; i++)
		{
			//sc1.setPixel(sw.getSwarm()[i].getX() * Screen::SCREEN_WIDTH / 2, sw.getSwarm()[i].getY()* Screen::SCREEN_HEIGHT / 2 , red, blue, green);
			int x = (sw.getSwarm()[i].getX() + 1 )* scr::Screen::SCREEN_WIDTH / 2;
			int y = sw.getSwarm()[i].getY() * scr:: Screen::SCREEN_WIDTH / 2 + scr::Screen::SCREEN_HEIGHT/2;
			sc1.setPixel(x, y, red, blue, green);
		}
		//box blur
		sc1.boxBlur();

		//draw the screen
		sc1.update();
			
		//check for events (mouse clicks, events)
		if (!sc1.processEvents())
			break;

		//measure performance
		frames++;
		const Uint64 end = SDL_GetPerformanceCounter();
		const static Uint64 freq = SDL_GetPerformanceFrequency();
		const double seconds = (end - start) / static_cast<double>(freq);
		if (seconds > 2.0)
		{
			std::cout
				<< frames << " frames in "
				<< std::setprecision(1) << std::fixed << seconds << " seconds = "
				<< std::setprecision(1) << std::fixed << frames / seconds << " FPS ("
				<< std::setprecision(3) << std::fixed << (seconds * 1000.0) / frames << " ms/frame)"
				<< std::endl;
			start = end;
			frames = 0;
		}	
	}
sc1.close();
return 0;
}
