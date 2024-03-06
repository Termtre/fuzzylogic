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

void BMP::setImage(int width, int height, const std::vector<pixel>& _image)
{
    image.clear();

    bmp_width = width;
    bmp_height = height;
    bmp_padding = (4 - (bmp_width * 3) % 4) % 4;
    bmp_size = 54 + _image.size() * sizeof(pixel) + bmp_height * 3;

    for (auto it = _image.begin(); it != _image.end(); ++it)
        image.push_back(*it);
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

BMP BMP::operator+(const BMP& other) const
{
    if (this->bmp_height != other.bmp_height || this->bmp_width != other.bmp_width)
        throw "Different height or width. Try again";

    BMP third;

    third = *this;

    for (int i = 0; i < third.bmp_width * third.bmp_height; i++)
    {
        third.image[i].r = third.image[i].r / 2 + other.image[i].r / 2;
        third.image[i].g = third.image[i].g / 2 + other.image[i].g / 2;
        third.image[i].b = third.image[i].b / 2 + other.image[i].b / 2 ;
    }

    return third;
}

const BMP& BMP::operator=(const BMP& other)
{
    if (*this != other)
    {
        this->bmp_height = other.bmp_height;
        this->bmp_width = other.bmp_width;
        this->bmp_padding = other.bmp_padding;
        this->bmp_size = other.bmp_size;

        this->image.clear();

        for (auto it = other.image.begin(); it != other.image.end(); ++it)
            this->image.push_back(*it);

        for (int i = 0; i < 54; i++)
            this->header[i] = other.header[i];
    }

    return *this;
}

const bool BMP::operator==(const BMP& other) const
{
    if (this->bmp_height != other.bmp_height) return false;
    if (this->bmp_width != other.bmp_width) return false;
    if (this->bmp_padding != other.bmp_padding) return false;
    if (this->bmp_size != other.bmp_size) return false;
    if (this->image != other.image) return false;

    return true;
}

const bool BMP::operator!=(const BMP& other) const
{
    return !(*this == other);
}
