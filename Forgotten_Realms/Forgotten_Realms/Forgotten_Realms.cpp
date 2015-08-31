#include <iostream>
#include <ctime>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <vector>
#include <cstdio>
#include <string>
#include "classes/headers/MENU.h"
#include "GLOBALS/GLOBAL_VARIABLES.h"
#include <Windows.h>
#include "functions/headers/load_music.h"
#include "functions/headers/create_texture.h"
#include "functions/headers/load_screen_thread.h"

using namespace std;

bool end_of_menu_loading = false;

static int loading_screen_Thread(void* current_info)
{
	load_screen_info* current_information = (load_screen_info*)current_info;
	while (!end_of_menu_loading)
	{
		loading_screen_function(current_information->render, current_information->texture);
	}
	return 1;
}

int main(int argc, char*argv[])
{  

	int result_of_thread = -1;

	srand(time(NULL));

	//получаем разрешение экрана
	int x_size_of_monitor, y_size_of_monitor;
	float main_multiplier = 0.0;
	x_size_of_monitor = GetSystemMetrics(SM_CXSCREEN);
	y_size_of_monitor = GetSystemMetrics(SM_CYSCREEN);
	cout << x_size_of_monitor << "\n" << y_size_of_monitor;

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	if (TTF_Init() != 0)
	{
		cout << "TTF_Init Error: " << SDL_GetError() << endl;
		return 1;
	}

	SDL_Window *win = SDL_CreateWindow("Textures test", 100, 100, window_size_x, window_size_y, SDL_WINDOW_SHOWN);
	if (win == nullptr)
	{
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		TTF_Quit();
		return 1;
	}

	SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (ren == nullptr)
	{
		SDL_DestroyWindow(win);
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		TTF_Quit();
		return 1;
	}

	if (Mix_OpenAudio(32000, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	{
		MessageBox(NULL,
			(LPCWSTR)L"SDL_Mix_OpenAudio_error",
			(LPCWSTR)L"Sound_error!",
			MB_ICONWARNING | MB_OK
			);
		SDL_DestroyRenderer(ren);
		SDL_DestroyWindow(win);
		SDL_Quit();
		TTF_Quit();
		return 1;
	}

	//SDL_ShowCursor(SDL_DISABLE);

	load_screen_info cur_info_for_load_scr_thread;
	cur_info_for_load_scr_thread.render = ren;
	cur_info_for_load_scr_thread.texture = create_texture_function(ren, L"images/load_screens/main_load_screen.png");
	SDL_Thread *thread_loading_screen;
	thread_loading_screen = SDL_CreateThread(loading_screen_Thread, "loading_screen_Thread", &cur_info_for_load_scr_thread);

	MENU all_menu_and_important_variables(ren);

	Mix_Chunk *menu_title = NULL;
	menu_title = load_music_function(L"sound_files/music/mus_global_title_theme.ogg");

	end_of_menu_loading = true;
	SDL_WaitThread(thread_loading_screen, &result_of_thread);


	while (!all_menu_and_important_variables.quit_state())
	{
		if (Mix_Playing(1) == 0)
		{
			if (Mix_PlayChannel(1, menu_title, 0) == -1)
			{
				MessageBox(NULL,
					(LPCWSTR)L"Main_title_sound_error",
					(LPCWSTR)L"Sound_error!",
					MB_ICONWARNING | MB_OK
					);
			}
		}
		all_menu_and_important_variables.menu_processing();
	}

	Mix_FreeChunk(menu_title);
	Mix_CloseAudio();
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();
	TTF_Quit();
	return 0;
}
