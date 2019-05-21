#pragma once
#include "Object.h"
class Weapon : public Object
{
protected:
	int Capacity;
	int Calibre;
	int Distance;

	int CountBullet;
public:
	Weapon();
	Weapon(int Capacity, int Calibre, int Distance);
	void Charge();
	void UnCharge();
	virtual ~Weapon();

	static int count;
	int GetCapacity();
	int GetCalibre();
	int GetDistance();
	int GetCountBullet();

	virtual void ToFile(std::ofstream &fout);
	virtual void ToStd(std::ostream &out);
	virtual void read(std::ifstream &fin);
	virtual void readFields(int args = 0);

};

