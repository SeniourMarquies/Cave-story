#pragma once

#ifdef __linux__ 
#include <SDL2/SDL.h>
#elif _WIN32
#include <SDL.h>   
#endif



#include <map>
#include <string>

#include "units.hh"

struct Graphics
{
	Graphics();
	~Graphics();

	Graphics(const Graphics&) = delete;
	Graphics& operator=(const Graphics&) = delete;

	SDL_Texture* loadImage(const std::string& file_name,
		const bool black_is_transparent = false);

	void renderTexture(SDL_Texture* tex, const SDL_Rect dst, const SDL_Rect* clip = nullptr)const;

	void renderTexture(SDL_Texture* tex, const int x, const int y, const SDL_Rect* clip = nullptr) const;

	void flip() const;
	void clear() const;

private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	std::map<std::string, SDL_Texture*> sprite_sheets_;
};
