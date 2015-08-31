
#include "../headers/load_screen_thread.h"

#include <SDL.h>

void loading_screen_function(SDL_Renderer * ren, SDL_Texture * current_screen)
{
	SDL_RenderClear(ren);
	SDL_RenderCopy(ren, current_screen, NULL, NULL);
	SDL_Delay(100);
	SDL_RenderPresent(ren);
}