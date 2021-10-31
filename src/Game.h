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
	void InitiliazeGameWindow();
	void InitGameAssets();


	void loadLevel(int level);
	void game();
	void cleanup();

	int level;
	bool gameRunning;

private:

	std::vector<Tile> loadTiles(int level);
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

	// Color
	SDL_Color white;
	SDL_Color black;

	// Fonts
	TTF_Font* font32;
	TTF_Font* font48;
	TTF_Font* font24;

	Ball* balls[2];
	std::vector<Hole> holes;

	std::vector<Tile> tiles;
	bool mouseDown;
	bool mousePressed;

	bool swingPlayed;
	bool secondSwingPlayed;
	SDL_Event event;

	int state;
	Uint64 currentTick;
	Uint64 lastTick;
	double deltaTime;
};