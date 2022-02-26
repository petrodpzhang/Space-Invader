#include "Player.h"
#include "Bomb.h"

using namespace std;

Player::Player(Engine* eng, Rocket* roc)
{
	engine = eng;
	rocket = roc;

	fireKey = false;
	playerKilled = false;
	killedLocation = 0;
	killedTime = 0.0f;
	
	score = 0;
	life = 3;
	x = 0;
}

void Player::showScore()
{
	string message = "Score: " + to_string(score);
	const char* msg = message.c_str();
	engine->drawText(msg, 0, 0);
}


void Player::showLife()
{
	string message = "Life: " + to_string(life);
	const char* msg = message.c_str();
	engine->drawText(msg, (Engine::CanvasWidth - (strlen(msg) * Engine::FontWidth)), 0);
}

//initialize rocket
void Player::Init()
{
	x = (Engine::CanvasWidth - Engine::SpriteSize) / 2;
}

//player position from keys input
void Player::Move(Engine::PlayerInput keys)
{
	
	if (keys.left)
	{
		--x;
		if (x < (~(Engine::SpriteSize) + 1))
			x = Engine::SpriteSize;
	}
	if (keys.right)
	{
		++x;
		if (x > Engine::CanvasWidth)
			x = Engine::CanvasWidth - Engine::SpriteSize;
	}

	engine->drawSprite(Engine::Sprite::Player, x, (Engine::CanvasHeight - Engine::SpriteSize));
}

void Player::Fire(Engine::PlayerInput keys)
{
	if (keys.fire && !fireKey)
	{
		fireKey = true;
		rocket->draw(x, (Engine::CanvasHeight - Engine::SpriteSize));
	}
	else if (!keys.fire)
		fireKey = false;
}

//check collision between bomb and player
//bomb boundary: X- [x1] - [x1+32]. Y- [y1] - [y1+32]
//player boundary: X- [x1-(32/2)] - [x1+32+(32/2)]. Y- [CanvasHeight-32-(32/2)] - [CanvasHeight]
void Player::Collision(Bomb* bomb, float timer)
{
	if (bomb->bombPos.size > 0 &&
		(bomb->bombPos.x[0] > (x - Engine::SpriteSize / 2)) &&
		((bomb->bombPos.x[0] + Engine::SpriteSize) < (x + Engine::SpriteSize + Engine::SpriteSize / 2)) &&
		(bomb->bombPos.y[0] > (Engine::CanvasHeight - Engine::SpriteSize - Engine::SpriteSize / 2)) &&
		((bomb->bombPos.y[0] + Engine::SpriteSize) < Engine::CanvasHeight))
	{
		playerKilled = true;
		killedLocation = x;// record time and position
		killedTime = timer;
		life -= 1;
		bomb->remove(0);
	}
}

//shows info when hit
void Player::displayInfo(float timer)
{
	if ((playerKilled) && (timer - killedTime) < 1)
	{
		engine->drawText("life -1", killedLocation, (Engine::CanvasHeight - (2 * Engine::SpriteSize)));
	}
	else if(playerKilled)
		playerKilled = false;	
}