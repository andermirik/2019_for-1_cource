#include "Language.h"
#include<iostream>
#include <fstream>
#include <string>

std::string Language::MsgAt(int i)
{
	
	try {
		if (now == russian) {
			return map.at(i).first;
		}
		else if (now == english) {
			return map.at(i).second;
		}
	}
	catch (const std::out_of_range& ) {

		if (now == russian) {
			return "нет подходящей фразы по номеру " + std::to_string(i);
		}
		else if (now == english) {
			return "no matching phrase for number " + std::to_string(i);
		}
	}
	return "none";
}

Language::TypeL Language::Current()
{
	return now;
}

void Language::SetLanguage(TypeL t)
{
	now = t;
}

bool Language::read_from_file(std::string ru, std::string eng)
{
	std::string rumsg;
	std::string enmsg;
	std::ifstream ruin;
	std::ifstream enin;
	bool result = true;
	ruin.exceptions(std::ifstream::badbit);
	enin.exceptions(std::ifstream::failbit);
	try {
		ruin.open(ru);
		enin.open(eng);
		int now_i = 0;
		while (!ruin.eof() && !enin.eof() && getline(ruin, rumsg) && getline(enin, enmsg))
		{
			if (now_i < count_phrases) {
				map.push_back({"",""});
				map[now_i++] = {
					rumsg,
					enmsg
				};
			}
		}
		ruin.close();
		enin.close();
	}
	catch (std::exception const& ) {
		if (now == english)
			std::cerr << "unable to open file with translate" << std::endl;
		else if (now == russian)
			std::cerr << "неудача при открытии файла с переводом" << std::endl;
		result = false;
	}
	return result;
}
	