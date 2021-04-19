#ifndef SWARM_H_
#define SWARM_H_

#include "Particle.h"

using namespace std;

class Swarm
{
public: 
	const static int NUMBER_OF_PARTICLES = (scr::Screen::SCREEN_HEIGHT * scr::Screen::SCREEN_WIDTH)/100;
private:
	Particle* particleArr;
	int lastTime;
public:
	Swarm();
	Particle* getSwarm();

	void updateSwarm(int );
	~Swarm();
};

#endif
