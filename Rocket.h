#ifndef ROCKET_H
#define ROCKET_H

#include "Engine.h"

typedef struct
{
	int size;
	int* x;
	int* y;

}rocketLocation;

class Rocket
{
private:
	Engine* engine;

public:
	Rocket(Engine* eng);

	//initialize rocket
	void Init();
	//create rocket from player position
	void draw(int rocketX, int rocketY);
	//rocket going up
	void Move(float move);
	void remove(int zero);
	
	rocketLocation rocketPos;
};

#endif // ROCKET_H

