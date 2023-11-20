//
//  dot.h
//  Image
//
//  Created by Дмитрий  on 20.11.2023.
//

#ifndef dot_h
#define dot_h

struct dot
{
    int x;
    int y;
    
    dot(int _x, int _y) : x(_x), y(_y) {}
    const dot& operator =(const dot& other);
};

const dot& dot::operator =(const dot& other)
{
    this->x = other.x;
    this->y = other.y;
    
    return *this;
}

#endif /* dot_h */
