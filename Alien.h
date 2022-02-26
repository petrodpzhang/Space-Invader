#ifndef ALIEN_H
#define ALIEN_H
#include"Engine.h"
#include"Bomb.h"
#include "Rocket.h"
#include "Player.h"

typedef struct
{
	int size;
	float* x;
	float* y;
	Engine::Sprite* en;
	
}alienMatrix;

class Alien
{
private:
	Engine* engine;
	Bomb* bomb;
	//alien moving to right?
	bool moveRight;
	//record the bomb dropping time
	float timeOfLastBomb;
public:
	Alien(Engine* eng, Bomb* bo);
	//alien moving to down?
	bool moveDown;
	//all aliens were killed?
	bool allAlienKilled;
	//allien reach bottom?
	bool reachBottom;
	//time intervals between bombs dropping
	float timeBetweenBombs;

	//initialize alien army
	void Init();
	//update army positon
	void Move(float move);	
	void Refresh();
	//drop bomb and calculate its speed
	void dropBomb(float timer);
	//check collison between rocket and alien
	void Collision(Rocket* rocket, Player* player);
	//refresh alien army after hit by rocket
	void remove(int zero);
	//allien reach bottom?
	void checkBottom();
	
	alienMatrix alienArmy;
};


#endif // !ALIEN_H

