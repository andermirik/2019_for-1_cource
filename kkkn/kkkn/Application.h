#pragma once
#include "Language.h"
#include "Interface.h"
#include "Config.h"
#include "Object.h"
#include <memory>
#include <list>

class Application {
private:
	std::list<std::unique_ptr<Object>> container;
public:
	Application() {}
	Application(const Application&) = delete;
	Application&operator=(Application&) = delete;

	static Application& get() {
		static Application  instance;
		return instance;
	}

	void LoadData();
	void SaveData();
	void AddWeapon();
	void AddGun();
	void AddGrenade();
	void AddColoredGun();

	void TestLastAdded();
	void SellSelected();
	void CheckInventory();
	int exec();
	int read_int();
	enum Attributes {
		RED = 1 << 0,
		GREEN = 1 << 1,
		BLUE = 1 << 2,
		CAPACITY = 1 << 3,
		CALIBRE = 1 << 4,
		DISTANCE = 1 << 5,
		COUNT_BULLETS = 1 << 6,
		NUMBER = 1 << 7,
		BARREL_TYPE = 1 << 8,
		DAMAGE_RADIUS = 1 << 9,
		WEIGHT = 1 << 10,
		CHECK
	};
};


/*
0: rus.txt  97
1: eng.txt  97
2: rus_readme.txt   13
3: rus_aboutme  3
4: rus_aboutprog  28
5: eng_readme  22
6: eng_aboutme 3
7: eng_aboutprog 32
*/