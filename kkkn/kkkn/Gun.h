#pragma once
#include "Weapon.h"
class Gun :	public Weapon
{
protected:
	int Number;
	int State;//1 = On, 0 = OFF
	std::string BarrelType;
public:
	static int count;
	Gun();
	Gun(
		int Capacity,
		int Calibre,
		int Distance,
		int Number,
		std::string BarrelType
	);
	void Shot();
	void operator!();
	virtual ~Gun();

	int GetNumber();
	int GetState();

	virtual void ToFile(std::ofstream &fout);
	virtual void ToStd(std::ostream &out);
	virtual void read(std::ifstream &fin);
	virtual void readFields(int args = 0);
};

