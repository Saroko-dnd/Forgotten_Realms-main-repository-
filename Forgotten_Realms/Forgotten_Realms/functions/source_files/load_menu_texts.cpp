#include "../headers/load_menu_texts.h"
#include <fstream>
#include <iostream>
#include <string>
#include <locale>
#include <locale.h>
#include <assert.h>
#include <codecvt>
#include <iostream>
#include "../../GLOBALS/GLOBAL_VARIABLES.h"

text load_texts_from_file(text current_storage, std::wstring path_name)
{
	int type_of_document=1;
	std::wifstream current_file(path_name.c_str(),std::ios::binary);

	//Ниже устанавливаем нужную для распознования кодировку для current_file 
	current_file.imbue(std::locale(current_file.getloc(), new std::codecvt_utf16<wchar_t, 0x10ffff, std::consume_header>));
	std::wstring buf, extra_buf;

	while (type_of_document && std::getline<wchar_t>(current_file, buf))
	{
		if (buf[0] == L'@')
			type_of_document = 0;
		else
			current_storage.short_.push_back(buf);
	}

	if (type_of_document == 0)
	{
		while (std::getline<wchar_t>(current_file, buf))
		{
			std::cout << "\n buf_size" << buf.size() << std::endl;
			if (buf[0] != L'@')
			{
				extra_buf = extra_buf + buf;
				//extra_buf[extra_buf.size() - 1] = L'\0';
			}
			else
			{
					current_storage.long_.push_back(extra_buf);
					extra_buf.resize(0);
			}
		}
	}

	std::cout <<"\n"<< current_storage.long_.size() << std::endl;

	current_file.close();

	//удаляем лишний символ из всех строк
	for (int counter = 0; counter < current_storage.short_.size();++counter)
	{
		current_storage.short_[counter][current_storage.short_[counter].size() - 1] = L'\0';
	};

	return current_storage;
}
