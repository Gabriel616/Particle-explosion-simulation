#ifndef PARTICLE_H_
#define PARTICLE_H_

#include <iostream>
#include <time.h>
#include <random>
#include <stdlib.h>
#include "Screen.h"

using namespace std;

class Particle
{

public : 
	
private :
	double xpos; //x position of particle 
	double ypos; //y position of particle 

	double xspeed;
	double yspeed;

	double direction;
	double speed;
public : 
	Particle();

	double getX();
	double getY();	
	void setX(int );
	void setY(int );

	void update(int );

	~Particle();
};

#endif // !PARTICLE_H_
