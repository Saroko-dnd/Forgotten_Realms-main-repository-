#include "../headers/create_texture.h"

#include <SDL.h>
#include <SDL_image.h>
#include <Windows.h>
#include <stdlib.h>

SDL_Texture* create_texture_function(SDL_Renderer * ren, const wchar_t* path_name)
{
	char buf[255];
	if (wcstombs(buf, path_name, sizeof(buf)) == 255)
		buf[254] = '\0';

	SDL_Surface *surface_for_texture = IMG_Load(buf);
	if (surface_for_texture == nullptr)
	{
		MessageBox(NULL,
			(LPCWSTR)path_name,
			(LPCWSTR)L"Cant load file!",
			MB_ICONWARNING | MB_OK
			);
	}
	SDL_Texture *current_texture=nullptr;
	if (surface_for_texture != nullptr)
	{
		current_texture = SDL_CreateTextureFromSurface(ren, surface_for_texture);
		if (current_texture == nullptr)
		{
			MessageBox(NULL,
				(LPCWSTR)path_name,
				(LPCWSTR)L"Cant load file!",
				MB_ICONWARNING | MB_OK
				);
		}
	}

	SDL_FreeSurface(surface_for_texture);

	return current_texture;
}
