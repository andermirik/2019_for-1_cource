#include"ColoredGun.h"
#include <fstream>
#include "Application.h"
Color::Color(int r, int g, int b)
{
	SetColor(r, g, b);
}


void Color::SetColor(int r, int g, int b)
{
	Red = r;
	Green = g;
	Blue = b;
}

void Color::ToFile(std::ofstream& fout)
{
	fout << Red << std::endl << Green << std::endl << Blue << std::endl;
}

void Color::ToStd(std::ostream& out)
{
	if (Language::get().Current() == Language::english) {
		out << "Red: " << Red << std::endl << "Green: " << Green << std::endl << "Blue: " << Blue << std::endl;
	}
	else {
		out << "Красный: " << Red << std::endl << "Зелёный: " << Green << std::endl << "Синий: " << Blue << std::endl;
	}
}

void Color::read(std::ifstream& fin)
{
	fin >> Red >> Green >> Blue;
}

void Color::readFields(int args)
{
	if (Language::get().Current() == Language::english) {
		if (args&Application::Attributes::RED) {
			std::cout << "Red: ";
			Red = Application::get().read_int();
		}
		if (args&Application::Attributes::GREEN) {
			std::cout << "Green: ";
			Green = Application::get().read_int();
		}
		if (args&Application::Attributes::BLUE) {
			std::cout << "Blue: ";
			Blue = Application::get().read_int();
		}
	}
	else if (Language::get().Current() == Language::russian) {
		if (args&Application::Attributes::RED) {
			std::cout << "Красный: ";
			Red = Application::get().read_int();
		}
		if (args&Application::Attributes::GREEN) {
			std::cout << "Зелёный: ";
			Green = Application::get().read_int();
		}
		if (args&Application::Attributes::BLUE) {
			std::cout << "Синий: ";
			Blue = Application::get().read_int();
		}
	}
}