#include<stdlib.h>
#include "Rocket.h"

const int totalRocket = 500;

Rocket::Rocket(Engine* eng)
{
	engine = eng;
}

//initialize rocket
void Rocket::Init()
{
	rocketPos.size = 0;
	rocketPos.x = (int*)malloc(sizeof(int) * totalRocket);
	rocketPos.y = (int*)malloc(sizeof(int) * totalRocket);

	for (int it = 0; it < totalRocket; it++)
	{
		rocketPos.x[it] = 0;
		rocketPos.y[it] = 0;
	}
}

//create rocket from player position
void Rocket::draw(int rocketX, int rocketY)
{
	rocketPos.x[rocketPos.size] = rocketX;
	rocketPos.y[rocketPos.size] = rocketY;
	engine->drawSprite(Engine::Sprite::Rocket, rocketPos.x[rocketPos.size], rocketPos.x[rocketPos.size]);
	rocketPos.size += 1;
}

//rocket going up
void Rocket::Move(float move)
{
	for (int it = 0; it < rocketPos.size; it++)
	{
		rocketPos.x[it] = rocketPos.x[it];
		rocketPos.y[it] -= (int)(8.0f * move); // rocket speed
		engine->drawSprite(Engine::Sprite::Rocket, rocketPos.x[it], rocketPos.y[it]);
	}
	if ((rocketPos.size > 0) && (rocketPos.y[0] < Engine::SpriteSize / 2)) // rocket not in screen
		remove(0);
}

void Rocket::remove(int zero)
{
	for (int it = zero; it < rocketPos.size; it++)
	{
		rocketPos.x[it] = rocketPos.x[it + 1];
		rocketPos.y[it] = rocketPos.y[it + 1];
	}
	rocketPos.size -= 1;
}
