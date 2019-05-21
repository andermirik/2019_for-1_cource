#include "Interface.h"
#include "Application.h"
#include "Weapon.h"
#include "Gun.h"
#include "Grenade.h"
#include "ColoredGun.h"
#include "Language.h"
#include "Config.h"
#include "conio.h"
#include "windows.h"
#include "Utils.h"

void Interface::PrintFile(int namefile, int locale, std::string path)
{
	std::ifstream fin;
	fin.exceptions(std::ios::failbit);
	try {
		if (path == "")
			fin.open(Config::get().Files()[namefile + 2 + locale * 3]);
		else
			fin.open(path);
		std::string temp;
		while (!fin.eof()) {
			std::getline(fin, temp);
			std::cout << temp << std::endl;
		}
		fin.close();
	}
	catch (std::exception const&) {
		if (locale == 1)
			std::cerr << "unable to open file" << std::endl;
		else if (locale == 0)
			std::cerr << "не удалось открыть файл" << std::endl;

	}
}

void Interface::DrawSlide(int slide, int back_slide) {
	char key;
	std::string temp;
	if (slide == start) {
		
		Put(std::pair<int,int>(1, 29));
		do {
			key = _getch();
			if (key == '1') {
				Interface::DrawSlide(change_lang, start);
				return;
			}
		} while (key != '2');
				
	}
	else if (slide == change_lang) {
		system("cls");
		
		Put(std::pair<int,int>(31, 33));
		do {
			key = _getch();
			switch (key) {
			case '1':
				Language::get().SetLanguage(Language::russian);
				system("cls");
				break;
			case '2':
				Language::get().SetLanguage(Language::english);
				system("cls");
				break;
			}
		} while (key != '1'&&key != '2');

		Interface::DrawSlide(back_slide, menu);
	}
	else if (slide == menu) {
		system("cls");
		Put(35);
		Put(80);
		Put(std::pair<int,int>(36, 42));
		do {
			key = _getch();
			switch (key)
			{
			case '0':
				system("cls");
				Interface::DrawSlide(config, menu);
				return;
				break;
			case '1':
				Put({ 43,45 });
				Application::get().LoadData();
				Put(46);
				break;
			case '2':
				Application::get().SaveData();
				break;
			case '3':
				Interface::DrawSlide(change_lang, menu);
				return;
			case '4':
				std::cout << std::endl << "---------------------------------" << std::endl;
				Interface::PrintFile(readme, Language::get().Current());
				std::cout << "---------------------------------" << std::endl;
				break;
			case'5':
				std::cout << std::endl << "---------------------------------" << std::endl;
				Interface::PrintFile(aboutme, Language::get().Current());
				std::cout << "---------------------------------" << std::endl;
				break;
			case'6':
				std::cout << std::endl << "---------------------------------" << std::endl;
				Interface::PrintFile(aboutprog, Language::get().Current());
				std::cout << "---------------------------------" << std::endl;
				break;
			case '7':
				Interface::DrawSlide(shop, menu);
				return;
			case 'r':
			case 'к'://refresh
				Interface::DrawSlide(menu);
				return;
				break;
			}
		} while (key != 27);
	}
	else if (slide == shop) {
		system("cls");
		Put({ 48,57 });
		do {
			key = _getch();
			switch (key)
			{
			case '1':
				Application::get().AddWeapon();
				std::cout << std::endl;
				break;
			case '2':
				Application::get().AddGun();
				std::cout << std::endl;
				break;
			case '3':
				Application::get().AddGrenade();
				std::cout << std::endl;
				break;
			case '4':
				Application::get().AddColoredGun();
				std::cout << std::endl;
				break;
			case '5':
				Application::get().TestLastAdded();
				break;
			case '6':
				Application::get().SellSelected();
				break;
			case '7':
				Application::get().CheckInventory();
				break;
			case '8':
				//count
				Put(75, ' '); std::cout << Weapon::count << std::endl;
				Put(76, ' '); std::cout << Gun::count << std::endl;
				Put(77, ' '); std::cout << Grenade::count << std::endl;
				Put(78, ' '); std::cout << ColoredGun::count << std::endl;
				break;
			case 'r':
			case 'к':
				Interface::DrawSlide(shop, menu);
				return;
			}
		}
		while (key!=27);
		Interface::DrawSlide(menu, none);
	}
	else if (slide == config) {
		Put({ 83, 96});
	do {
		key = _getch();
		if (key >= '1' && key <= '8') {
			std::cout << std::endl << std::endl;
			Put(97, ' '); //name:
			std::getline(std::cin, temp);
			temp = "Data/" + temp;
			if (fopen(temp.c_str(), "r")) {
				if (CountLines(temp) < Config::get().CountLinesFiles()[key - 49]) {
					if (Language::get().Current() == Language::english)
						std::cout << "ERROR!File is no exist or count str's is no correct." << std::endl;
					else if (Language::get().Current() == Language::russian)
						std::cout << "ќЎ»Ѕ ј!‘айл не существует или в нЄм недосточно строк."<<std::endl;

					std::cout << "(" << CountLines(temp) << "<" << Config::get().CountLinesFiles()[key - 49] << ")\n";
				}
				else {
					Config::get().Files()[key - 49] = temp;
					std::cout << "+" << std::endl;
					if (key == '1' || key == '2')
						if (!Config::get().CheckResourceFiles())
						{
							std::cin.get();
							exit(1);
						}
				}
			}
			else {
				if (Language::get().Current() == Language::english)
					std::cout << "ERROR!File is no exist or count str's is no correct." << std::endl;
				else if (Language::get().Current() == Language::russian)
					std::cout << "ќЎ»Ѕ ј!‘айл не существует или в нЄм недосточно строк." << std::endl;
			}

		}
		else if (key == 's' || key == 'ы') {
			system("cls");
			Interface::SaveConfig();
			Interface::DrawSlide(config, menu);
			return;
		}

		else if (key == 'c' || key == 'с') {
			Interface::DrawSlide(change_lang, config);
			return;
		}
	} while (key != 'd' && key != 'в');

	Interface::DrawSlide(back_slide, menu);
	}
}

void Interface::Put(int num, char end) {
	std::cout << Language::get().MsgAt(num-1) << end;
}

void Interface::Put(std::pair<int,int> range)
{
	for (range.first; range.first <= range.second; range.first++)
		std::cout << Language::get().MsgAt(range.first - 1) << std::endl;
}

void Interface::SaveConfig() {
	std::ofstream fout;
	try {
		fout.exceptions(std::ios::badbit);
		fout.open("data/config.txt");
		for(auto& file : Config::get().Files())
		{
			fout << file.c_str() + 5 << std::endl;
		}
		fout.close();
		auto error = Language::get().read_from_file(
			Config::get().Files()[0].c_str(),
			Config::get().Files()[1].c_str()
		);
		if (!error) { std::cin.get(); exit(1); }

	}
	catch (std::exception const& e) {
		if (Language::get().Current() == Language::english)
			std::cerr << "unable to open file" << std::endl;
		else if (Language::get().Current() == Language::russian)
			std::cerr << "не удалось открыть файл" << std::endl;
	}
}
