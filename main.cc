#ifdef __linux__ 
   #include <SDL2/SDL.h>
#elif _WIN32
   #include <SDL.h>   
#endif

#include "Game.hh"



int main(int argc, char* argv[]) {

	//SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Hello world", "Successful", NULL);
	
	Game game;

	return 0;
}
