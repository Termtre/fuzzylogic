//
//  BMP.hpp
//  Image
//
//  Created by Дмитрий  on 25.09.2023.
//
#pragma once

// libraries
#include <iostream>

// my libraries
#include "includes.h"
#include "fuzzylogic.hpp"
#include "pixel.h"
#include "pixel.h"

#define uchar unsigned char

class BMP
{
private:
    int bmp_width;
    int bmp_height;
    int bmp_size;
    int heightColor = 1;
    uchar header[54];
    uchar padding[3] = { 0, 0, 0 };
    int bmp_padding;
    std::vector<pixel> image;
    std::vector<pixel> greyImage;
    std::vector<pixel> mask;
    
private:  // Instruments
    void sobel(int a, int b, double d);
    void horizontalSmear(int left, int middle, int right, const pixel& leftColor, const pixel& rightColor);
    void verticalSmear(int down, int middle, int up, const pixel& downColor, const pixel& upColor);
    void triangleSmear(const std::vector<std::pair<int, int>>& sides, double angle, const pixel& in, const pixel& out);
    void p2triangleSmear(std::vector<std::pair<int, int>> sides, double angle, const pixel& in, const pixel& out);
    void _3p2triangleSmear(std::vector<std::pair<int, int>> sides, double angle, const pixel& in, const pixel& out);
    void _2ptriangleSmear(std::vector<std::pair<int, int>> sides, double angle, const pixel& in, const pixel& out);
    void testTriangleSmear(const std::vector<std::pair<int, int>>& sides, double angle, const pixel& in, const pixel& out);
    //void smearArea();
    
private: // For creating
    void create_horizontal_streakes(int number_streakes, std::vector<std::pair<pixel, int>> colors);
    void create_vertical_streakes(int number_streakes, std::vector<std::pair<pixel, int>> colors);
    void create_circle(int radius);
    void create_square(int side, pixel out_color, pixel in_color);
    void create_horizontal_clear_rainbow();
    void create_vertical_clear_rainbow();
    void create_triangle(int side, pixel out_color, pixel in_color);
    
public:
    BMP() {}
    ~BMP() {}
    
    void createImage(int _width, int _height);
    void interpretationHeader();
    void vertSmear();
    void horSmear();
    void smearTriangle();
    void smearSquare();
    void smearCircle();
    
    void importImage(std::string url);
    void exportImage(std::string url);
    
    int size();
    int width();
    int height();
    
    void clearColor();
    void cartoonFilter();
    void greyFilter(double _r, double _g, double _b);
    
    bool isEmpty();
    void clear();
};
