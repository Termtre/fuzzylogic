#pragma once
#include "fuzzylogic.h"
#include "pixel.h"
#include <utility>

class Smear
{
private:
	pixel less;			// от этого цвета происходит размытие
	pixel more;			// к этому цвету происходит размытие
	int lessBorder;		// координата исходного цвета
	int moreBorder;		// координата конечного цвета
	int redDiff, greenDiff, blueDiff;
	int absRedDiff, absGreenDiff, absBlueDiff;

public:
	Smear() {}
	~Smear() {}

	void setSmearColors(const pixel&, const pixel&);	// Установка цветов для размытия
	void setSmearBorder(const int&, const int&);		// Установка границ размытия
	pixel changeColor(int);								// Размытие
	void clear();										// Очистка

};
