#pragma once

#include <SDL.h>
//возвращает текстуру изображения, находящегося по заданному пути для заданного рендера
SDL_Texture* create_texture_function(SDL_Renderer *, const wchar_t*);

