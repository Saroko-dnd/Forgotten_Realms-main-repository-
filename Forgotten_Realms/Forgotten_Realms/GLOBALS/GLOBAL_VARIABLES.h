#pragma once

#include <vector>
#include <string>
#include <SDL.h>

const int window_size_x = 1000;
const int window_size_y = 900;

//макросы для меню
#define MAIN_MENU 1
#define MENU_DIF_LEVEL 2
#define MENU_OPTIONS 3
#define MENU_SEX 4
#define MENU_RACE_SELECTION 5

typedef struct text
{
	std::vector<std::wstring> short_;
	std::vector<std::wstring> long_;
}text;

typedef struct load_screen_info
{
	SDL_Renderer * render;
	SDL_Texture * texture;
}load_screen_info;

typedef struct text_with_size
{
	SDL_Texture * texture;
	int width_text;
	int height_text;
}text_with_size;

typedef struct hero_information
{
	bool male;
	int race;

	int strength;
	int dexterity;
	int constitution;
	int wisdom;
	int charisma;
	int intelligence;
	//основные мод-ры спасбросков.
	int save_will;
	int save_react;
	int save_endurance;
	//вспомогательные мод-ры спасбросков.
	int save_poison;
}hero_information;