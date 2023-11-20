//
//  fuzzylogic.hpp
//  Image
//
//  Created by Дмитрий  on 09.10.2023.
//
#pragma once

#include <cmath>

// Линейная функция принадлежности
double straight_memFunction(int x, int a, int b, int c);
// Трапецевидная функция принадлежности
double trapezoid_memFunction(int x, int a, int b, int c, int d);
// S-образная функция принадлежности
double S_memFunction(int x, int a, int b, int c);
// P-образная функция принадлежности
double P_memFunction(int x, int a, int b, int c);