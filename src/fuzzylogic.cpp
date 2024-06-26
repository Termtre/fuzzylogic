//
//  fuzzylogic.cpp
//  Image
//
//  Created by Дмитрий  on 18.10.2023.
//

#include "fuzzylogic.h"

double straight_memFunction(int x, int a, int b, int c)
{
    if (x < a) return 0.;
    if (a <= x && x <= b) return (static_cast<double>(x - a) / static_cast<double>(b - a));
    if (b < x && x <= c) return (static_cast<double>(c - x) / static_cast<double>(c - b));
    return 0.;
}

double trapezoid_memFunction(int x, int a, int b, int c, int d)
{
    if (x < a) return 0.;
    if (a <= x && x <= b) return (static_cast<double>(x - a) / static_cast<double>(b - a));
    if (b < x && x < c) return 1.;
    if (c <= x && x <= d) return (static_cast<double>(c - x) / static_cast<double>(c - b));
    return 0.;
}

double S_memFunction(int x, int a, int b, int c)
{
    if (x <= a) return 0.;
    else if (a < x && x <= b) return 2. * pow((static_cast<double>(x - a) / static_cast<double>(c - a)), 2.);
    else if (b < x && x <= c) return 1. - 2. * pow((static_cast<double>(x - c) / static_cast<double>(c - a)), 2.);
    else return 1.;
}

double P_memFunction(int x, int a, int b, int c)
{
    if (x <= c) return S_memFunction(x, c - b, c - b / 2, c);
    else return 1. - S_memFunction(x, c, c + b / 2, c + b);
}

double Laplas_memFunction(int x, int a, int b, int c)
{
    if (x < a) return 0.;
    if (a <= x && x <= b) return exp(-.000005 * (x - b) * (x - b));
    if (b < x && x <= c) return exp(-.000005 * (x - b) * (x - b));
    return 0.;
}

double exp_memFunction(int x, int a, int b, int c)
{
    if (x < a) return 0.;
    if (a <= x && x <= b) return exp(.003 * static_cast<double>(x - b));
    if (b < x && x <= c) return exp(-.003 * static_cast<double>(x - b));
    return 0.;
}

double parabola_memFunction(int x, int a, int b, int c)
{
    if (x < a) return 0.;
    if (a <= x && x <= b) return static_cast<double>((x - a) * (x - a)) / static_cast<double>(b - a) / static_cast<double>(b - a);
    if (b < x && x <= c) return static_cast<double>((x - c) * (x - c)) / static_cast<double>(b - c) / static_cast<double>(b - c);
    return 0.;
}
