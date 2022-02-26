#include "Alien.h"
#include<stdlib.h>
#include<time.h>

using namespace std;

//total alien army size
const int alienRows = 6;
const int alienCols = 12;

//constructor
Alien::Alien(Engine* eng, Bomb* bo)
{
	engine = eng;
	bomb = bo;
	moveRight = true;
	moveDown = false;
	allAlienKilled = false;
	reachBottom = false;
	this->timeBetweenBombs = 2.0f;
	timeOfLastBomb = 0.0f;
}

//initialize alien army
void Alien::Init()
{
	alienArmy.size = 0;
	alienArmy.x = (float*)malloc(sizeof(float) * alienRows * alienCols);
	alienArmy.y = (float*)malloc(sizeof(float) * alienRows * alienCols);
	alienArmy.en = (Engine::Sprite*)malloc(sizeof(int) * alienRows * alienCols);
	for (int row = 0; row < alienRows; row++)
	{
		int y = row * Engine::SpriteSize + Engine::SpriteSize / 2 + 2 * row;

		for (int col = 0; col < alienCols; col++)
		{
			int x = col * Engine::SpriteSize + 2 * col;			
			alienArmy.x[alienArmy.size] = (float)x;
			alienArmy.y[alienArmy.size] = (float)y;
			
			if (row % 2 == 0)
			{
				alienArmy.en[alienArmy.size] = Engine::Sprite::Enemy1;
				engine->drawSprite(Engine::Sprite::Enemy1, x, y);
			}				
			else if (row % 2 == 1)
			{
				alienArmy.en[alienArmy.size] = Engine::Sprite::Enemy2;
				engine->drawSprite(Engine::Sprite::Enemy2, x, y);
			}
			alienArmy.size += 1;
		}
	}
}

//update army positon
void Alien::Move(float move)
{
	for (int it = 0; it < alienArmy.size; it++)
	{
		if (moveRight)
			alienArmy.x[it] += 0.25f * move;//go right: speed 0.25*move		
		else
			alienArmy.x[it] -= 0.25f * move;//go left			
	}

	for (int it = 0; it < alienArmy.size; it++)
	{
		if (alienArmy.x[it] >= (Engine::CanvasWidth - Engine::SpriteSize))//army go down condition
		{
			moveRight = false;
			moveDown = true;
			break;
		}

		else if (alienArmy.x[it] <= 0)//army go down condition
		{
			moveRight = true;
			moveDown = true;
			break;
		}
	}
	if (moveDown)
	{
		moveDown = false;
		for (int it = 0; it < alienArmy.size; it++)
			alienArmy.y[it] += 40.0f * move;//go down speed		
	}
}

void Alien::Refresh()
{
	for(int it = 0; it < alienArmy.size; it++)
		engine->drawSprite(alienArmy.en[it], (int)alienArmy.x[it], (int)alienArmy.y[it]);
}

//drop bomb and calculate its speed
void Alien::dropBomb(float timer)
{
	bool creatBomb = (timer - this->timeOfLastBomb) > this->timeBetweenBombs;//drop bomb condition: 2s
	srand((unsigned int)time(NULL));
	if (creatBomb)
	{
		if (alienArmy.size > 0)
		{
			int random_var = rand() % alienArmy.size;//random choose one alien to release bomb
			bomb->draw(alienArmy.x[random_var], alienArmy.y[random_var]);
			this->timeOfLastBomb = timer;
		}
	}	
}

//check collison between rocket and alien
//
void Alien::Collision(Rocket* rocket, Player* player)
{
	for (int it = 0; it < rocket->rocketPos.size; ++it)
	{
		//rocket is not inside of alien army
		if ((rocket->rocketPos.y[it] + Engine::SpriteSize) < alienArmy.y[0]) continue;

		if (rocket->rocketPos.y[it] > (alienArmy.y[alienArmy.size - 1] + Engine::SpriteSize)) break;

		//rocket is inside of alien army: 
		//rocket from [x1+(32/3)] - [x1+32-(32/3)] to [y1+(32/3)] - [y1+32-(32/3)]
		//alien from [x1] - [x1+32] to [y1] - [y1+32]
		for (int itr = 0; itr < alienArmy.size; ++itr)
		{
			if (((rocket->rocketPos.x[it] + Engine::SpriteSize / 3) > alienArmy.x[itr]) &&
				((rocket->rocketPos.x[it] + Engine::SpriteSize - Engine::SpriteSize / 3) < (alienArmy.x[itr] + Engine::SpriteSize)) &&
				((rocket->rocketPos.y[it] + Engine::SpriteSize / 3) > alienArmy.y[itr]) &&
				((rocket->rocketPos.y[it] + Engine::SpriteSize - Engine::SpriteSize / 3) < (alienArmy.y[itr] + Engine::SpriteSize)))
			{
				rocket->remove(it);
				remove(itr);
				player->score += 10;
			}
		}
	}
	if (alienArmy.size == 0)
		allAlienKilled = true;
}

void Alien::remove(int zero)
{
	for (int it = zero; it < alienArmy.size; it++)
	{
		alienArmy.x[it] = alienArmy.x[it + 1];
		alienArmy.y[it] = alienArmy.y[it + 1];
		alienArmy.en[it] = alienArmy.en[it + 1];
	}
	alienArmy.size -= 1;
}

//allien reach bottom?
void Alien::checkBottom()
{
	for (int it = alienArmy.size - 1; it >= 0; it--)
	{
		if (alienArmy.y[it] > (Engine::CanvasHeight - Engine::SpriteSize))
		{
			reachBottom = true;			
		}
	}
}

