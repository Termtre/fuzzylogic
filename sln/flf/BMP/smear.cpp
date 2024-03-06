#include "smear.h"
#include <iostream>

void Smear::setSmearColors(const pixel& _less, const pixel& _more)
{
	less = _less;
	more = _more;

	redDiff = more.r - less.r;
	greenDiff = more.g - less.g;
	blueDiff = more.b - less.b;

	absRedDiff = abs(redDiff);
	absGreenDiff = abs(greenDiff);
	absBlueDiff = abs(blueDiff);
}

void Smear::setSmearBorder(const int& _less, const int& _more)
{
	lessBorder = _less;
	moreBorder = _more;
}

pixel Smear::changeColor(int cur)
{
	//double f1 = straight_memFunction(cur, lessBorder - 1, lessBorder, moreBorder);
	//double f2 = straight_memFunction(cur, lessBorder, moreBorder, moreBorder + 1);
	double f1 = Laplas_memFunction(cur, lessBorder - 1, lessBorder, moreBorder);
	double f2 = Laplas_memFunction(cur, lessBorder, moreBorder, moreBorder + 1);
	//double f1 = exp_memFunction(cur, lessBorder - 1, lessBorder, moreBorder);
	//double f2 = exp_memFunction(cur, lessBorder, moreBorder, moreBorder + 1);

	//std::cout << f1 << " " << f2 << std::endl;

	uchar red = less.r, green = less.g, blue = less.b;

	if (redDiff) red = redDiff > 0 ? absRedDiff * f2 + less.r : absRedDiff * f1 + more.r;
	if (greenDiff) green = greenDiff > 0 ? absGreenDiff * f2 + less.g : absGreenDiff * f1 + more.g;
	if (blueDiff) blue = blueDiff > 0 ? absBlueDiff * f2 + less.b : absBlueDiff * f1 + more.b;

	return pixel(red, green, blue);
}

void Smear::clear()
{
	less = std::move(pixel());
	more = std::move(pixel());
	lessBorder = 0;
	moreBorder = 0;
	double smearKoef = 0;
}
