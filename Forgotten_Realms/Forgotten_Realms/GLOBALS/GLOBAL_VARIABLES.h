#pragma once

#include <vector>
#include <string>
#include <SDL.h>
//размер окна игры по оси x
const int window_size_x = 1000;
//размер окна игры по оси y
const int window_size_y = 900;

//макросы для меню
#define MAIN_MENU 1
#define MENU_DIF_LEVEL 2
#define MENU_OPTIONS 3
#define MENU_SEX 4
#define MENU_RACE_SELECTION 5
#define MENU_HERO_INFORMATION -1

//структура для хранения загруженных из файла текстов
typedef struct text
{
	//вектор хранящий короткие тексты
	std::vector<std::wstring> short_;
	//вектор хранящий длинные тексты
	std::vector<std::wstring> long_;
}text;
//структура в которой содержится информация для передачи в функцию-поток загрузочного экрана
typedef struct load_screen_info
{
	//куда рендерить загрузочное изображение
	SDL_Renderer * render;
	//изображение для экрана загрузки
	SDL_Texture * texture;
}load_screen_info;
//структура в которой хранятся текстуры с большим количеством текста и их размеры для рендеринга
typedef struct text_with_size
{
	//текстура с текстом
	SDL_Texture * texture;
	//ширина текстуры
	int width_text;
	//высота текстуры
	int height_text;
}text_with_size;
//содержит в себе всю информацию о персонаже игрока
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