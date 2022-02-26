#include "Bomb.h"
#include<stdlib.h>

const int totalBomb = 500;

Bomb::Bomb(Engine* eng)
{
	engine = eng;	
}

//initialize bomb
void Bomb::Init()
{
	bombPos.size = 0;
	bombPos.x = (float*)malloc(sizeof(float) * totalBomb);
	bombPos.y = (float*)malloc(sizeof(float) * totalBomb);	

	for (int it = 0; it < totalBomb; it++)
	{
		bombPos.x[it] = 0.0f;
		bombPos.y[it] = 0.0f;
	}
}

//create bomb from alien position
void Bomb::draw(float bombX, float bombY)
{
	bombPos.x[bombPos.size] = bombX;
	bombPos.y[bombPos.size] = bombY;
	engine->drawSprite(Engine::Sprite::Bomb, (int)bombPos.x[bombPos.size], (int)bombPos.x[bombPos.size]);
	bombPos.size += 1;
}

//bomb moving down
void Bomb::Refreash(float move)
{
	for (int it = 0; it < bombPos.size; it++)
	{
		bombPos.x[it] = bombPos.x[it];
		bombPos.y[it] += 2.0f * move; //moving speed
		engine->drawSprite(Engine::Sprite::Bomb, (int)bombPos.x[it], (int)bombPos.y[it]);
	}
	if ((bombPos.size > 0) && (bombPos.y[0] >= Engine::CanvasHeight)) //bomb is not inside of screen
		remove(0);
}

void Bomb::remove(int zero)
{
	for (int it = zero; it < bombPos.size; it++)
	{
		bombPos.x[it] = bombPos.x[it + 1];
		bombPos.y[it] = bombPos.y[it + 1];
	}
	bombPos.size -= 1;
}
