//
//  pixel.h
//  Image
//
//  Created by Дмитрий  on 20.11.2023.
//

#ifndef pixel_h
#define pixel_h

#include <utility>
#define uchar unsigned char

struct pixel
{
    uchar r;
    uchar g;
    uchar b;
    
    pixel() : r(0), g(0), b(0) {}
    pixel(uchar _r, uchar _g, uchar _b) : r(_r), g(_g), b(_b) {}
    pixel(const pixel& other) : r(other.r), g(other.g), b(other.b) {}
    pixel(pixel&& other) noexcept : r(std::move(other.r)), g(std::move(other.g)), b(std::move(other.b)) {}

    void setPixel(uchar _r, uchar _g, uchar _b)
    {
        r = _r;
        g = _g;
        b = _b;
    }
    
    const pixel& operator =(const pixel& other)
    {
        this->r = other.r;
        this->g = other.g;
        this->b = other.b;
        
        return *this;
    }
    
    pixel& operator =(pixel&& other) noexcept
    {
        this->r = std::move(other.r);
        this->g = std::move(other.g);
        this->b = std::move(other.b);

        return *this;
    }

    pixel& operator *=(double koef)
    {
        this->r = koef * this->r;
        this->g = koef * this->g;
        this->b = koef * this->b;

        return *this;
    }

    pixel operator *(double koef) const
    {
        return pixel(koef * this->r, koef * this->g, koef * this->g);
    }

    bool operator ==(const pixel& other) const
    {
        return (this->r == other.r) && (this->g == other.g) && (this->b == other.b);
    }
    
    bool operator !=(const pixel& other) const
    {
        return (this->r != other.r) || (this->g != other.g) || (this->b != other.b);
    }
};

#endif /* pixel_h */
