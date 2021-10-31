#pragma once
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "Entity.h"


class RenderWindow 
{
public:
	RenderWindow() {};
	RenderWindow(const std::string& p_title, int p_w, int p_h);
	void init(const std::string& p_title, int p_w, int p_h);

	SDL_Texture* loadTexture(const std::string& p_filePath);
	void cleanUp();
	void clear();
	void render(Entity& p_entity);
	void render(int x, int y, SDL_Texture* p_tex);
	void render(float p_x, float p_y, const std::string& p_string, TTF_Font* font, SDL_Color textColor);
	void renderCenter(float p_x, float p_y, const std::string& p_string, TTF_Font* font, SDL_Color textColor);
	void display();
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
};