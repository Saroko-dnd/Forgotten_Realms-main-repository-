#include "../headers/load_path_names.h"

#include <vector>
#include <string>

std::vector<std::wstring> load_path_names_function()
{
	std::vector<std::wstring> buf_vector;
	buf_vector.push_back(L"texts/MENU_MAIN_texts.txt");//0
	buf_vector.push_back(L"texts/MENU_dif_level.txt");//1
	buf_vector.push_back(L"texts/MENU_options.txt");//2
	buf_vector.push_back(L"texts/MENU_sex.txt");//3
	buf_vector.push_back(L"texts/MENU_race.txt");//4
	return buf_vector;
}

