#pragma once
#include "fuzzylogic.h"
#include "pixel.h"
#include <utility>

class Smear
{
private:
	pixel less;			// �� ����� ����� ���������� ��������
	pixel more;			// � ����� ����� ���������� ��������
	int lessBorder;		// ���������� ��������� �����
	int moreBorder;		// ���������� ��������� �����

public:
	Smear() {}
	~Smear() {}

	void setSmearColors(const pixel&, const pixel&);	// ��������� ������ ��� ��������
	void setSmearBorder(const int&, const int&);		// ��������� ������ ��������
	pixel changeColor(int);								// ��������
	void clear();										// �������

};
