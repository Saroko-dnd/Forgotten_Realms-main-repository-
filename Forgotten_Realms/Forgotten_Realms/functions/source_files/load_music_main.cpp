#include "../headers/load_music.h"

#include <stdlib.h>
#include <SDL.h>
#include <SDL_mixer.h>
#include <Windows.h>
#include <iostream>

Mix_Chunk * load_music_function(const wchar_t* current_path_name)
{
	char buf[255];
	if (wcstombs(buf, current_path_name, sizeof(buf)) == 255)
		buf[254] = '\0';
	Mix_Chunk * music = Mix_LoadWAV(buf);
	if (music == NULL)
	{
		MessageBox(NULL,
			(LPCWSTR)current_path_name,
			(LPCWSTR)L"Cant load sound!",
			MB_ICONWARNING | MB_OK
			);
	}

	return music;

}