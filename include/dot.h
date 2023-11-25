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
    
    dot() {}
    dot(int _x, int _y) : x(_x), y(_y) {}
    dot(const dot& other) : x(other.x), y(other.y) {}
    dot(dot&& other) : x(std::move(other.x)), y(std::move(other.y)) {}

    const dot& operator =(const dot& other)
    {
        this->x = other.x;
        this->y = other.y;

        return *this;
    }

    dot& operator =(dot&& other)
    {
        this->x = std::move(other.x);
        this->y = std::move(other.y);

        return *this;
    }

    bool operator ==(const dot& other)
    {
        return this->x == other.x && this->y == other.y;
    }

    bool operator !=(const dot& other)
    {
        return this->x != other.x || this->y != other.y;
    }

};

#endif /* dot_h */
