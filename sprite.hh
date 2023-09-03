#pragma once

#ifdef __linux__ 
#include <SDL2/SDL.h>
#elif _WIN32
#include <SDL.h>   
#endif

#include <chrono>
#include <string>
#include "vector.hh"
#include "units.hh"


struct Graphics;


struct Sprite
{
	Sprite(Graphics& graphics, const std::string& file_name, const units::Pixel source_x, const units::Pixel source_y,
		const units::Pixel width, const units::Pixel height);

	virtual ~Sprite() = default;

	Sprite(const Sprite&) = delete;
	Sprite& operator=(const Sprite&) = delete;

	virtual void update(){}
	void draw(Graphics& graphics, const Vector<units::Game>& pos) const;

private:
	SDL_Texture* texture;


protected:
	SDL_Rect source_rect;
};

