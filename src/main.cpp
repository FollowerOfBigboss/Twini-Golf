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
	game.InitiazeSdlAndModules();
	game.InitiliazeGameWindow();
	game.InitGameAssets();
	game.loadLevel(game.level);
	
	while (game.gameRunning)
	{
		game.game();
	}

	game.cleanup();
	return 0;
}