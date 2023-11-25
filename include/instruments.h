//
//  instruments.h
//  fuzzylogic
//
//  Created by Дмитрий  on 20.11.2023.
//

#ifndef instruments_h
#define instruments_h

#include <iostream>
#include "BMP.h"
#include "fuzzylogic.h"
#include "line.h"
#include "dot.h"
#include <cmath>

class Instruments
{
private:
    std::vector<pixel> image;
    int width;
    int height;
    
private:
    void triangleSmear(const std::vector<dot>& sides, const pixel& in, const pixel& out);

public:
    Instruments(const BMP& bmpImage);
    ~Instruments() {}
    
    void exportImage(BMP& bmpImage);
    
    void createLine();
    void create_square(int side, pixel out_color, pixel in_color);
    void smearSquare(double koef);
    void smearTriangle(double koef);
    void testSmearSquare(double koef);
    void smearCircle(double koef);
    void test();
};

#endif /* instruments_h */
