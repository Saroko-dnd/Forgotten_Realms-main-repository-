#include "../headers/MENU.h"

#include "../../functions/headers/create_texture.h"
#include "../../GLOBALS/GLOBAL_VARIABLES.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <string>
#include <vector>
#include <iostream>
#include "../../functions/headers/load_menu_texts.h"
#include "../../functions/headers/load_path_names.h"
#include <Windows.h>
#include "../../functions/headers/load_music.h"
#include "../../functions/headers/load_screen_thread.h"
#include <ctime> 

//эта функция запускает необходимую функцию для обработки меню в конкретный момент
void MENU::menu_processing()
{
	SDL_GetMouseState(&mouse_x, &mouse_y);
	if (current_menu_id == MAIN_MENU)
		main_menu_processing();
	else if (current_menu_id == MENU_DIF_LEVEL)
		diff_levels_menu_processing();
	else if (current_menu_id == MENU_OPTIONS)
		options_menu_processing();
	else if (current_menu_id == MENU_SEX)
		sex_menu_processing();
	else if (current_menu_id == MENU_RACE_SELECTION)
		race_menu_processing();
	else if (current_menu_id == MENU_HERO_INFORMATION)
		list_of_selected_parameters_menu_processing();
}

bool MENU::quit_state()
{
	return quit;
}

//главное меню
void MENU::main_menu_processing()
{
	text our_texts;
	our_texts = load_texts_from_file(our_texts, path_name_list[0]);
	int check_mouse = -1, width_text, height_text;
	SDL_Rect srcrect_2;

	srcrect_2.x = 0;
	srcrect_2.y = 0;
	srcrect_2.w = 300;
	srcrect_2.h = 50;

	SDL_Rect dstrect_2;

	dstrect_2.x = (window_size_x - 300) / 2;
	dstrect_2.y = (window_size_y) / 5;
	dstrect_2.w = 300;
	dstrect_2.h = 50;

	SDL_RenderCopy(ren, main_picture_texture, NULL, NULL);

	//проверка на какой из кнопок меню находится мышь
	for (int counter = 1; counter <= our_texts.short_.size(); ++counter)
	{
		if (mouse_x > dstrect_2.x && mouse_x < (dstrect_2.x + 300) && mouse_y>dstrect_2.y + (60 * (counter - 1))
			&& mouse_y<(dstrect_2.y + 50) + (60 * (counter - 1)))
		{
			check_mouse += counter;
		}
	}

	//рисуем картинки для меню
	for (int counter = 0; counter < our_texts.short_.size(); ++counter)
	{
		SDL_RenderCopy(ren, current_menu, &srcrect_2, &dstrect_2);
		dstrect_2.y += 60;
	}
	dstrect_2.y = (window_size_y) / 5;

	//рисуем текст для меню
	for (int counter = 0; counter < our_texts.short_.size(); ++counter)
	{
		SDL_Surface* text_surface;
		if (counter == check_mouse)
			text_surface = TTF_RenderUNICODE_Blended(font, (Uint16*)our_texts.short_[counter].c_str(), Blue);
		else
			text_surface = TTF_RenderUNICODE_Blended(font, (Uint16*)our_texts.short_[counter].c_str(), White);
		if (text_surface == nullptr)
		{
			MessageBox(NULL,
				(LPCWSTR)L"Cant load text for current menu!",
				(LPCWSTR)L"Error!",
				MB_ICONWARNING | MB_OK
				);
		}
		else
		{
			TTF_SizeUNICODE(font, (Uint16*)our_texts.short_[counter].c_str(), &width_text, &height_text);
			SDL_Texture *text_texture = SDL_CreateTextureFromSurface(ren, text_surface);
			dstrect_2.x = ((300 - width_text) / 2) + (window_size_x - 300) / 2;
			dstrect_2.w = width_text;
			dstrect_2.h = height_text;
			SDL_RenderCopy(ren, text_texture, NULL, &dstrect_2);
			SDL_DestroyTexture(text_texture);
		}

		dstrect_2.y += 60;
		SDL_FreeSurface(text_surface);
	}

	while (SDL_PollEvent(&our_event))
	{
		//проверка нажатий клавиш мыши на пункты меню************************************************
		if (our_event.type == SDL_MOUSEBUTTONDOWN && our_event.button.button == SDL_BUTTON_LEFT)
		{
			if (check_mouse > -1)
				check_button_pressed = true;
		}
		if (check_mouse < 0)
		{
			check_button_pressed = false;
		}
		if (our_event.type == SDL_MOUSEBUTTONUP  && our_event.button.button == SDL_BUTTON_LEFT &&
			check_button_pressed && check_mouse == 3)
		{
			if (Mix_Playing(2) == 0 && sound_swi)
			{
				if (Mix_PlayChannel(2, click_wave, 0) == -1)
				{
					MessageBox(NULL,
						(LPCWSTR)L"click_sound_error",
						(LPCWSTR)L"Sound_error!",
						MB_ICONWARNING | MB_OK
						);
				}
			}
			quit = true;
		}
		if (our_event.type == SDL_MOUSEBUTTONUP  && our_event.button.button == SDL_BUTTON_LEFT &&
			check_button_pressed && check_mouse == 2)
		{
			if (Mix_Playing(2) == 0 && sound_swi)
			{
				if (Mix_PlayChannel(2, click_wave, 0) == -1)
				{
					MessageBox(NULL,
						(LPCWSTR)L"click_sound_error",
						(LPCWSTR)L"Sound_error!",
						MB_ICONWARNING | MB_OK
						);
				}
			}
			current_menu_id = MENU_OPTIONS;
		}
		if (our_event.type == SDL_MOUSEBUTTONUP  && our_event.button.button == SDL_BUTTON_LEFT &&
			check_button_pressed && check_mouse == 0)
		{
			if (Mix_Playing(2) == 0 && sound_swi)
			{
				if (Mix_PlayChannel(2, click_wave, 0) == -1)
				{
					MessageBox(NULL,
						(LPCWSTR)L"click_sound_error",
						(LPCWSTR)L"Sound_error!",
						MB_ICONWARNING | MB_OK
						);
				}
			}
			current_menu_id = MENU_DIF_LEVEL;
		}
		//******************************************************************************************
		if (our_event.type == SDL_QUIT){
			quit = true;
		}
	}

}

//меню выбора уровня сложности
void MENU::diff_levels_menu_processing()
{
	text our_texts;
	our_texts = load_texts_from_file(our_texts, path_name_list[1]);
	int check_mouse = -1, width_text, height_text;
	SDL_Rect srcrect_2;

	srcrect_2.x = 0;
	srcrect_2.y = 0;
	srcrect_2.w = 300;
	srcrect_2.h = 50;

	SDL_Rect dstrect_2;

	dstrect_2.x = (window_size_x - 300) / 2;
	dstrect_2.y = (window_size_y) / 5;
	dstrect_2.w = 300;
	dstrect_2.h = 50;

	SDL_RenderCopy(ren, main_picture_texture, NULL, NULL);

	//проверка на какой из кнопок меню находится мышь
	for (int counter = 1; counter <= our_texts.short_.size(); ++counter)
	{
		if (mouse_x > dstrect_2.x && mouse_x < (dstrect_2.x + 300) && mouse_y>dstrect_2.y + (60 * (counter - 1))
			&& mouse_y<(dstrect_2.y + 50) + (60 * (counter - 1)))
		{
			check_mouse += counter;
		}
	}

	//рисуем картинки для меню
	for (int counter = 0; counter < our_texts.short_.size(); ++counter)
	{
		SDL_RenderCopy(ren, current_menu, &srcrect_2, &dstrect_2);
		dstrect_2.y += 60;
	}
	dstrect_2.y = (window_size_y) / 5;

	//рисуем рамку для текста
	SDL_Rect dstrect;
	dstrect.x = 10;
	dstrect.y = dstrect_2.y;
	dstrect.w = (window_size_x - 340) / 2;
	dstrect.h = (window_size_y * 2) / 3;

	SDL_RenderCopy(ren, frame_texture, NULL, &dstrect);

	if (check_mouse > -1 && (check_mouse + 1) <= our_texts.long_.size())
	{
		SDL_Surface* text_surface_add;

		TTF_SizeUNICODE(font_add, (Uint16*)our_texts.long_[check_mouse].c_str(), &width_text, &height_text);
		text_surface_add = TTF_RenderUNICODE_Blended_Wrapped(font_add,
			(Uint16*)our_texts.long_[check_mouse].c_str(), White, dstrect.w);

		if (text_surface_add == nullptr)
		{
			MessageBox(NULL,
				(LPCWSTR)L"Cant load text for current menu!",
				(LPCWSTR)L"Error!",
				MB_ICONWARNING | MB_OK
				);
		}
		else
		{
			SDL_Texture *text_texture_add = SDL_CreateTextureFromSurface(ren, text_surface_add);
			dstrect.h = (width_text / dstrect.w)*(height_text + 3);
			SDL_RenderCopy(ren, text_texture_add, NULL, &dstrect);
			SDL_DestroyTexture(text_texture_add);
		}
	}

	//рисуем текст для меню
	for (int counter = 0; counter < our_texts.short_.size(); ++counter)
	{
		SDL_Surface* text_surface;
		if (counter == check_mouse)
			text_surface = TTF_RenderUNICODE_Blended(font, (Uint16*)our_texts.short_[counter].c_str(), Blue);
		else
			text_surface = TTF_RenderUNICODE_Blended(font, (Uint16*)our_texts.short_[counter].c_str(), White);
		if (text_surface == nullptr)
		{
			MessageBox(NULL,
				(LPCWSTR)L"Cant load text for current menu!",
				(LPCWSTR)L"Error!",
				MB_ICONWARNING | MB_OK
				);
		}
		else
		{
			TTF_SizeUNICODE(font, (Uint16*)our_texts.short_[counter].c_str(), &width_text, &height_text);
			SDL_Texture *text_texture = SDL_CreateTextureFromSurface(ren, text_surface);
			dstrect_2.x = ((300 - width_text) / 2) + (window_size_x - 300) / 2;
			dstrect_2.w = width_text;
			dstrect_2.h = height_text;
			SDL_RenderCopy(ren, text_texture, NULL, &dstrect_2);
			SDL_DestroyTexture(text_texture);
		}

		dstrect_2.y += 60;
		SDL_FreeSurface(text_surface);
	}

	while (SDL_PollEvent(&our_event))
	{
		//проверка нажатий клавиш мыши на пункты меню************************************************
		if (our_event.type == SDL_MOUSEBUTTONDOWN && our_event.button.button == SDL_BUTTON_LEFT)
		{
			if (check_mouse > -1)
				check_button_pressed = true;
		}
		if (check_mouse < 0)
		{
			check_button_pressed = false;
		}

		//выбор уровня сложности
		if (our_event.type == SDL_MOUSEBUTTONUP  && our_event.button.button == SDL_BUTTON_LEFT &&
			check_button_pressed && check_mouse == 0)
		{
			if (Mix_Playing(2) == 0 && sound_swi)
			{
				if (Mix_PlayChannel(2, click_wave, 0) == -1)
				{
					MessageBox(NULL,
						(LPCWSTR)L"click_sound_error",
						(LPCWSTR)L"Sound_error!",
						MB_ICONWARNING | MB_OK
						);
				}
			}
			main_multiplier = 0.75;
			current_menu_id = MENU_SEX;
		}
		if (our_event.type == SDL_MOUSEBUTTONUP  && our_event.button.button == SDL_BUTTON_LEFT &&
			check_button_pressed && check_mouse == 1)
		{
			if (Mix_Playing(2) == 0 && sound_swi)
			{
				if (Mix_PlayChannel(2, click_wave, 0) == -1)
				{
					MessageBox(NULL,
						(LPCWSTR)L"click_sound_error",
						(LPCWSTR)L"Sound_error!",
						MB_ICONWARNING | MB_OK
						);
				}
			}
			main_multiplier = 1.0;
			current_menu_id = MENU_SEX;
		}
		if (our_event.type == SDL_MOUSEBUTTONUP  && our_event.button.button == SDL_BUTTON_LEFT &&
			check_button_pressed && check_mouse == 2)
		{
			if (Mix_Playing(2) == 0 && sound_swi)
			{
				if (Mix_PlayChannel(2, click_wave, 0) == -1)
				{
					MessageBox(NULL,
						(LPCWSTR)L"click_sound_error",
						(LPCWSTR)L"Sound_error!",
						MB_ICONWARNING | MB_OK
						);
				}
			}
			main_multiplier = 1.25;
			current_menu_id = MENU_SEX;
		}

		if (our_event.type == SDL_MOUSEBUTTONUP  && our_event.button.button == SDL_BUTTON_LEFT &&
			check_button_pressed && check_mouse == 3)
		{
			if (Mix_Playing(2) == 0 && sound_swi)
			{
				if (Mix_PlayChannel(2, click_wave, 0) == -1)
				{
					MessageBox(NULL,
						(LPCWSTR)L"click_sound_error",
						(LPCWSTR)L"Sound_error!",
						MB_ICONWARNING | MB_OK
						);
				}
			}
			current_menu_id = MAIN_MENU;
		}
		//******************************************************************************************
		if (our_event.type == SDL_QUIT){
			quit = true;
		}
	}

}

//меню настроек
void MENU::options_menu_processing()
{
	text our_texts;
	our_texts = load_texts_from_file(our_texts, path_name_list[2]);
	int check_mouse = -1, width_text, height_text;
	SDL_Rect srcrect_2;

	srcrect_2.x = 0;
	srcrect_2.y = 0;
	srcrect_2.w = 300;
	srcrect_2.h = 50;

	SDL_Rect dstrect_2;

	dstrect_2.x = (window_size_x - 300) / 2;
	dstrect_2.y = (window_size_y) / 5;
	dstrect_2.w = 300;
	dstrect_2.h = 50;

	SDL_Rect dstrect_3;

	dstrect_3.x = ((window_size_x - 300) / 2)+350;
	dstrect_3.y = (window_size_y) / 5;
	dstrect_3.w = 100;
	dstrect_3.h = 50;

	SDL_RenderCopy(ren, main_picture_texture, NULL, NULL);

	//проверка на какой из кнопок меню находится мышь
	for (int counter = 1; counter <= our_texts.short_.size()/2; ++counter)
	{
		if (mouse_x > dstrect_3.x && mouse_x < (dstrect_3.x + 100) && mouse_y>dstrect_3.y + (60 * (counter - 1))
			&& mouse_y<(dstrect_3.y + 50) + (60 * (counter - 1)))
		{
			check_mouse += counter;
		}
	}
	if (mouse_x > dstrect_2.x && mouse_x < (dstrect_2.x + 300) && mouse_y>dstrect_2.y + 120
		&& mouse_y<(dstrect_2.y + 50) + 120)
	{
		check_mouse += 3;
	}

	//рисуем картинки для меню
	SDL_RenderCopy(ren, current_menu, &srcrect_2, &dstrect_2);
	dstrect_2.y += 60;
	SDL_RenderCopy(ren, current_menu, &srcrect_2, &dstrect_2);
	dstrect_2.y += 60;
	SDL_RenderCopy(ren, current_menu, &srcrect_2, &dstrect_2);
	dstrect_2.y = (window_size_y) / 5;
	SDL_RenderCopy(ren, current_menu, &srcrect_2, &dstrect_3);
	dstrect_3.y += 60;
	SDL_RenderCopy(ren, current_menu, &srcrect_2, &dstrect_3);
	dstrect_3.y = (window_size_y) / 5;

	//рисуем текст для меню
	for (int counter = 0; counter < our_texts.short_.size(); ++counter)
	{
		SDL_Surface* text_surface;
		if (counter <= 2)
		{
			if (counter == 2 && check_mouse == 2)
				text_surface = TTF_RenderUNICODE_Blended(font, (Uint16*)our_texts.short_[counter].c_str(), Blue);
			else
				text_surface = TTF_RenderUNICODE_Blended(font, (Uint16*)our_texts.short_[counter].c_str(), White);
		}
		if (counter == 3)
		{
			if (counter == (check_mouse + 3))
			{
				if (sound_swi)
					text_surface = TTF_RenderUNICODE_Blended(font, (Uint16*)our_texts.short_[3].c_str(), Blue);
				else
					text_surface = TTF_RenderUNICODE_Blended(font, (Uint16*)our_texts.short_[4].c_str(), Blue);
			}
			else
			{
				if (sound_swi)
					text_surface = TTF_RenderUNICODE_Blended(font, (Uint16*)our_texts.short_[3].c_str(), White);
				else
					text_surface = TTF_RenderUNICODE_Blended(font, (Uint16*)our_texts.short_[4].c_str(), White);
			}
		}
		if (counter == 4)
		{
			if (counter == (check_mouse + 3))
			{
				if (music_swi)
					text_surface = TTF_RenderUNICODE_Blended(font, (Uint16*)our_texts.short_[3].c_str(), Blue);
				else
					text_surface = TTF_RenderUNICODE_Blended(font, (Uint16*)our_texts.short_[4].c_str(), Blue);
			}
			else
			{
				if (music_swi)
					text_surface = TTF_RenderUNICODE_Blended(font, (Uint16*)our_texts.short_[3].c_str(), White);
				else
					text_surface = TTF_RenderUNICODE_Blended(font, (Uint16*)our_texts.short_[4].c_str(), White);
			}
		}
		if (text_surface == nullptr)
		{
			MessageBox(NULL,
				(LPCWSTR)L"Cant load text for current menu!",
				(LPCWSTR)L"Error!",
				MB_ICONWARNING | MB_OK
				);
		}
		else
		{
			if (counter <= 2)
				TTF_SizeUNICODE(font, (Uint16*)our_texts.short_[counter].c_str(), &width_text, &height_text);
			else
			{
				if (counter == 3)
				{
					if (sound_swi)
						TTF_SizeUNICODE(font, (Uint16*)our_texts.short_[3].c_str(), &width_text, &height_text);
					else
						TTF_SizeUNICODE(font, (Uint16*)our_texts.short_[4].c_str(), &width_text, &height_text);
				}
				if (counter == 4)
				{
					if (music_swi)
						TTF_SizeUNICODE(font, (Uint16*)our_texts.short_[3].c_str(), &width_text, &height_text);
					else
						TTF_SizeUNICODE(font, (Uint16*)our_texts.short_[4].c_str(), &width_text, &height_text);
				}
			}
			SDL_Texture *text_texture = SDL_CreateTextureFromSurface(ren, text_surface);
			if (counter > 2)
				dstrect_2.x = ((window_size_x - 300) / 2) + 360;
			else
				dstrect_2.x = ((300 - width_text) / 2) + (window_size_x - 300) / 2;
			dstrect_2.w = width_text;
			dstrect_2.h = height_text;
			SDL_RenderCopy(ren, text_texture, NULL, &dstrect_2);
			SDL_DestroyTexture(text_texture);
		}
		if (counter != 2)
			dstrect_2.y += 60;
		else
			dstrect_2.y = (window_size_y) / 5;
		SDL_FreeSurface(text_surface);
	}

	click_option = 0;

	while (SDL_PollEvent(&our_event))
	{
		//проверка нажатий клавиш мыши на пункты меню************************************************
		if (our_event.type == SDL_MOUSEBUTTONDOWN && our_event.button.button == SDL_BUTTON_LEFT)
		{
			if (check_mouse > -1)
				check_button_pressed = true;
		}
		if (check_mouse < 0)
		{
			check_button_pressed = false;
		}

		//выбор уровня сложности
		if (our_event.type == SDL_MOUSEBUTTONUP  && our_event.button.button == SDL_BUTTON_LEFT &&
			check_button_pressed && check_mouse == 0)
		{
			click_option = 1;
			if (sound_swi)
			{
				sound_swi = false;
			}
			else
			{
				sound_swi = true;
			}
			if (Mix_Playing(2) == 0 && sound_swi)
			{
				if (Mix_PlayChannel(2, click_wave, 0) == -1)
				{
					MessageBox(NULL,
						(LPCWSTR)L"click_sound_error",
						(LPCWSTR)L"Sound_error!",
						MB_ICONWARNING | MB_OK
						);
				}
			}
		}
		if (our_event.type == SDL_MOUSEBUTTONUP  && our_event.button.button == SDL_BUTTON_LEFT &&
			check_button_pressed && check_mouse == 1)
		{
			click_option = 2;
			if (music_swi)
			{
				music_swi = false;
				Mix_Pause(1);//блокирование проигрывание звуков на канале 1
			}
			else
			{
				music_swi = true;
				Mix_Resume(1);//разблокирование проигрывание звуков на канале 1
			}
			if (Mix_Playing(2) == 0 && sound_swi)
			{
				if (Mix_PlayChannel(2, click_wave, 0) == -1)
				{
					MessageBox(NULL,
						(LPCWSTR)L"click_sound_error",
						(LPCWSTR)L"Sound_error!",
						MB_ICONWARNING | MB_OK
						);
				}
			}
		}
		if (our_event.type == SDL_MOUSEBUTTONUP  && our_event.button.button == SDL_BUTTON_LEFT &&
			check_button_pressed && check_mouse == 2)
		{
			
			if (Mix_Playing(2) == 0 && sound_swi)
			{
				if (Mix_PlayChannel(2, click_wave, 0) == -1)
				{
					MessageBox(NULL,
						(LPCWSTR)L"click_sound_error",
						(LPCWSTR)L"Sound_error!",
						MB_ICONWARNING | MB_OK
						);
				}
			}
			current_menu_id = MAIN_MENU;
		}
		//******************************************************************************************
		if (our_event.type == SDL_QUIT){
			quit = true;
		}
	}

}

void MENU::sex_menu_processing()
{
	unsigned int start_time = clock(); // начальное время

	text our_texts;
	our_texts = load_texts_from_file(our_texts, path_name_list[3]);

	int check_mouse = -1, width_text, height_text;
	SDL_Rect srcrect_2;

	srcrect_2.x = 0;
	srcrect_2.y = 0;
	srcrect_2.w = 300;
	srcrect_2.h = 50;

	SDL_Rect dstrect_2;

	dstrect_2.x = (window_size_x - 300) / 2;
	dstrect_2.y = (window_size_y) / 5;
	dstrect_2.w = 300;
	dstrect_2.h = 50;

	SDL_RenderCopy(ren, main_picture_texture, NULL, NULL);

	//проверка на какой из кнопок меню находится мышь
	for (int counter = 1; counter <= (our_texts.short_.size() - 1); ++counter)
	{
		if (mouse_x > dstrect_2.x && mouse_x < (dstrect_2.x + 300) && mouse_y>dstrect_2.y + (60 * (counter - 1))
			&& mouse_y<(dstrect_2.y + 50) + (60 * (counter - 1)))
		{
			check_mouse += counter;
		}
	}

	//рисуем картинки для меню**************************************************
	for (int counter = 0; counter < (our_texts.short_.size() - 1); ++counter)
	{
		SDL_RenderCopy(ren, current_menu, &srcrect_2, &dstrect_2);
		dstrect_2.y += 60;
	}

	dstrect_2.y = ((window_size_y) / 5) - 60;
	dstrect_2.x = ((window_size_x - 300) / 2) - 150;
	dstrect_2.w = 600;
	SDL_RenderCopy(ren, information_element, NULL, &dstrect_2);
	//**************************************************************************

	//рисуем текст для меню
	for (int counter = 0; counter < our_texts.short_.size(); ++counter)
	{
		SDL_Surface* text_surface;
		if ((counter - 1) == check_mouse && (counter -1) != -1)
			text_surface = TTF_RenderUNICODE_Blended(font, (Uint16*)our_texts.short_[counter].c_str(), Blue);
		else
			text_surface = TTF_RenderUNICODE_Blended(font, (Uint16*)our_texts.short_[counter].c_str(), White);
		if (text_surface == nullptr)
		{
			MessageBox(NULL,
				(LPCWSTR)L"Cant load text for current menu!",
				(LPCWSTR)L"Error!",
				MB_ICONWARNING | MB_OK
				);
		}
		else
		{
			TTF_SizeUNICODE(font, (Uint16*)our_texts.short_[counter].c_str(), &width_text, &height_text);
			SDL_Texture *text_texture = SDL_CreateTextureFromSurface(ren, text_surface);
			if (counter != 0)
			{
				dstrect_2.x = ((300 - width_text) / 2) + (window_size_x - 300) / 2;
			}
			else
			{
				dstrect_2.x = ((600 - width_text) / 2) + (((window_size_x - 300) / 2)-150);
			}
			dstrect_2.w = width_text;
			dstrect_2.h = height_text;

			SDL_RenderCopy(ren, text_texture, NULL, &dstrect_2);
			SDL_DestroyTexture(text_texture);
		}

		dstrect_2.y += 60;
		SDL_FreeSurface(text_surface);
	}

	while (SDL_PollEvent(&our_event))
	{
		//проверка нажатий клавиш мыши на пункты меню************************************************
		if (our_event.type == SDL_MOUSEBUTTONDOWN && our_event.button.button == SDL_BUTTON_LEFT)
		{
			if (check_mouse > -1)
				check_button_pressed = true;
		}
		if (check_mouse < 0)
		{
			check_button_pressed = false;
		}
		if (our_event.type == SDL_MOUSEBUTTONUP  && our_event.button.button == SDL_BUTTON_LEFT &&
			check_button_pressed && check_mouse == 0)
		{
			if (Mix_Playing(2) == 0 && sound_swi)
			{
				if (Mix_PlayChannel(2, click_wave, 0) == -1)
				{
					MessageBox(NULL,
						(LPCWSTR)L"click_sound_error",
						(LPCWSTR)L"Sound_error!",
						MB_ICONWARNING | MB_OK
						);
				}
			}
			//добавляем в список текстуру, содержащую выбранную характеристику для персонажа в текстовом виде
			//start
			text_with_size buf_struct;
			SDL_Surface* text_surface_add;
			text_surface_add = TTF_RenderUNICODE_Blended_Wrapped(small_font_add,
				(Uint16*)L"пол: мужской", White, NULL);
			TTF_SizeUNICODE(small_font_add, (Uint16*)L"пол: мужской", &buf_struct.width_text,
				&buf_struct.height_text);
			if (text_surface_add == nullptr)
			{
				MessageBox(NULL,
					(LPCWSTR)L"Cant load text for current menu!",
					(LPCWSTR)L"Error!",
					MB_ICONWARNING | MB_OK
					);
			}
			else
			{
				buf_struct.texture = SDL_CreateTextureFromSurface(ren, text_surface_add);
				textures_of_texts_for_list_of_main_character.push_back(buf_struct);
				SDL_FreeSurface(text_surface_add);
			}
			//end
			current_hero_information.male = true;
			current_menu_id = MENU_HERO_INFORMATION;
			prev_menu_id = MENU_SEX;
			next_menu_id = MENU_RACE_SELECTION;
		}
		if (our_event.type == SDL_MOUSEBUTTONUP  && our_event.button.button == SDL_BUTTON_LEFT &&
			check_button_pressed && check_mouse == 1)
		{
			if (Mix_Playing(2) == 0 && sound_swi)
			{
				if (Mix_PlayChannel(2, click_wave, 0) == -1)
				{
					MessageBox(NULL,
						(LPCWSTR)L"click_sound_error",
						(LPCWSTR)L"Sound_error!",
						MB_ICONWARNING | MB_OK
						);
				}
			}

			//добавляем в список текстуру, содержащую выбранную характеристику для персонажа в текстовом виде
			//start
			text_with_size buf_struct;
			SDL_Surface* text_surface_add;
			text_surface_add = TTF_RenderUNICODE_Blended_Wrapped(small_font_add,
				(Uint16*)L"пол: женский", White, NULL);
			TTF_SizeUNICODE(small_font_add, (Uint16*)L"пол: женский", &buf_struct.width_text,
				&buf_struct.height_text);
			if (text_surface_add == nullptr)
			{
				MessageBox(NULL,
					(LPCWSTR)L"Cant load text for current menu!",
					(LPCWSTR)L"Error!",
					MB_ICONWARNING | MB_OK
					);
			}
			else
			{
				buf_struct.texture = SDL_CreateTextureFromSurface(ren, text_surface_add);
				textures_of_texts_for_list_of_main_character.push_back(buf_struct);
				SDL_FreeSurface(text_surface_add);
			}
			//end

			current_hero_information.male = false;
			current_menu_id = MENU_HERO_INFORMATION;
			prev_menu_id = MENU_SEX;
			next_menu_id = MENU_RACE_SELECTION;
		}
		if (our_event.type == SDL_MOUSEBUTTONUP  && our_event.button.button == SDL_BUTTON_LEFT &&
			check_button_pressed && check_mouse == 2)
		{
			if (Mix_Playing(2) == 0 && sound_swi)
			{
				if (Mix_PlayChannel(2, click_wave, 0) == -1)
				{
					MessageBox(NULL,
						(LPCWSTR)L"click_sound_error",
						(LPCWSTR)L"Sound_error!",
						MB_ICONWARNING | MB_OK
						);
				}
			}

			current_menu_id = MENU_DIF_LEVEL;
		}
		//******************************************************************************************
		if (our_event.type == SDL_QUIT){
			quit = true;
		}
	}
	unsigned int end_time = clock(); // конечное время
	unsigned int search_time = end_time - start_time;
	end_time = 0;
}

void MENU::race_menu_processing()
{
	int check_mouse = -1, width_text, height_text;

	SDL_Rect srcrect_2;

	srcrect_2.x = 0;
	srcrect_2.y = 0;
	srcrect_2.w = 300;
	srcrect_2.h = 50;

	SDL_Rect dstrect_2;

	dstrect_2.x = (window_size_x - 300) / 2;
	dstrect_2.y = ((window_size_y) / 5) - 60;
	dstrect_2.w = 300;
	dstrect_2.h = 50;

	SDL_RenderCopy(ren, main_picture_texture, NULL, NULL);

	//проверка на какой из кнопок меню находится мышь
	for (int counter = 1; counter <= (race_texts.short_.size() - 1); ++counter)
	{
		if (mouse_x > dstrect_2.x && mouse_x < (dstrect_2.x + 300) && mouse_y>dstrect_2.y + (60 * (counter - 1))
			&& mouse_y<(dstrect_2.y + 50) + (60 * (counter - 1)))
		{
			check_mouse += counter;
		}
	}

	//рисуем картинки для меню**************************************************
	for (int counter = 0; counter < (race_texts.short_.size() - 3); ++counter)
	{
		SDL_RenderCopy(ren, current_menu, &srcrect_2, &dstrect_2);
		dstrect_2.y += 60;
	}

	dstrect_2.y = ((window_size_y) / 5) - 120;
	dstrect_2.x = ((window_size_x - 300) / 2) - 150;
	dstrect_2.w = 600;
	SDL_RenderCopy(ren, information_element, NULL, &dstrect_2);

	SDL_Rect dstrect_info;
	dstrect_info.x = 10;
	dstrect_info.y = dstrect_2.y + 60;
	dstrect_info.w = (window_size_x - 340) / 2;
	dstrect_info.h = 50;

	SDL_RenderCopy(ren, information_element, NULL, &dstrect_info);
	dstrect_info.x = ((window_size_x - 300) / 2) + 310;
	SDL_RenderCopy(ren, information_element, NULL, &dstrect_info);

	//рисуем текст для меню

	for (int counter = 0; counter < race_texts.short_.size(); ++counter)
	{
		SDL_Surface* text_surface;
		if ((counter - 3) == check_mouse && (counter - 3) != -1)
		{
			text_surface = TTF_RenderUNICODE_Blended(font, (Uint16*)race_texts.short_[counter].c_str(), Blue);
		}
		else
		{
			text_surface = TTF_RenderUNICODE_Blended(font, (Uint16*)race_texts.short_[counter].c_str(), White);
		}
		if (text_surface == nullptr)
		{
			MessageBox(NULL,
				(LPCWSTR)L"Cant load text for current menu!",
				(LPCWSTR)L"Error!",
				MB_ICONWARNING | MB_OK
				);
		}
		else
		{
			TTF_SizeUNICODE(font, (Uint16*)race_texts.short_[counter].c_str(), &width_text, &height_text);
			SDL_Texture *text_texture = SDL_CreateTextureFromSurface(ren, text_surface);
			if (counter > 2)
			{
				dstrect_2.x = ((300 - width_text) / 2) + (window_size_x - 300) / 2;
			}
			else
			{
				if (counter == 0)
					dstrect_2.x = ((600 - width_text) / 2) + (((window_size_x - 300) / 2) - 150);
				else if (counter == 1)
					dstrect_2.x = (((window_size_x - 340) / 4) +10) - (width_text / 2);
				else if (counter == 2)
					dstrect_2.x = ((window_size_x - 300) / 2) + 310 + ((window_size_x - 340) / 4) - (width_text / 2);
			}
			dstrect_2.w = width_text;
			dstrect_2.h = height_text;
			SDL_RenderCopy(ren, text_texture, NULL, &dstrect_2);
			SDL_DestroyTexture(text_texture);
		}
		if (counter == 0 || counter > 2)
			dstrect_2.y += 60;
		SDL_FreeSurface(text_surface);
	}

	dstrect_2.y = (window_size_y) / 5;
	dstrect_2.x = (window_size_x - 300) / 2;

	SDL_Rect dstrect;
	dstrect.x = 10;
	dstrect.y = dstrect_2.y;
	dstrect.w = (window_size_x - 340) / 2;
	dstrect.h = ((window_size_y * 2) / 3) + 55;

	SDL_RenderCopy(ren, frame_texture, NULL, &dstrect);
	dstrect.x = dstrect_2.x + 310;
	SDL_RenderCopy(ren, frame_texture, NULL, &dstrect);


	if (check_mouse > -1 && check_mouse <= 6)
	{
			int counter = 0;
			for (int number = check_mouse; number > 0; --number)
			{
				counter += 2;
			}

			dstrect.h = (large_texts[counter].width_text / dstrect.w)*(large_texts[counter].height_text + 10);
			dstrect.x = 10;
			SDL_RenderCopy(ren, large_texts[counter].texture, NULL, &dstrect);
			if (check_mouse != 3)
				dstrect.h = (large_texts[counter + 1].width_text / dstrect.w)*(large_texts[counter + 1].height_text + 15);
			else
				dstrect.h = (large_texts[counter + 1].width_text / dstrect.w)*(large_texts[counter + 1].height_text + 20);
			dstrect.x = dstrect_2.x + 310;
			SDL_RenderCopy(ren, large_texts[counter + 1].texture, NULL, &dstrect);
	}

	while (SDL_PollEvent(&our_event))
	{
		if (our_event.type == SDL_QUIT)
		{
			quit = true;
		}
		if (our_event.type == SDL_MOUSEBUTTONDOWN && our_event.button.button == SDL_BUTTON_LEFT)
		{
			if (check_mouse > -1)
				check_button_pressed = true;
		}
		if (check_mouse < 0)
		{
			check_button_pressed = false;
		}
		if (our_event.type == SDL_MOUSEBUTTONUP  && our_event.button.button == SDL_BUTTON_LEFT &&
			check_button_pressed && check_mouse == 7)
		{
			if (Mix_Playing(2) == 0 && sound_swi)
			{
				if (Mix_PlayChannel(2, click_wave, 0) == -1)
				{
					MessageBox(NULL,
						(LPCWSTR)L"click_sound_error",
						(LPCWSTR)L"Sound_error!",
						MB_ICONWARNING | MB_OK
						);
				}
			}
			current_menu_id = MENU_HERO_INFORMATION;
			next_menu_id = MENU_RACE_SELECTION;
			prev_menu_id = MENU_SEX;
		}
	}
}

void MENU::list_of_selected_parameters_menu_processing()
{
	int check_mouse = -1, width_text, height_text;

	text our_texts;
	our_texts = load_texts_from_file(our_texts, path_name_list[5]);

	SDL_Rect srcrect_2;

	srcrect_2.x = 0;
	srcrect_2.y = 0;
	srcrect_2.w = 300;
	srcrect_2.h = 50;

	SDL_Rect dstrect_2;

	dstrect_2.x = (window_size_x - 300) / 2;
	dstrect_2.y = window_size_y - 120;
	dstrect_2.w = 300;
	dstrect_2.h = 50;

	SDL_RenderCopy(ren, main_picture_texture, NULL, NULL);

	//проверка на какой из кнопок меню находится мышь
	for (int counter = 1; counter <= (our_texts.short_.size() - 1); ++counter)
	{
		if (mouse_x > dstrect_2.x && mouse_x < (dstrect_2.x + 300) && mouse_y>dstrect_2.y + (60 * (counter - 1))
			&& mouse_y<(dstrect_2.y + 50) + (60 * (counter - 1)))
		{
			check_mouse += counter;
		}
	}

	//рисуем картинки для меню**************************************************
	for (int counter = 0; counter < (our_texts.short_.size() - 1); ++counter)
	{
		SDL_RenderCopy(ren, current_menu, &srcrect_2, &dstrect_2);
		dstrect_2.y += 60;
	}

	dstrect_2.x = (window_size_x - 600)/2;
	dstrect_2.y = 10;
	dstrect_2.w = 600;
	dstrect_2.h = 50;

	SDL_RenderCopy(ren, information_element, NULL, &dstrect_2);

	//отрисовка кнопок и заголовка
	for (int counter = 0; counter < our_texts.short_.size(); ++counter)
	{
		SDL_Surface* text_surface;
		if (counter == 0)
		{
			text_surface = TTF_RenderUNICODE_Blended(font, (Uint16*)our_texts.short_[counter].c_str(), White);
		}
		else
		{
			if ((counter - 1) == check_mouse)
			{
				text_surface = TTF_RenderUNICODE_Blended(font, (Uint16*)our_texts.short_[counter].c_str(), Blue);
			}
			else
			{
				text_surface = TTF_RenderUNICODE_Blended(font, (Uint16*)our_texts.short_[counter].c_str(), White);
			}
		}
		if (text_surface == nullptr)
		{
			MessageBox(NULL,
				(LPCWSTR)L"Cant load text for current menu!",
				(LPCWSTR)L"Error!",
				MB_ICONWARNING | MB_OK
				);
		}
		else
		{
			TTF_SizeUNICODE(font, (Uint16*)our_texts.short_[counter].c_str(), &width_text, &height_text);
			SDL_Texture *text_texture = SDL_CreateTextureFromSurface(ren, text_surface);
			if (counter == 0)
			{
				dstrect_2.y = 10;
				dstrect_2.x = ((600 - width_text) / 2) + (window_size_x - 600) / 2;
			}
			else
			{
				dstrect_2.y = window_size_y - (60*(2/counter));
				dstrect_2.x = ((300 - width_text) / 2) + (window_size_x - 300) / 2;
			}
			dstrect_2.w = width_text;
			dstrect_2.h = height_text;
			SDL_RenderCopy(ren, text_texture, NULL, &dstrect_2);
			SDL_DestroyTexture(text_texture);
		}
		SDL_FreeSurface(text_surface);
	}

	dstrect_2.x = (window_size_x - 800) / 2;
	dstrect_2.y = 70;
	dstrect_2.w = 800;
	dstrect_2.h = 700;

	SDL_RenderCopy(ren, frame_texture, NULL, &dstrect_2);

	int space_between_lines = 3;
	for (int counter = 0; counter < textures_of_texts_for_list_of_main_character.size(); ++counter)
	{
		dstrect_2.w = textures_of_texts_for_list_of_main_character[counter].width_text;
		dstrect_2.h = textures_of_texts_for_list_of_main_character[counter].height_text;
		SDL_RenderCopy(ren, textures_of_texts_for_list_of_main_character[counter].texture, NULL, &dstrect_2);
		dstrect_2.y += dstrect_2.h + space_between_lines;
	}

	while (SDL_PollEvent(&our_event))
	{
		//проверка нажатий клавиш мыши на пункты меню************************************************
		if (our_event.type == SDL_MOUSEBUTTONDOWN && our_event.button.button == SDL_BUTTON_LEFT)
		{
			if (check_mouse > -1)
				check_button_pressed = true;
		}
		if (check_mouse < 0)
		{
			check_button_pressed = false;
		}
		if (our_event.type == SDL_MOUSEBUTTONUP  && our_event.button.button == SDL_BUTTON_LEFT &&
			check_button_pressed && check_mouse == 0)
		{
			if (Mix_Playing(2) == 0 && sound_swi)
			{
				if (Mix_PlayChannel(2, click_wave, 0) == -1)
				{
					MessageBox(NULL,
						(LPCWSTR)L"click_sound_error",
						(LPCWSTR)L"Sound_error!",
						MB_ICONWARNING | MB_OK
						);
				}
			}
			current_menu_id = next_menu_id;
		}
		if (our_event.type == SDL_MOUSEBUTTONUP  && our_event.button.button == SDL_BUTTON_LEFT &&
			check_button_pressed && check_mouse == 1)
		{
			if (Mix_Playing(2) == 0 && sound_swi)
			{
				if (Mix_PlayChannel(2, click_wave, 0) == -1)
				{
					MessageBox(NULL,
						(LPCWSTR)L"click_sound_error",
						(LPCWSTR)L"Sound_error!",
						MB_ICONWARNING | MB_OK
						);
				}
			}
			current_menu_id = prev_menu_id;
			//удаляем последний элемент из списка характеристик персонажа (отмена)
			textures_of_texts_for_list_of_main_character.pop_back();
		}
		//******************************************************************************************
		if (our_event.type == SDL_QUIT){
			quit = true;
		}
	}
}

hero_information MENU::get_hero_information()
{
	return current_hero_information;
}

MENU::MENU(SDL_Renderer * new_ren)
{
	White = { 255, 255, 255 };
	Blue = { 0, 0, 255 };
	path_name_list = load_path_names_function();
	font = TTF_OpenFont("C:/windows/fonts/Arial.ttf", 30);
	font_add = TTF_OpenFont("C:/windows/fonts/Arial.ttf", 30);
	small_font_add = TTF_OpenFont("C:/windows/fonts/Arial.ttf", 15);
	TTF_SetFontOutline(font, 1);
	TTF_SetFontOutline(font_add, 1);
	ren = new_ren;
	current_menu = create_texture_function(ren, L"images/menu_images/MENU_basic_element.png");
	information_element = create_texture_function(ren, L"images/menu_images/MENU_information_element.png");
	main_picture_texture = create_texture_function(ren, L"images/menu_images/main_picture.png");
	frame_texture = create_texture_function(ren, L"images/menu_images/large_frame_for_text.png");
	quit = false;
	sound_swi = true;
	music_swi = true;
	check_button_pressed = false;
	current_menu_id = MAIN_MENU;
	click_wave = NULL;
	click_wave = load_music_function(L"sound_files/sounds/click_sound.ogg");
	click_option = 0;
	race_selector_text_load_swi = true;
	race_texts = load_texts_from_file(race_texts, path_name_list[4]);
	//загружаем заранее большие куски текста
	SDL_Rect dstrect;
	dstrect.x = 10;
	dstrect.y = (window_size_y) / 5;
	dstrect.w = (window_size_x - 340) / 2;
	dstrect.h = ((window_size_y * 2) / 3) + 55;

	text_with_size left_text;
	text_with_size right_text;

	text our_texts;
	our_texts = load_texts_from_file(our_texts, path_name_list[4]);
	SDL_Color White = { 255, 255, 255 };
	for (int counter = 0; counter <= 6; ++counter)
	{
			SDL_Surface* text_surface_add;
			SDL_Surface* text_surface_add_right;
			TTF_SizeUNICODE(small_font_add, (Uint16*)our_texts.long_[counter].c_str(), &left_text.width_text,
				&left_text.height_text);
			TTF_SizeUNICODE(small_font_add, (Uint16*)our_texts.long_[counter + 7].c_str(),
				&right_text.width_text, &right_text.height_text);
			text_surface_add = TTF_RenderUNICODE_Blended_Wrapped(small_font_add,
				(Uint16*)our_texts.long_[counter].c_str(), White, dstrect.w);
			text_surface_add_right = TTF_RenderUNICODE_Blended_Wrapped(small_font_add,
				(Uint16*)our_texts.long_[counter + 7].c_str(), White, dstrect.w);
			if (text_surface_add == nullptr || text_surface_add_right == nullptr)
			{
				MessageBox(NULL,
					(LPCWSTR)L"Cant load text for current menu!",
					(LPCWSTR)L"Error!",
					MB_ICONWARNING | MB_OK
					);
			}
			else
			{
				SDL_Texture *text_texture_add = SDL_CreateTextureFromSurface(ren, text_surface_add);
				left_text.texture = text_texture_add;
				large_texts.push_back(left_text);
				SDL_Texture *text_texture_add_right = SDL_CreateTextureFromSurface(ren, text_surface_add_right);
				right_text.texture = text_texture_add_right;
				large_texts.push_back(right_text);
				SDL_FreeSurface(text_surface_add);
				SDL_FreeSurface(text_surface_add_right);
			}
	}
	//конец загрузки текста
}	


MENU::~MENU()
{
	SDL_DestroyTexture(current_menu);
	SDL_DestroyTexture(information_element);
	SDL_DestroyTexture(main_picture_texture);
	SDL_DestroyTexture(frame_texture);
	for (int counter = 0; counter < textures_of_texts_for_list_of_main_character.size(); ++counter)
	{
		SDL_DestroyTexture(textures_of_texts_for_list_of_main_character[counter].texture);
	}
	Mix_FreeChunk(click_wave);
}
