#include <memory>

#include "RenderWindow.h"
#include "Entity.h"
#include "Ball.h"	
#include "Tile.h"
#include "Hole.h"

class Game
{
public:
	Game();
	bool InitiazeSdlAndModules();
	bool InitiliazeGameWindow(const std::string& title, int w, int h);
	bool InitGameAssets();


	void loadLevel(int level);
	void game();
	void cleanup();

	int level;
	bool gameRunning;

private:

	void loadTiles(int level);
	std::string getStrokeText();
	std::string getLevelText(int side);

	void update();
	void graphics();
	void titleScreen();

	RenderWindow window;

	// Textures
	SDL_Texture* ballTexture;
	SDL_Texture* holeTexture;
	SDL_Texture* pointTexture;
	SDL_Texture* tileDarkTexture32;
	SDL_Texture* tileDarkTexture64;
	SDL_Texture* tileLightTexture32;
	SDL_Texture* tileLightTexture64;
	SDL_Texture* ballShadowTexture;
	SDL_Texture* bgTexture;
	SDL_Texture* uiBgTexture;
	SDL_Texture* levelTextBgTexture;
	SDL_Texture* powerMeterTexture_FG;
	SDL_Texture* powerMeterTexture_BG;
	SDL_Texture* powerMeterTexture_overlay;
	SDL_Texture* logoTexture;
	SDL_Texture* click2start;
	SDL_Texture* endscreenOverlayTexture;
	SDL_Texture* splashBgTexture;

	// Sfxs
	Mix_Chunk* chargeSfx;
	Mix_Chunk* swingSfx;
	Mix_Chunk* holeSfx;

	// Colors
	const SDL_Color white = { 255, 255, 255 };
	const SDL_Color black = { 0, 0, 0 };

	// Fonts
	TTF_Font* font32;
	TTF_Font* font48;
	TTF_Font* font24;

	// Game Objects
	Ball* balls[2];
	std::vector<Hole> holes;
	
	// Tile textures
	std::vector<Tile> tiles;

	// Mouse states
	bool mouseDown;
	bool mousePressed;

	bool swingPlayed;
	bool secondSwingPlayed;
	// Game state
	int state;

	// Tick stuff
	Uint64 currentTick;
	Uint64 lastTick;
	double deltaTime;
	
	// unimportant sdl event structure
	SDL_Event event;
};