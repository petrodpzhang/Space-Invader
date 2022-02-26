#ifndef BOMB_H
#define BOMB_H

#include"Engine.h"

typedef struct
{
	int size;
	float* x;
	float* y;

}bombLocation;

class Bomb
{
private:
	Engine* engine;

public:
	Bomb(Engine* eng);
	//initialize bomb
	void Init();
	//create bomb from alien position
	void draw(float bombX, float bombY);
	//bomb moving down
	void Refreash(float move);	
	void remove(int zero);
	
	bombLocation bombPos;
};

#endif // !BOMB_H

