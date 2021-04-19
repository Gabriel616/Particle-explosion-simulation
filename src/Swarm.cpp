#include "Swarm.h"

Swarm::Swarm() : lastTime(0) {
	particleArr = new Particle[NUMBER_OF_PARTICLES];
}


Particle* Swarm::getSwarm(){
	return this->particleArr;
}

void Swarm::updateSwarm(int elapsed) {

	int interval = elapsed - lastTime;

	for (int i = 0; i < NUMBER_OF_PARTICLES; i++)
		particleArr[i].update(interval);

	lastTime = elapsed;
}

Swarm::~Swarm(){
	delete[] particleArr;
}