#include "Game.hh"

#ifdef __linux__ 
#include <SDL2/SDL.h>
#elif _WIN32
#include <SDL.h>   
#endif




const units::FPS kFps{ 60 };
const auto kMaxFrameTime = std::chrono::milliseconds{ 5 * 1000 / 60 };
units::Tile Game::kScreenWidth{ 640 };
units::Tile Game::kScreenHeight{ 480 };


Game::Game() {
	
	runEventLoop();
}
Game::~Game() {
	SDL_Quit();
}


void Game::runEventLoop() {
	SDL_Event event;

	bool running = true;
	auto last_updated_time = std::chrono::high_resolution_clock::now();

	while (running)
	{
		using std::chrono::high_resolution_clock; // Class std::chrono::high_resolution_clock represents the clock with the smallest tick period
												 // provided by the implementation. It may be an alias of std::chrono::system_clock or std::chrono::steady_clock, or a third, independent clock.
		using std::chrono::milliseconds;
		using std::chrono::duration_cast;

		const auto start_time = high_resolution_clock::now();

		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE) {
					running = false;
				}
					
			default:
				break;
			}
		}

		// update the scene and last_updated_time
		const auto current_time = high_resolution_clock::now();
		const auto upd_elapsed_time = current_time - last_updated_time;

		
		// std::min Returns the smaller of the given values.

		// 1, 2) Returns the smaller of a and b.
		// 3, 4) Returns the smallest of the values in initializer list ilist.

		// duration_cast Converts a std::chrono::duration to a duration of different type ToDuration.
		update(std::min(duration_cast<milliseconds>(upd_elapsed_time),
			kMaxFrameTime),
			graphics_); 
		last_updated_time = current_time;

		draw(graphics_);

		// calculate delay for constant fps
		const auto end_time = high_resolution_clock::now();
		const auto elapsed_time = duration_cast<milliseconds>(end_time - start_time);

		const auto delay_duration = milliseconds(1000) / kFps - elapsed_time;
		if (delay_duration.count() >= 0)
			SDL_Delay(delay_duration.count());
	}
}

void Game::update(const std::chrono::milliseconds elapsed_time, Graphics& graphics)
{

}

void Game::draw(Graphics& graphics) const
{
	graphics.clear();
}


