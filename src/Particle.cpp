#include "Particle.h"

Particle::Particle() {
	
	/*xpos = ((2.0 * rand()) / RAND_MAX) - 1;
	ypos = ((2.0 * rand()) / RAND_MAX) - 1;*/

	xpos = 0;
	ypos = 0;
	xspeed = 0.001 * (((2.0 * rand()) / RAND_MAX) - 1);
	yspeed = 0.001 * (((2.0 * rand()) / RAND_MAX) - 1);
	
	direction = 2 * M_PI* rand()/RAND_MAX;
	speed = 0.0001 * rand()/RAND_MAX;
}

double Particle::getX(){
	return this->xpos;
}

double Particle::getY() {
	return this->ypos;
}

void Particle::setX(int x) {
	this->xpos = x;
}

void Particle::setY(int y) {
	this->ypos = y;
}



void Particle::update(int interval) {
//xpos += xspeed;
//ypos += yspeed;
//
//if (xpos <= -1.0 || xpos >= 1.0) {
//	xspeed = xspeed;
//}
//
//if (ypos <= -1.0 || ypos >= 1.0) {
//	yspeed = -yspeed;
//}

	xpos += speed * cos(direction) * interval;
	ypos += speed * sin(direction) * interval;


}

Particle::~Particle() {

}