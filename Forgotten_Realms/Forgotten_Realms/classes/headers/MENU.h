#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <vector>
#include <string>
#include "../../GLOBALS/GLOBAL_VARIABLES.h"

class MENU
{
private:
	hero_information current_hero_information;
	int click_option;
	int current_menu_id;
	//количество меню которое игрок уже прошел в процессе создания своего персонажа (сюда входят только меню
	//в которых игрок определяет характеристики и другие особенности своего персонажа)
	int number_of_passed_menu = 0;
	//текстуры с текстом для списка того, что игрок уже выбрал для своего персонажа при его создании
	std::vector<text_with_size> textures_of_texts_for_list_of_main_character;
	//id меню на которое нужно переключиться по кнопке (назад) в 
	//list_of_selected_parameters_menu_processing
	int prev_menu_id;
	//id меню на которое нужно переключиться по кнопке (далее) в 
	//list_of_selected_parameters_menu_processing
	int next_menu_id;

	bool sound_swi;
	bool music_swi;
	bool quit;
	bool check_button_pressed;
	bool race_selector_text_load_swi;

	std::vector<text_with_size> large_texts;
	Mix_Chunk *click_wave;
	SDL_Texture * current_menu;
	SDL_Texture * information_element;
	SDL_Texture * main_picture_texture;
	//тестура-окно для больших описаний
	SDL_Texture * frame_texture;
	SDL_Event our_event;
	SDL_Color White;
	SDL_Color Blue;
	TTF_Font *font;
	TTF_Font *font_add;
	TTF_Font *small_font_add;
	SDL_Renderer *ren;
	std::vector<SDL_Texture *> very_long_texts_storage;
	float main_multiplier;//множитель параметров (зависит от выбранного уровня сложности)
	std::vector<std::wstring> path_name_list;
	text race_texts;

	void main_menu_processing();
	void diff_levels_menu_processing();
	void options_menu_processing();
	void sex_menu_processing();
	void race_menu_processing();
	void list_of_selected_parameters_menu_processing();
public:
	int mouse_x, mouse_y;
	void menu_processing();
	hero_information get_hero_information();
	bool quit_state();
	MENU(SDL_Renderer *);
	~MENU();
};

