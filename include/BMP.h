//
//  BMP.hpp
//  Image
//
//  Created by Дмитрий  on 25.09.2023.
//
#pragma once

#include <vector>
#include <fstream>
#include "pixel.h"

#define uchar unsigned char

class BMP
{
    friend class Instruments;
    
private:
    int bmp_width;
    int bmp_height;
    int bmp_size;
    int heightColor = 1;
    uchar header[54];
    uchar padding[3] = { 0, 0, 0 };
    int bmp_padding;
    std::vector<pixel> image;
    
public:
    BMP() {}
    ~BMP() {}
    
    void importImage(const std::vector<pixel>& _image);
    void importImage(std::string url);
    void exportImage(std::string url);
    
    int size();
    int width();
    int height();
    bool isEmpty();
    void clear();
};
