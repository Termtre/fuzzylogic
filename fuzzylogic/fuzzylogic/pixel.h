//
//  pixel.h
//  Image
//
//  Created by Дмитрий  on 20.11.2023.
//

#ifndef pixel_h
#define pixel_h

#define uchar unsigned char

struct pixel
{
    uchar r;
    uchar g;
    uchar b;
    
    pixel() : r(0), g(0), b(0) {}
    pixel(uchar _r, uchar _g, uchar _b) : r(_r), g(_g), b(_b) {}
    
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