#include "Weapon.h"
#include "Language.h"
#include "Application.h"
int Weapon::count = 0;
Weapon::Weapon()
{
	this->Capacity = 0;
	this->Calibre = 0;
	this->Distance = 0;

	this->CountBullet = 0;
	Weapon::count++;
}

Weapon::Weapon(int Capacity, int Calibre, int Distance)
{
	this->Capacity = Capacity;
	this->Calibre = Calibre;
	this->Distance = Distance;

	this->CountBullet = 0;
	Weapon::count++;
}

void Weapon::Charge()
{
	UnCharge();
	CountBullet = Capacity;
}

void Weapon::UnCharge()
{
	CountBullet = 0;
}

Weapon::~Weapon()
{
	Weapon::count--;
}

int Weapon::GetCapacity()
{
	return Capacity;
}

int Weapon::GetCalibre()
{
	return Capacity;
}

int Weapon::GetDistance()
{
	return Distance;
}

int Weapon::GetCountBullet()
{
	return CountBullet;
}

void Weapon::ToFile(std::ofstream & fout)
{
	fout << Capacity << std::endl << Calibre << std::endl << Distance << std::endl;
}


void Weapon::ToStd(std::ostream & out)
{
	if(Language::get().Current()==Language::english)
		out << "Capacity: " << Capacity << std::endl
			<< "Calibre: " << Calibre << std::endl
			<< "Distance: " << Distance << std::endl;
	else if(Language::get().Current() == Language::russian)
		out << "Объем магазина: " << Capacity << std::endl
		<< "Калибр: " << Calibre << std::endl
		<< "Дальность стрельбы: " << Distance << std::endl;
}

void Weapon::read(std::ifstream & fin)
{
	fin >> Capacity >> Calibre >> Distance;
}

void Weapon::readFields(int args)
{
	if (Language::get().Current() == Language::english) {
		if (args&Application::Attributes::CAPACITY) {
			std::cout << "Capacity: ";
			Capacity = Application::get().read_int();
		}
		if (args&Application::Attributes::CALIBRE) {
			std::cout << "Calibre: ";
			Calibre = Application::get().read_int();
		}
		if (args&Application::Attributes::DISTANCE) {
			std::cout << "Distance: ";
			Distance = Application::get().read_int();
		}
	}
	else if (Language::get().Current() == Language::russian) {
		if (args&Application::Attributes::CAPACITY) {
			std::cout << "Объем магазина: ";
			Capacity = Application::get().read_int();
		}
		if (args&Application::Attributes::CALIBRE) {
			std::cout << "Калибр: ";
			Calibre = Application::get().read_int();
		}
		if (args&Application::Attributes::DISTANCE) {
			std::cout << "Дальность стрельбы: ";
			Distance = Application::get().read_int();
		}
	}
}
