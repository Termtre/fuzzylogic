#pragma once
#include "fuzzylogic.h"
#include "pixel.h"
#include "dot.h"
#include <utility>

class Smear
{
private:
	pixel less;
	pixel more;
	pixel middle;
	int lessBorder;
	int moreBorder;
	int rr;				// ������� ����� ������� ������
	int gr;				// ������� ����� ������� ������
	int br;				// ������� ����� ����� ������
	double koef;		// ������� ����������� ��������

protected:
	double smearKoef(const int&);

public:
	Smear(const pixel&, const pixel&);
	~Smear() {}

	void setSmearBorder(const int&, const int&);
	void changeColor(pixel&);
	void clear();

};
