#include "Gun.h"
#include "Language.h"
#include "Application.h"
#include <string>
int Gun::count = 0;

Gun::Gun()
{
	Gun::count++;
	Weapon::count--;
}


Gun::Gun(int Capacity, int Calibre, int Distance, int Number, std::string BarrelType)
	:Weapon(Capacity,Calibre,Distance)
{
	this->Number = Number;
	this->BarrelType = BarrelType;
	this->State = 1;

	Gun::count++;
	Weapon::count--;
}

int Gun::GetNumber()
{
	return Number;
}

int Gun::GetState()
{
	return State;
}

void Gun::ToFile(std::ofstream & fout)
{
	Weapon::ToFile(fout);
	fout << Number << std::endl 
		 << BarrelType << std::endl;
}

void Gun::ToStd(std::ostream & out)
{
	Weapon::ToStd(out);
	if (Language::get().Current() == Language::english)
		out << "Number: " << Number << std::endl
		<< "BarrelType: " << BarrelType << std::endl;
	else if (Language::get().Current() == Language::russian)
		out << "Табельный номер: " << Number << std::endl
		<< "Тип ствола: " << BarrelType << std::endl;

}

void Gun::read(std::ifstream & fin)
{
	Weapon::read(fin);
	fin >> Number >> BarrelType;
}

void Gun::readFields(int args)
{
	Weapon::readFields(args);
	if (Language::get().Current() == Language::english) {
		if (args&Application::Attributes::NUMBER) {
			std::cout << "Number: ";
			Number = Application::get().read_int();
		}
		if (args&Application::Attributes::BARREL_TYPE) {
			std::cout << "Barrel Type: ";
			std::cin >> BarrelType;
		}
	}
	else if (Language::get().Current() == Language::russian) {
		if (args&Application::Attributes::NUMBER) {
			std::cout << "Табельный номер: ";
			Number = Application::get().read_int();
		}
		if (args&Application::Attributes::BARREL_TYPE) {
			std::cout << "Тип ствола: ";
			std::cin >> BarrelType;
		}
	}
}

void Gun::Shot()
{
	if (CountBullet != 0 && State == 0)
		this->CountBullet = CountBullet - 1;
}

void Gun::operator!()
{
	if (State == 0)
		State = 1;
	else if (State == 1)
		State = 0;
}

Gun::~Gun()
{
	Gun::count--;
	Weapon::count++;
}
