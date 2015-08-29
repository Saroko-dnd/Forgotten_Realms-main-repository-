#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <sstream>

void logSDLError(const std::string &msg)
{
	std::cout << msg << " error: " << SDL_GetError() << std::endl;
}

SDL_Texture* create_texture(const std::string &file, SDL_Renderer *ren)
{
	SDL_Texture *texture = nullptr;
	SDL_Surface *loadedImage = IMG_Load(file.c_str());
	if (loadedImage != nullptr)
	{
		texture = SDL_CreateTextureFromSurface(ren, loadedImage);
		SDL_FreeSurface(loadedImage);
		if (texture == nullptr)
		{
			logSDLError("CreateTextureFromSurface");
		}
	}
	else 
	{
		logSDLError("Load_image");
	}
	return texture;
}

void render_texture(SDL_Texture *current_texture, SDL_Renderer *ren, int x_1, int y_1, int w_1, int h_1,int x_2, int y_2, int w_2, int h_2)
{
	SDL_Rect srcrect;
	SDL_Rect dstrect;

	srcrect.x = x_1;
	srcrect.y = y_1;
	srcrect.w = w_1;
	srcrect.h = h_1;

	dstrect.x = x_2;
	dstrect.y = y_2;
	dstrect.w = w_2;
	dstrect.h = h_2;

	SDL_RenderCopy(ren, current_texture, &srcrect, &dstrect);
}
