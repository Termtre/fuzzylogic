//
//  instruments.cpp
//  fuzzylogic
//
//  Created by Дмитрий  on 20.11.2023.
//

#include "instruments.h"
#include "line.h"

Instruments::Instruments(const BMP& bmpImage)
{
    this->width = bmpImage.bmp_width;
    this->height = bmpImage.bmp_height;
    
    for (auto it = bmpImage.image.begin(); it != bmpImage.image.end(); ++it)
        this->image.push_back(*it);
}

void Instruments::exportImage(BMP& bmpImage)
{
    for (auto it = this->image.begin(); it != this->image.end(); ++it)
        bmpImage.image.push_back(*it);
}

void Instruments::createLine()
{
    Line firstLine(dot(0, 0), dot(10, 10));
    
    for (dot it = dot(0, 0); it.x < 300 && it.y < 300;)
    {
        it = firstLine.nextDot(it);
        image[it.y * width + it.x] = pixel(0, 0, 0);
    }
}
