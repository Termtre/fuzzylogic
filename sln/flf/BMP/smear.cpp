#include "smear.h"

void Smear::setSmearColors(const pixel& _less, const pixel& _more)
{
	less = _less;
	more = _more;
}

void Smear::setSmearBorder(const int& _less, const int& _more)
{
	lessBorder = _less;
	moreBorder = _more;
}

pixel Smear::changeColor(int cur)
{
	double f1 = straight_memFunction(cur, lessBorder - 1, lessBorder, moreBorder);
	double f2 = straight_memFunction(cur, lessBorder, moreBorder, moreBorder + 1);
	int redDiff = abs(more.r - less.r);
	int greenDiff = abs(more.g - less.g);
	int blueDiff = abs(more.b - less.b);
	uchar red = less.r, green = less.g, blue = less.b;

	if (redDiff) red = (more.r - less.r) > 0 ? redDiff * f2 + less.r :redDiff * f1 + more.r;
	if (greenDiff) green = (more.g - less.g) > 0 ? greenDiff * f2 + less.g : greenDiff * f1 + more.g;
	if (blueDiff) blue = (more.b - less.b) > 0 ? blueDiff * f2 + less.b : blueDiff * f1 + more.b;

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
