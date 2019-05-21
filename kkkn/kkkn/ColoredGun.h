#pragma once
#include <iostream>
#include "Gun.h"
class ColoredGun;
class Color {
	friend ColoredGun;
protected:
	int Red;
	int Green;
	int Blue;
public:
	Color(int, int, int);
	virtual void WhatColor() = 0;
	void SetColor(int, int, int);
	void ToFile(std::ofstream&);
	virtual ~Color() {}
	void ToStd(std::ostream &out);
	void read(std::ifstream&);
	virtual void readFields(int args = 0);
};

class ColoredGun : public Color, public Gun {
public:
	ColoredGun(
		int Capacity,
		int Calibre,
		int Distance,
		int Number,
		std::string BarrelType,
		int Red,
		int Green,
		int Blue
	);
	static int count;

	void SetColor(int color);
	void WhatColor();

	void ToFile(std::ofstream&);
	void ToStd(std::ostream &out);
	void read(std::ifstream&);
	void readFields(int args = 0);

	~ColoredGun();
};

