#pragma once
#include <iostream>
#include <fstream>
#include <string>

enum namefile {
	readme,
	aboutme,
	aboutprog
};
enum slides {
	none = -1,
	start,
	change_lang,
	menu,
	edit_config,
	shop,
	config
};

class Interface
{
public:
	Interface() {}
	Interface(const Interface&) = delete;
	Interface&operator=(Interface&) = delete;

	static Interface& get() {
		static Interface  instance;
		return instance;
	}
public:
	void PrintFile(int namefile, int locale, std::string path="");
	void DrawSlide(int slide, int back_slide=none);
	void Put(int num, char end='\n');
	void Put(std::pair<int, int> range);
	void SaveConfig();
};

