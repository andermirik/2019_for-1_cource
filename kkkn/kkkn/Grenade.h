#pragma once
#include "Object.h"
class Grenade : public Object //
{
protected:
	int DamageRadius;
	int Weight;
	int Check;//1 - pulled, 0 - inserted
public:
	Grenade(int DamageRadius, int Weight);
	~Grenade();
	void PullCheck();
	void InsertCheck();
	static int count;

	int GetDamageRadius();
	int GetWeight();
	int GetCheck();

	void operator!();//check=!check

	virtual void ToFile(std::ofstream &fout);
	virtual void ToStd(std::ostream &out);
	virtual void read(std::ifstream &fin);
	virtual void readFields(int args = 0);
};

