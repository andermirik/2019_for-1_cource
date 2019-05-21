#include "Grenade.h"
#include "Language.h"
#include "Application.h"
int Grenade::count = 0;

Grenade::Grenade(int DamageRadius, int Weight)
{
	this->DamageRadius = DamageRadius;
	this->Weight = Weight;
	this->Check = 0;

	Grenade::count++;
}

Grenade::~Grenade()
{
	Grenade::count--;
}

void Grenade::PullCheck()
{
	Check = 1;
}

void Grenade::InsertCheck()
{
	Check = 0;
}

int Grenade::GetDamageRadius()
{
	return DamageRadius;
}

int Grenade::GetWeight()
{
	return Weight;
}

int Grenade::GetCheck()
{
	return Check;
}

void Grenade::operator!()
{
	if (Check == 1)
		InsertCheck();
	else if (Check == 0)
		PullCheck();
}

void Grenade::ToFile(std::ofstream & fout)
{
	fout << DamageRadius << std::endl << Weight << std::endl;
}

void Grenade::ToStd(std::ostream & out)
{
	if (Language::get().Current() == Language::english)
		out << "Damage Radius: " << DamageRadius << std::endl
		<< "Weight: " << Weight << std::endl
		<< "Check: " << Check << std::endl;
	else if (Language::get().Current() == Language::russian)
		out << "Радиус поражения: " << DamageRadius << std::endl
		<< "Вес: " << Weight << std::endl
		<< "Чека: " << Check<< std::endl;
}

void Grenade::read(std::ifstream & fin)
{
	fin >> DamageRadius >> Weight;
}

void Grenade::readFields(int args)
{
	if (Language::get().Current() == Language::english) {
		if (args&Application::Attributes::DAMAGE_RADIUS) {
			std::cout << "DamageRadius: ";
			DamageRadius = Application::get().read_int();
		}
		if (args&Application::Attributes::WEIGHT) {
			std::cout << "Weight: ";
			Weight = Application::get().read_int();
		}
	}
	else if (Language::get().Current() == Language::russian) {
		if (args&Application::Attributes::DAMAGE_RADIUS) {
			std::cout << "DamageRadius: ";
			DamageRadius = Application::get().read_int();
		}
		if (args&Application::Attributes::WEIGHT) {
			std::cout << "Weight: ";
			Weight = Application::get().read_int();
		}
	}
}
