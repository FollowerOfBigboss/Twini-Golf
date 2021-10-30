#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Math.h"

class Entity
{
public:
	Entity(Vector2f p_pos, SDL_Texture* p_tex);
	inline Vector2f& getPos() { return pos; }
	inline float getAngle() const { return angle; }
	inline Vector2f getScale() const { return scale; }

	void setPos(float x, float y);
	void setScale(float w, float h);
	void setAngle(float angle);

	inline SDL_Texture* getTex() const { return tex; }
	inline SDL_Rect getCurrentFrame() const { return currentFrame; }
private:
	Vector2f pos;
	float angle = 0;
	Vector2f scale = Vector2f(1, 1);
	SDL_Rect currentFrame;
	SDL_Texture* tex;
};