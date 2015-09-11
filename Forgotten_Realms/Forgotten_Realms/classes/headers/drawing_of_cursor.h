#pragma once

#include <SDL.h>
#include <vector>

//класс рисующий игровой курсор
class cursor
{
private:
	std::vector<SDL_Texture *> textures_for_cursor;
	SDL_Renderer *ren;
	SDL_Rect dstrect;
public:
	void get_coordinates(int, int);
	void draw_cursor();
	void destroy_textures();
	cursor(SDL_Renderer *);
	cursor(const cursor &old_object);
};