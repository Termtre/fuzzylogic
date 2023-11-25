//
//  BMP.cpp
//  Image
//
//  Created by Дмитрий  on 25.09.2023.
//

#include "BMP.h"

void BMP::importImage(const std::vector<pixel>& _image)
{
    if (isEmpty())
    {
        throw "Container is empty. First upload image";
    }
    
    image.clear();
    
    for (auto it = _image.begin(); it != _image.end(); ++it)
        image.push_back(*it);
}

void BMP::importImage(std::string url)
{
    if (!isEmpty()) clear();
    
    std::ifstream openFile(url, std::ios::in | std::ios::binary);
    
    if (!openFile.is_open())
    {
        throw "File didn't open!";
    }
    
    openFile.read(reinterpret_cast<char*>(header), 54);
    
    if (header[0] != 'B' || header[1] != 'M')
    {
        throw "This file isn't BMP format!";
    }
    
    bmp_size = *reinterpret_cast<int*>(&header[0x02]);
    bmp_width = *reinterpret_cast<int*>(&header[0x12]);
    bmp_height = *reinterpret_cast<int*>(&header[0x16]);
    
    bmp_padding = (4 - (bmp_width * 3) % 4) % 4;
    
    for (int y = 0; y < bmp_height; y++)
    {
        for (int x = 0; x < bmp_width; x++)
        {
            uchar color[3];
            
            openFile.read(reinterpret_cast<char*>(color), 3);
            
            image.push_back(pixel(color[2], color[1], color[0]));
        }
        
        openFile.ignore(bmp_padding);
    }
    
    openFile.close();
}

void BMP::exportImage(std::string url)
{
    if (isEmpty())
    {
        throw "Image hasn't been found!";
    }
    
    std::ofstream openFile(url, std::ios::out | std::ios::binary);
    
    if (!openFile.is_open())
    {
        throw "File didn't open!";
    }
    
    openFile.write(reinterpret_cast<char*>(header), 54);
    
    for (int y = 0; y < bmp_height; y++)
    {
        for (int x = 0; x < bmp_width; x++)
        {
            uchar color[3];
            color[0] = image[y * bmp_width + x].b;
            color[1] = image[y * bmp_width + x].g;
            color[2] = image[y * bmp_width + x].r;
            
            openFile.write(reinterpret_cast<char*>(color), 3);
        }
        
        openFile.write(reinterpret_cast<char*>(padding), bmp_padding);
    }
    
    openFile.close();
}

int BMP::size()
{
    return bmp_size;
}

int BMP::width()
{
    return bmp_width;
}

int BMP::height()
{
    return bmp_height;
}

bool BMP::isEmpty()
{
    return image.empty();
}

void BMP::clear()
{
    if (!isEmpty())
    {
        image.clear();
        bmp_size = 0;
        bmp_width = 0;
        bmp_height = 0;
    }
}
