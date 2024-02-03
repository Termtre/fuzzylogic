#include "smear.h"

Smear::Smear(const pixel& _less, const pixel& _more) : less(_less), more(_more)
{
    rr = abs(less.r - more.r);
    gr = abs(less.g - more.g);
    br = abs(less.b - more.b);

}

void Smear::setSmearBorder(const int& _less, const int& _more)
{
	lessBorder = _less;
	moreBorder = _more;
}

void Smear::changeColor(pixel&)
{
    if (rr != 0) 1;
    if (gr != 0) 1;
    if (br != 0) 1;
}

void Smear::clear()
{
    koef = 0.;
}

double Smear::smearKoef(const int& cur)
{
    koef = straight_memFunction(cur, lessBorder, lessBorder, moreBorder);

	return koef;
}
