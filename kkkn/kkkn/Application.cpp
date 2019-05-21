#include "Application.h"
#include "Weapon.h"
#include "Gun.h"
#include "Grenade.h"
#include "ColoredGun.h"
#include <iostream>
#include "conio.h"

void Application::TestLastAdded() {
	if (container.size() == 0) {
		Interface::get().Put(61);
		return;
	}
	std::string type = (std::string)(typeid(*(container.back())).name() + 6);

	if (type == "")
		return;

	std::cout << "---------------------------------" << std::endl;
	std::cout << type << std::endl;
	std::cout << "---------------------------------" << std::endl;


	if (type == "Weapon") {
		Interface::get().Put(64);
		((Weapon*)container.back().get())->Charge();
		Interface::get().Put(65);
		((Weapon*)container.back().get())->UnCharge();
	}
	else if (type == "Gun") {
		Interface::get().Put(67);
		((Gun*)container.back().get())->operator!();

		Interface::get().Put(64);
		((Gun*)container.back().get())->Charge();
		Interface::get().Put(68);
		((Gun*)container.back().get())->Shot();
		Interface::get().Put(63, ' ');
		std::cout
			<<
			((Gun*)container.back().get())->GetCountBullet()
			<< std::endl;
		Interface::get().Put(65);
		((Gun*)container.back().get())->UnCharge();

		Interface::get().Put(69);
		((Gun*)container.back().get())->operator!();
	}
	else if (type == "Grenade") {
		Interface::get().Put(71);
		((Grenade*)container.back().get())->operator!();
		Interface::get().Put(72);
		((Grenade*)container.back().get())->operator!();
	}
	else if (type == "ColoredGun") {
		Interface::get().Put(67);
		((Gun*)container.back().get())->operator!();

		Interface::get().Put(64);
		((Gun*)container.back().get())->Charge();
		Interface::get().Put(68);
		((Gun*)container.back().get())->Shot();
		Interface::get().Put(63, ' ');
		std::cout 
			<<
			((Gun*)container.back().get())->GetCountBullet()
			<< std::endl;
		Interface::get().Put(65);
		((Gun*)container.back().get())->UnCharge();

		Interface::get().Put(69);
		((Gun*)container.back().get())->operator!();
	}
	else {
		std::cerr << "Class " << type << " not found" << std::endl;
	}

}

void Application::SellSelected() {
	if (container.size() == 0) {
		Interface::get().Put(61);
		return;
	}
	int num = 0;
	Interface::get().Put(74, ' ');
	num = read_int();
	int i = 1;
	for (auto&object : container) {
		if (i == num) {
			std::cout << "---------------------------------" << std::endl;
			std::cout << (std::string)(typeid(*object).name() + 6)<< std::endl;
			std::cout << "---------------------------------" << std::endl;
			std::cout << object.get() << std::endl;
			container.remove(object);
			break;
		}
		i++;
	}
	Interface::get().Put(46);
}

void Application::CheckInventory() {
	if (container.size() == 0)
		Interface::get().Put(61);
	int i = 1;
	for (auto&object : container) {
		std::cout << "---------------------------------"<<std::endl;
		std::cout << i<<"|"<<(std::string)(typeid(*object).name() + 6) << std::endl;
		std::cout << "---------------------------------" << std::endl;
		std::cout << object.get() << std::endl;
		i++;
	}
}

void Application::AddWeapon() {
	auto obj = std::make_unique<Weapon>(0, 0, 0);
	obj.get()->readFields(
		Attributes::CAPACITY
		| Attributes::CALIBRE
		| Attributes::DISTANCE
	);
	container.push_back(std::move(obj));
}

void Application::AddGun() {
	auto obj = std::make_unique<Gun>(0, 0, 0, 0, "");
	obj.get()->readFields(
		Attributes::CAPACITY
		| Attributes::CALIBRE
		| Attributes::DISTANCE
		| Attributes::NUMBER
		| Attributes::BARREL_TYPE
	);
	container.push_back(std::move(obj));
}
void Application::AddGrenade() {
	auto obj = std::make_unique<Grenade>(0, 0);
	obj.get()->readFields(
		Attributes::DAMAGE_RADIUS
		| Attributes::WEIGHT
	);
	container.push_back(std::move(obj));
}
void Application::AddColoredGun() {
	auto obj = std::make_unique<ColoredGun>(0, 0, 0, 0, "", 0, 0, 0);
	obj.get()->readFields(
		Attributes::RED
		| Attributes::GREEN
		| Attributes::BLUE
		| Attributes::CAPACITY
		| Attributes::CALIBRE
		| Attributes::DISTANCE
		| Attributes::NUMBER
		| Attributes::BARREL_TYPE
	);
	container.push_back(std::move(obj));
}

void Application::LoadData()
{
	std::ifstream fin;
	fin.exceptions(std::ios::badbit);
	try {
		fin.open("Data/save.txt");
		container.clear();

		std::string type;
		std::unique_ptr<Object> obj;
		while (!fin.eof()) {
			fin >> type;
			if (type == "")
				return;
			if (type == "Weapon") {
				obj = std::make_unique<Weapon>(0, 0, 0);
				fin >> obj.get();
			}
			else if (type == "Gun") {
				obj = std::make_unique<Gun>(0, 0, 0, 0, "");
				fin >> obj.get();
			}
			else if (type == "Grenade") {
				obj = std::make_unique<Grenade>(0, 0);
				fin >> obj.get();
			}
			else if (type == "ColoredGun") {
				obj = std::make_unique<ColoredGun>(0, 0, 0, 0, "", 0, 0, 0);
				fin >> obj.get();
			}
			else {
				std::cerr << "Class " << type << " not found" << std::endl;
				continue;
			}
			//std::cout << obj << std::endl;//debug
			container.push_back(std::move(obj));
			type = "";
		}
		
		fin.close();
	}
	catch (std::exception const&) {
		if (Language::get().Current() == Language::english)
			std::cerr << std::endl << "unable to found last session" << std::endl;
		else if (Language::get().Current() == Language::russian)
			std::cerr << std::endl << "не удалось найти прошлую сессию" << std::endl;
	}
}

void Application::SaveData()
{
		if (container.size()) {
			std::ofstream fout("Data/save.txt");
			for (auto&object : container) {
				fout << (std::string)(typeid(*object).name() + 6) << std::endl;
				fout << object.get() << std::endl;
			}
			fout.close();
			if (Language::get().Current() == Language::english)
				std::cout << std::endl << "session saved" << std::endl;
			else if (Language::get().Current() == Language::russian)
				std::cout << std::endl << "сессия сохранена" << std::endl;

		}
		else {
			if (Language::get().Current() == Language::english)
				std::cerr << std::endl << "session is clear" << std::endl;
			else if (Language::get().Current() == Language::russian)
				std::cerr << std::endl << "сессия пуста" << std::endl;
		}
}

int Application::exec()
{
	Config::get().ReadConfig();
	auto error = Config::get().CheckResourceFiles();
	if (!error) { std::cin.get(); return 1; }

	error = Language::get().read_from_file(
		Config::get().Files()[0],
		Config::get().Files()[1]
	);
	if (!error) { std::cin.get(); return 1; }

	Interface::get().DrawSlide(slides::start);
	Interface::get().DrawSlide(slides::menu);
	return 0;
}

int Application::read_int()
{
	int k, n = 0, flgS = 0, c = 0, q = 0;

	while (1)
	{

		k = _getch();
		/*if ((k == '-') && (flgS == 0))
		{
			flgS = -1;
			_putch('-');
			c++;
		}*/

		if ((k >= '0') && (k <= '9'))
		{
			printf("%c", k);
			n = n * 10 + k - '0';
			c++;
			q++;
		}

		if (k == 8)
		{
			_putch(8);
			_putch(' ');
			_putch(8);
			n = n / 10;
			q--;
			if (q < 0) q = 0;
			c--;
			if (c == 0) flgS = 0;
		}

		if ((k == 13) && (c != 0) && (q != 0)) break;

	}

	if (flgS == -1) n = -n;
	_putch('\n');
	return n;
}
