#include "../headers/drawing_of_cursor.h"

#include "../../functions/headers/create_texture.h"
#include <SDL.h>
#include <vector>
#include <Windows.h>

void cursor::get_coordinates(int new_x, int new_y)
{
	dstrect.x = new_x;
	dstrect.y = new_y;
}

void cursor::draw_cursor()
{
	SDL_RenderCopy(ren, textures_for_cursor[0], NULL, &dstrect);
}

void cursor::destroy_textures()
{
	for (int counter = 0; counter < textures_for_cursor.size(); ++counter)
	{
		SDL_DestroyTexture(textures_for_cursor[counter]);
	}
}

cursor::cursor(SDL_Renderer * new_render)
{
	dstrect.x = 0;
	dstrect.y = 0;
	dstrect.w = 33;
	dstrect.h = 31;
	ren = new_render;
	textures_for_cursor.push_back(create_texture_function(ren, L"images/cursors/my_cursor.png"));
}

cursor::cursor(const cursor &origin_object)
{
	dstrect = origin_object.dstrect;
	ren = origin_object.ren;
	textures_for_cursor = origin_object.textures_for_cursor;
}