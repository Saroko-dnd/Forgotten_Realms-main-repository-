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
	int mouse_x, mouse_y;
	bool sound_swi;
	bool music_swi;
	bool quit;
	bool check_button_pressed;
	bool race_selector_text_load_swi;
	Mix_Chunk *click_wave;
	SDL_Texture * current_menu;
	SDL_Texture * information_element;
	SDL_Event our_event;
	TTF_Font *font;
	TTF_Font *font_add;
	TTF_Font *small_font_add;
	SDL_Renderer *ren;
	std::vector<SDL_Texture *> very_long_texts_storage;
	float main_multiplier;//множитель параметров (зависит от выбранного уровня сложности)
	std::vector<std::wstring> path_name_list;

	void main_menu_processing();
	void diff_levels_menu_processing();
	void options_menu_processing();
	void sex_menu_processing();
	void race_menu_processing();
public:
	void menu_processing();
	hero_information get_hero_information();
	bool quit_state();
	MENU(SDL_Renderer *);
	~MENU();
};

