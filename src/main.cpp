#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <vector>
#include <string>

#include "Game.h"

int main(int argc, char* args[])
{
	Game game;
	if (game.InitiazeSdlAndModules() != true)
	{
		std::cout << "Initialization of SDL or SDL libraries are failed.\n";
		return 1;
	}

	if (game.InitiliazeGameWindow("Twini-Golf", 640, 480) != true)
	{
		return 1;
	}

	if (game.InitGameAssets() != true)
	{
		std::cout << "Asset loading failed!" << "\n";
		return 1;
	}

	game.loadLevel(game.level);
	
	while (game.gameRunning)
	{
		game.game();
	}

	// Optinal
	game.cleanup();
	return 0;
}