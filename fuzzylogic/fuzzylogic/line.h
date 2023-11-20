//
//  line.hpp
//  Image
//
//  Created by Дмитрий  on 16.11.2023.
//

#pragma once

#include <cmath>
#include "dot.h"

class Line
{
private:
    int line_type, line_h;
    double line_k, line_sdv;
    enum { normalLine = 1, yconst = 2, xconst = 3 };
    
public:
    Line(const dot& dot1, const dot& dot2);
    dot nextDot(const dot& cur);
    int getType() { return line_type; }
    int getH() { return line_h; }
    double getK() { return line_k; }
    double getSdv() { return line_sdv;}
    
};

Line::Line(const dot& dot1, const dot& dot2)
{
    if (((dot2.x - dot1.x) == 0) && ((dot2.y - dot1.y) == 0))
    {
        throw "Invalid coordinates";
    }
    
    else if ((dot2.x - dot1.x) == 0)
    {
        line_type = xconst;
        line_h = (dot2.y - dot1.y) > 0 ? 1 : -1;
        line_k = std::numeric_limits<double>::max();
    }
    
    else if ((dot2.y - dot1.y) == 0)
    {
        line_type = yconst;
        line_h = (dot2.x - dot1.x) > 0 ? 1 : -1;
    }
    
    else
    {
        line_type = normalLine;
        line_k = (dot2.y - dot1.y) / (dot2.x - dot1.x);
        line_sdv = dot2.y - line_k * dot2.x;
        if (dot2.x >= dot2.y)
        {
            line_h = (dot2.x - dot1.x) > 0 ? 1 : -1;
        }
        else
        {
            line_h = (dot2.y - dot1.y) > 0 ? 1 : -1;
        }
    }
}

dot Line::nextDot(const dot& cur)
{
    if (line_type == normalLine)
    {
        if (cur.x >= cur.y) return dot(cur.x + line_h, line_k * (cur.x + line_h) + line_sdv);
        else return dot((cur.y - line_sdv) / line_k, cur.y + line_h);
    }
    else if (line_type == yconst) return dot(cur.x + line_h, cur.y);
    else return dot(cur.x, cur.y + line_h);
}
