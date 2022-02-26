#include "Engine.h"
#include "Alien.h"
#include "Bomb.h"
#include "Player.h"
#include "Rocket.h"
#include <cstring>
#include <string>

void EngineMain()
{
	Engine engine;
	Bomb bomb(&engine);
	Rocket rocket(&engine);
	Alien alien(&engine, &bomb);	
	Player player(&engine, &rocket);
	
	/////////////////////////////////////////////////////////////////
	//                     Start Screen                           //
	////////////////////////////////////////////////////////////////

	while (engine.startFrame())
	{
		//shows some infomation on the screen
		const char msg_1[] = "INVADERS ARE COMING!";
		engine.drawText(
			msg_1,
			(Engine::CanvasWidth - (sizeof(msg_1) - 1) * Engine::FontWidth) / 2,
			(Engine::CanvasHeight - Engine::FontRowHeight) / 2);

		const char msg_2[] = "Press SPACE to start";
		engine.drawText(
			msg_2,
			(Engine::CanvasWidth - (sizeof(msg_2) - 1) * Engine::FontWidth) / 2,
			(Engine::CanvasHeight - Engine::FontRowHeight + 6 * Engine::FontRowHeight) / 2);

		//Press SPACE to enter game
		Engine::PlayerInput keys = engine.getPlayerInput();
		if (keys.fire)		
			break;		
	}

	float lastTime = (float)engine.getStopwatchElapsedSeconds();
	
	//initilize bomb, rocket, alien, player 
	bomb.Init();	
	rocket.Init();
	alien.Init();
	player.Init();

	//////////////////////////////////////////////////////////////////
	//                     Game Screen                              //
	//////////////////////////////////////////////////////////////////
	
	while (engine.startFrame())
	{
		//get system time and objects moving speed based on system time
		float newTime = (float)engine.getStopwatchElapsedSeconds();
		float move = (newTime - lastTime) * 160.f;
		lastTime = newTime;

		//show and update player score and life
		player.showScore();
		player.showLife();
		
		//update alien position and check the alien reaching bottom
		alien.Move(move);
		alien.checkBottom();

		//create bomb based on alien position
		alien.dropBomb(newTime);
		
		//real-time refresh alien and bomb positon
		alien.Refresh();
		bomb.Refreash(move);

		//update player position and create rocket from keys input
		Engine::PlayerInput keys = engine.getPlayerInput();
		player.Move(keys);
		player.Fire(keys);

		//update rocket postion
		rocket.Move(move);

		//check the collision between player and bomb, alien and rocket, shows information when player hit by bomb
		player.Collision(&bomb, newTime);
		player.displayInfo(newTime);
		alien.Collision(&rocket, &player);

		//check game over condition
		if (alien.allAlienKilled || (player.life == 0) || alien.reachBottom)
		{
			player.life = 3;
			alien.reachBottom = false;
			alien.allAlienKilled = false;
			break;
		}		
	}

	//////////////////////////////////////////////////////////////////
	//                     Game Over Screen                         //
	//////////////////////////////////////////////////////////////////

	while (engine.startFrame())
	{
		//shows some infomation on the screen
		const char msg_1[] = "GAME OVER!";
		engine.drawText(
			msg_1,
			(Engine::CanvasWidth - (sizeof(msg_1) - 1) * Engine::FontWidth) / 2,
			(Engine::CanvasHeight - Engine::FontRowHeight) / 2);

		std::string message = "Score: " + std::to_string(player.score);
		const char* msg_2 = message.c_str();		
		engine.drawText(
			msg_2,
			(Engine::CanvasWidth - Engine::FontWidth) / 2 + 8,
			(Engine::CanvasHeight - Engine::FontRowHeight + 6 * Engine::FontRowHeight) / 2);			
	}	
}



