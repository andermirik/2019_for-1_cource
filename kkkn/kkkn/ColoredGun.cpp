#include "ColoredGun.h"
int ColoredGun::count = 0;
ColoredGun::ColoredGun
(
	int Capacity,int Calibre, int Distance,	int Number,
	std::string BarrelType,	int Red, int Green, int Blue
)
	:Gun(Capacity,Calibre,Distance,Number,BarrelType) , Color(Red, Green, Blue)
{
	ColoredGun::count++;
	Gun::count--;
}

void ColoredGun::SetColor(int color)
{
	Red = (color & 0xff0000) >> 16;
	Green = (color & 0xff00) >> 8;
	Blue = color & 0xff;
}

void ColoredGun::WhatColor()
{
	std::printf("(%d;%d;%d)", Red, Green, Blue);
}

void ColoredGun::ToFile(std::ofstream &fout)
{
	Gun::ToFile(fout);
	Color::ToFile(fout);
}

void ColoredGun::ToStd(std::ostream & out)
{
	Gun::ToStd(out);
	Color::ToStd(out);
}

void ColoredGun::read(std::ifstream &fin)
{
	Gun::read(fin);
	Color::read(fin);
}

void ColoredGun::readFields(int args)
{
	Gun::readFields(args);
	Color::readFields(args);
}

ColoredGun::~ColoredGun()
{
	ColoredGun::count--;
	Gun::count++;
}
