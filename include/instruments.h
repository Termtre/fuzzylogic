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
#include <utility>

class Instruments
{
private:
    std::vector<pixel> image;
    int width;
    int height;
    
private:
    void triangleSmear(const std::vector<dot>& sides, const pixel& in, const pixel& out);
    bool findTriangle(dot& s1, dot& s2, dot& s3, dot& O);
    bool findSquare(dot& s1, dot& s2, dot& s3, dot& s4, dot& O);
    bool findCircle(dot& O, int& radius);

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
    void testSmearTriangle(double koef);
    void test();
};

#endif /* instruments_h */
