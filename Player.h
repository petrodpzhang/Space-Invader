#ifndef PLAYER_H
#define PLAYER_H

#include "Engine.h"
#include "Bomb.h"
#include "Rocket.h"
#include <cstring>
#include <string>


class Player
{
private:
	Engine* engine;
	Rocket* rocket;
	bool fireKey;
	bool playerKilled;// player hit by bomb
	int killedLocation;// the position when bomb hit player
	float killedTime;// the time when bomb hit player
public:
	int score;
	int life;
	int x;
	
	Player(Engine* eng, Rocket* roc);
	//display score, life
	void showScore();
	void showLife();

	//initialize rocket
	void Init();
	//player position from keys input
	void Move(Engine::PlayerInput keys);
	void Fire(Engine::PlayerInput keys);
	//check collision between bomb and player
	void Collision(Bomb* bomb, float timer);
	//shows info when hit
	void displayInfo(float timer);
};

#endif