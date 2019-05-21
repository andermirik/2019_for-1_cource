#include "Config.h"
#include "Language.h"
#include "Interface.h"
#include "Utils.h"
#include <iostream>
#include <fstream>
#include <string>

void Config::ReadConfig()
{
	std::fstream fin;
	fin.exceptions(std::ios::failbit);
	try {
		fin.open("Data\\config.txt");
		for (int i = 0; i < 8; i++) {
			files.push_back("");
			getline(fin, files[i]);
			files[i] = "Data/" + files[i];
		}

		fin.close();
	}
	catch (std::exception const&) {
		if (Language::get().Current() == Language::TypeL::english)
			std::cerr << "unable to open file with config" << std::endl;
		else if (Language::get().Current() == Language::TypeL::russian)
			std::cerr << "не удалось открыть файл конфига" << std::endl;
	}
}

bool Config::CheckResourceFiles()
{
	bool result = true;
	int now = 0;
	for (auto&file : files)
	{
		if (fopen(file.c_str(), "r")) {
			if (CountLines(file) < count_strs_files[now++]) {
				result = false;
				if (Language::get().Current() == Language::russian) {
					std::cout << "недостаточно строк в файле ";
				}
				else if (Language::get().Current() == Language::english) {
					std::cout << "not enough lines in the file ";
				}
				std::cout << "(" << CountLines(file) << " < " << count_strs_files[now - 1] << ")  ";
				std::cout << file<<std::endl;
			}
		}
		else {
			if (Language::get().Current() == Language::russian) {
				std::cout << "отсутсвует файл ";
			}
			else if (Language::get().Current() == Language::english) {
				std::cout << "not exist the file ";
			}
			result = false;
			std::cout << file << std::endl;
		}
	}

	return result;
}

std::vector<std::string>& Config::Files()
{
	return files;
}

std::vector<int>& Config::CountLinesFiles()
{
	return count_strs_files;
}

