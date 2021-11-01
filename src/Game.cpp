#include "Game.h"

#define check_asset_load(asset) if (asset == nullptr) return false;

Game::Game()
{
	gameRunning = true;
	mouseDown = false;
	mousePressed = false;
	
	swingPlayed = false;
	secondSwingPlayed = false;
	
	state = 0; //0 = title screen, 1 = game, 2 = end screen
	level = 0;
	currentTick = 0;
	lastTick = 0;
	deltaTime = 0;

	currentTick = SDL_GetPerformanceCounter();
}

bool Game::InitiazeSdlAndModules()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cout << "HEY.. SDL_Init HAS FAILED. SDL_ERROR: " << SDL_GetError() << "\n";
		return false;
	}

	int flags = IMG_INIT_PNG;
	int initted = IMG_Init(flags);
	if ((initted & flags) != flags)
	{
		std::cout << "IMG_init has failed. Error: " << IMG_GetError() << "\n";
		return false;
	}

	if (TTF_Init() == -1)
	{
		std::cout << "TTF_init has failed. Error: " << TTF_GetError() << "\n";
		return false;
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
	{
		std::cout << "Mix_OpenAudio has failed. Error: " << Mix_GetError() << "\n";
		return false;
	}

	return true;
}

bool Game::InitiliazeGameWindow(const std::string& title, int w, int h)
{
	return window.init(title, w, h);
}

bool Game::InitGameAssets()
{
	ballTexture = window.loadTexture("res/gfx/ball.png");
	check_asset_load(ballTexture);

	holeTexture = window.loadTexture("res/gfx/hole.png");
	check_asset_load(holeTexture);

	pointTexture = window.loadTexture("res/gfx/point.png");
	check_asset_load(pointTexture);

	tileDarkTexture32 = window.loadTexture("res/gfx/tile32_dark.png");
	check_asset_load(tileDarkTexture32);

	tileDarkTexture64 = window.loadTexture("res/gfx/tile64_dark.png");
	check_asset_load(tileDarkTexture64);

	tileLightTexture32 = window.loadTexture("res/gfx/tile32_light.png");
	check_asset_load(tileLightTexture32);

	tileLightTexture64 = window.loadTexture("res/gfx/tile64_light.png");
	check_asset_load(tileLightTexture64);

	ballShadowTexture = window.loadTexture("res/gfx/ball_shadow.png");
	check_asset_load(ballShadowTexture);

	bgTexture = window.loadTexture("res/gfx/bg.png");
	check_asset_load(bgTexture);

	uiBgTexture = window.loadTexture("res/gfx/UI_bg.png");
	check_asset_load(uiBgTexture);

	levelTextBgTexture = window.loadTexture("res/gfx/levelText_bg.png");
	check_asset_load(levelTextBgTexture);

	powerMeterTexture_FG = window.loadTexture("res/gfx/powermeter_fg.png");
	check_asset_load(powerMeterTexture_FG);

	powerMeterTexture_BG = window.loadTexture("res/gfx/powermeter_bg.png");
	check_asset_load(powerMeterTexture_BG);

	powerMeterTexture_overlay = window.loadTexture("res/gfx/powermeter_overlay.png");
	check_asset_load(powerMeterTexture_overlay);

	logoTexture = window.loadTexture("res/gfx/logo.png");
	check_asset_load(logoTexture);

	click2start = window.loadTexture("res/gfx/click2start.png");
	check_asset_load(click2start);

	endscreenOverlayTexture = window.loadTexture("res/gfx/end.png");
	check_asset_load(endscreenOverlayTexture);

	splashBgTexture = window.loadTexture("res/gfx/splashBg.png");
	check_asset_load(splashBgTexture);

	chargeSfx = Mix_LoadWAV("res/sfx/charge.mp3");
	check_asset_load(chargeSfx);

	swingSfx = Mix_LoadWAV("res/sfx/swing.mp3");
	check_asset_load(swingSfx);

	holeSfx = Mix_LoadWAV("res/sfx/hole.mp3");
	check_asset_load(holeSfx);

	font32 = TTF_OpenFont("res/font/font.ttf", 32);
	check_asset_load(font32);

	font48 = TTF_OpenFont("res/font/font.ttf", 48);
	check_asset_load(font48);

	font24 = TTF_OpenFont("res/font/font.ttf", 24);
	check_asset_load(font24);

	loadTiles(level);

	balls[0] =  new Ball(Vector2f(0, 0), ballTexture, pointTexture, powerMeterTexture_FG, powerMeterTexture_BG, 0);
	balls[1] = new Ball(Vector2f(0, 0), ballTexture, pointTexture, powerMeterTexture_FG, powerMeterTexture_BG, 1);
	
	holes.push_back(Hole(Vector2f(0, 0), holeTexture));
	
	holes.push_back(Hole(Vector2f(0, 0), holeTexture));

	return true;
}

void Game::loadLevel(int level)
{
	if (level > 4)
	{
		state = 2;
		return;
	}
	balls[0]->setVelocity(0, 0);
	balls[1]->setVelocity(0, 0);
	balls[0]->setScale(1, 1);
	balls[1]->setScale(1, 1);
	balls[0]->setWin(false);
	balls[1]->setWin(false);

	loadTiles(level);

	switch (level)
	{
	case 0:
		balls[0]->setPos(24 + 32 * 4, 24 + 32 * 11);
		balls[1]->setPos(24 + 32 * 4 + 32 * 10, 24 + 32 * 11);

		holes.at(0).setPos(24 + 32 * 4, 22 + 32 * 2);
		holes.at(1).setPos(24 + 32 * 4 + 32 * 10, 22 + 32 * 2);
		break;
	case 1:
		balls[0]->setPos(24 + 32 * 4, 24 + 32 * 11);
		balls[1]->setPos(24 + 32 * 4 + 32 * 10, 24 + 32 * 11);

		holes.at(0).setPos(24 + 32 * 4, 22 + 32 * 2);
		holes.at(1).setPos(24 + 32 * 4 + 32 * 10, 22 + 32 * 2);
		break;
	case 2:
		balls[0]->setPos(8 + 32 * 7, 8 + 32 * 10);
		balls[1]->setPos(8 + 32 * 7 + 32 * 10, 8 + 32 * 10);

		holes.at(0).setPos(8 + 32 * 2, 6 + 32 * 5);
		holes.at(1).setPos(8 + 32 * 4 + 32 * 10, 6 + 32 * 3);
		break;
	case 3:
		balls[0]->setPos(24 + 32 * 4, 24 + 32 * 5);
		balls[1]->setPos(24 + 32 * 4 + 32 * 10, 24 + 32 * 4);

		holes.at(0).setPos(24 + 32 * 4, 22 + 32 * 1);
		holes.at(1).setPos(24 + 32 * 4 + 32 * 10, 22 + 32 * 11);
		break;
	case 4:
		balls[0]->setPos(24 + 32 * 2, 24 + 32 * 12);
		balls[1]->setPos(24 + 32 * 0 + 32 * 10, 24 + 32 * 5);

		holes.at(0).setPos(24 + 32 * 1, 22 + 32 * 1);
		holes.at(1).setPos(24 + 32 * 0 + 32 * 10, 22 + 32 * 7);
		break;
	}
}

void Game::game()
{
	if (state == 0)
	{
		titleScreen();
	}
	else
	{
		update();
		graphics();
	}
}

void Game::cleanup()
{
	window.cleanup();

	SDL_DestroyTexture(ballTexture);
	SDL_DestroyTexture(holeTexture);
	SDL_DestroyTexture(pointTexture);
	SDL_DestroyTexture(tileDarkTexture32);
	SDL_DestroyTexture(tileDarkTexture64);
	SDL_DestroyTexture(tileLightTexture32);
	SDL_DestroyTexture(tileLightTexture64);
	SDL_DestroyTexture(ballShadowTexture);
	SDL_DestroyTexture(bgTexture);
	SDL_DestroyTexture(uiBgTexture);
	SDL_DestroyTexture(levelTextBgTexture);
	SDL_DestroyTexture(powerMeterTexture_FG);
	SDL_DestroyTexture(powerMeterTexture_BG);
	SDL_DestroyTexture(powerMeterTexture_overlay);
	SDL_DestroyTexture(logoTexture);
	SDL_DestroyTexture(click2start);
	SDL_DestroyTexture(endscreenOverlayTexture);
	SDL_DestroyTexture(splashBgTexture);

	Mix_FreeChunk(chargeSfx);
	Mix_FreeChunk(swingSfx);
	Mix_FreeChunk(holeSfx);

	TTF_CloseFont(font32);
	TTF_CloseFont(font48);
	TTF_CloseFont(font24);

	delete balls[0];
	delete balls[1];

	holes.clear();
	holes.shrink_to_fit();

	tiles.clear();
	tiles.shrink_to_fit();

	TTF_Quit();
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}

void Game::loadTiles(int level)
{
	std::vector<Tile> temp = {};
	tiles.clear();
	tiles.shrink_to_fit();

	switch (level)
	{
	case 0:
		tiles.push_back(Tile(Vector2f(64 * 3, 64 * 3), tileDarkTexture64));
		tiles.push_back(Tile(Vector2f(64 * 4, 64 * 3), tileDarkTexture64));
		
		tiles.push_back(Tile(Vector2f(64 * 0, 64 * 3), tileDarkTexture64));
		tiles.push_back(Tile(Vector2f(64 * 1, 64 * 3), tileDarkTexture64));
		
		tiles.push_back(Tile(Vector2f(64 * 3 + 64 * 5, 64 * 3), tileLightTexture64));
		tiles.push_back(Tile(Vector2f(64 * 4 + 64 * 5, 64 * 3), tileLightTexture64));
		
		tiles.push_back(Tile(Vector2f(64 * 0 + 64 * 5, 64 * 3), tileLightTexture64));
		tiles.push_back(Tile(Vector2f(64 * 1 + 64 * 5, 64 * 3), tileLightTexture64));
		break;
	case 1:
		tiles.push_back(Tile(Vector2f(64 * 2, 64 * 3), tileDarkTexture64));
		tiles.push_back(Tile(Vector2f(64 * 4 + 64 * 5, 64 * 3), tileLightTexture64));
		break;
	case 2:
		tiles.push_back(Tile(Vector2f(32 * 1 + 32 * 10 + 16, 32 * 5), tileLightTexture32));

		break;
	case 3:
		tiles.push_back(Tile(Vector2f(32 * 4, 32 * 7), tileDarkTexture64));
		tiles.push_back(Tile(Vector2f(32 * 3, 32 * 5), tileDarkTexture32));
		tiles.push_back(Tile(Vector2f(32 * 6, 32 * 3), tileDarkTexture32));

		tiles.push_back(Tile(Vector2f(32 * 4 + 64 * 5, 32 * 2), tileLightTexture64));
		tiles.push_back(Tile(Vector2f(32 * 3 + 32 * 10, 32 * 6), tileLightTexture32));
		tiles.push_back(Tile(Vector2f(32 * 6 + 32 * 10, 32 * 9), tileLightTexture32));

		break;
	case 4:
		tiles.push_back(Tile(Vector2f(32 * 3, 32 * 1), tileDarkTexture32));
		tiles.push_back(Tile(Vector2f(32 * 1, 32 * 3), tileDarkTexture32));
		tiles.push_back(Tile(Vector2f(32 * 5, 32 * 3), tileDarkTexture32));
		tiles.push_back(Tile(Vector2f(32 * 3, 32 * 5), tileDarkTexture32));
		tiles.push_back(Tile(Vector2f(32 * 7, 32 * 5), tileDarkTexture32));
		tiles.push_back(Tile(Vector2f(32 * 7, 32 * 10), tileDarkTexture32));
		tiles.push_back(Tile(Vector2f(32 * 3, 32 * 10), tileDarkTexture32));
		tiles.push_back(Tile(Vector2f(32 * 5, 32 * 12), tileDarkTexture32));
		tiles.push_back(Tile(Vector2f(32 * 7, 32 * 10), tileDarkTexture32));

		//temp.push_back(Tile(Vector2f(32*4, 32*7), tileDarkTexture64));
		tiles.push_back(Tile(Vector2f(32 * 8, 32 * 7), tileDarkTexture64));
		 
		tiles.push_back(Tile(Vector2f(32 * 2 + 32 * 10, 32 * 2), tileLightTexture32));
		tiles.push_back(Tile(Vector2f(32 * 5 + 32 * 10, 32 * 11), tileLightTexture32));
		 
		tiles.push_back(Tile(Vector2f(32 * 3 + 32 * 10, 32 * 1), tileLightTexture64));
		tiles.push_back(Tile(Vector2f(32 * 8 + 32 * 10, 32 * 6), tileLightTexture64));
		tiles.push_back(Tile(Vector2f(32 * 3 + 32 * 10, 32 * 11), tileLightTexture64));

		break;
	}
}

std::string Game::getStrokeText()
{
	int biggestStroke = 0;
	if (balls[1]->getStrokes() > balls[0]->getStrokes())
	{
		biggestStroke = balls[1]->getStrokes();
	}
	else
	{
		biggestStroke = balls[0]->getStrokes();
	}
	std::string s = std::to_string(biggestStroke);
	s = "STROKES: " + s;
	return s;
}

std::string Game::getLevelText(int side)
{
	int tempLevel = (level + 1) * 2 - 1;
	if (side == 1)
	{
		tempLevel++;
	}
	std::string s = std::to_string(tempLevel);
	s = "HOLE: " + s;
	return s;
}

void Game::update()
{
	lastTick = currentTick;
	currentTick = SDL_GetPerformanceCounter();
	deltaTime = (double)((currentTick - lastTick) * 1000 / (double)SDL_GetPerformanceFrequency());

	mousePressed = false;
	//Get our controls and events
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			gameRunning = false;
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				mouseDown = true;
				mousePressed = true;
			}
			break;
		case SDL_MOUSEBUTTONUP:
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				mouseDown = false;
			}
			break;

#	ifdef __ANDROID__
		case SDL_FINGERDOWN:
		{
			mouseDown = true;
			mousePressed = true;
		}
		case SDL_FINGERUP:
		{
			mouseDown = false;
		}

#	endif
		}
	}
	mouseDown = (SDL_GetGlobalMouseState(NULL, NULL) & SDL_BUTTON_LMASK) & mouseDown;

	if (state == 1)
	{
		for (Ball* b : balls)
		{
			b->update(deltaTime, mouseDown, mousePressed, tiles, holes, chargeSfx, swingSfx, holeSfx);
		}
		if (balls[0]->getScale().x < -1 && balls[1]->getScale().x < -1)
		{
			level++;
			loadLevel(level);
		}
	}
}

void Game::graphics()
{
	window.clear();
	window.render(0, 0, bgTexture);
	for (Hole& h : holes)
	{
		window.render(h);
	}
	for (Ball* b : balls)
	{
		if (!b->isWin())
		{
			window.render(b->getPos().x, b->getPos().y + 4, ballShadowTexture);
		}
		for (Entity& e : b->getPoints())
		{
			window.render(e);
		}
		window.render(*b);
	}
	for (Tile& t : tiles)
	{
		window.render(t);
	}
	for (Ball* b : balls)
	{
		for (Entity& e : b->getPowerBar())
		{
			window.render(e);
		}
		window.render(b->getPowerBar().at(0).getPos().x, b->getPowerBar().at(0).getPos().y, powerMeterTexture_overlay);

	}
	if (state != 2)
	{
		window.render(640 / 4 - 132 / 2, 480 - 32, levelTextBgTexture);
		window.renderCenter(-160, 240 - 16 + 3, getLevelText(0), font24, black);
		window.renderCenter(-160, 240 - 16, getLevelText(0), font24, white);

		window.render(640 / 2 + 640 / 4 - 132 / 2, 480 - 32, levelTextBgTexture);
		window.renderCenter(160, 240 - 16 + 3, getLevelText(1), font24, black);
		window.renderCenter(160, 240 - 16, getLevelText(1), font24, white);

		window.render(640 / 2 - 196 / 2, 0, uiBgTexture);
		window.renderCenter(0, -240 + 16 + 3, getStrokeText(), font24, black);
		window.renderCenter(0, -240 + 16, getStrokeText(), font24, white);
	}
	else
	{
		window.render(0, 0, endscreenOverlayTexture);
		window.renderCenter(0, 3 - 32, "YOU COMPLETED THE COURSE!", font48, black);
		window.renderCenter(0, -32, "YOU COMPLETED THE COURSE!", font48, white);
		window.renderCenter(0, 3 + 32, getStrokeText(), font32, black);
		window.renderCenter(0, 32, getStrokeText(), font32, white);
	}
	window.display();
}

void Game::titleScreen()
{
	if (SDL_GetTicks() < 2000)
	{
		if (!swingPlayed)
		{
			Mix_PlayChannel(-1, swingSfx, 0);
			swingPlayed = true;
		}
		//Get our controls and events
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				gameRunning = false;
				break;
			}
		}

		window.clear();
		window.render(0, 0, bgTexture);
		window.render(0, 0, splashBgTexture);
		window.renderCenter(0, 0 + 3, "POLYMARS", font32, black);
		window.renderCenter(0, 0, "POLYMARS", font32, white);
		window.display();
	}
	else
	{
		if (!secondSwingPlayed)
		{
			Mix_PlayChannel(-1, swingSfx, 0);
			secondSwingPlayed = true;
		}
		lastTick = currentTick;
		currentTick = SDL_GetPerformanceCounter();
		deltaTime = (double)((currentTick - lastTick) * 1000 / (double)SDL_GetPerformanceFrequency());

		//Get our controls and events
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				gameRunning = false;
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (event.button.button == SDL_BUTTON_LEFT)
				{
					Mix_PlayChannel(-1, holeSfx, 0);
					state = 1;
				}
				break;
			}
		}
		window.clear();
		window.render(0, 0, bgTexture);
		window.render(320 - 160, 240 - 100 - 50 + 4 * SDL_sin(SDL_GetTicks() * (3.14 / 1500)), logoTexture);
		window.render(0, 0, click2start);
		window.renderCenter(0, 240 - 48 + 3 - 16 * 5, "LEFT CLICK TO START", font32, black);
		window.renderCenter(0, 240 - 48 - 16 * 5, "LEFT CLICK TO START", font32, white);
		window.display();
	}
}

