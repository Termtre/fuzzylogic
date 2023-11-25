//
//  line.hpp
//  Image
//
//  Created by Дмитрий  on 16.11.2023.
//

#pragma once

#include <cmath>
#include "dot.h"

struct Line
{
    int line_type = 0;
    double line_k = 0., line_sdv = 0., line_h = 0.;
    enum { normalLine = 1, yconst = 2, xconst = 3 };
    
    Line(const dot& dot1, const dot& dot2)
    {
        if (((dot2.x - dot1.x) == 0) && ((dot2.y - dot1.y) == 0))
        {
            throw "Invalid coordinates";
        }

        else if (abs(dot2.x - dot1.x) == 0)
        {
            line_type = xconst;
            line_k = std::numeric_limits<double>::max();
        }

        else if (abs(dot2.y - dot1.y) == 0)
        {
            line_type = yconst;
            line_k = 0.0;
        }

        else
        {
            line_type = normalLine;
            line_k = static_cast<double>(dot2.y - dot1.y) / static_cast<double>(dot2.x - dot1.x);
            line_sdv = static_cast<double>(dot2.y) - line_k * static_cast<double>(dot2.x);
        }
    }

    void changeSDV(double sdv)
    {
        line_sdv += sdv;
    }

    dot nextDot(const dot& cur)
    {
        if (line_type == normalLine)
        {
            //if (cur.x >= cur.y) return dot(cur.x + line_h, line_k * (cur.x + line_h) + line_sdv);
            //else return dot((cur.y + line_h - line_sdv) / line_k, cur.y + line_h);
            if (abs(line_k) <= 1) return dot(cur.x + line_h, line_k * (cur.x + line_h) + line_sdv);
            else return dot((cur.y + line_h - line_sdv) / line_k, cur.y + line_h);
            //return dot(static_cast<double>(cur.x) + line_h, line_k * (static_cast<double>(cur.x) + line_h) + line_sdv);
        }
        else if (line_type == yconst) return dot(static_cast<double>(cur.x) + line_h, cur.y + line_sdv);
        else return dot(cur.x + line_sdv, static_cast<double>(cur.y) + line_h);
    }
    
    void calcH(const dot& from, const dot& to)
    {
        if (line_type == normalLine)
        {
            line_h = to.x >= from.x ? 1. : -1.;
        }
        else if (line_type == yconst) line_h = to.x >= from.x ? 1. : -1.;
        else line_h = to.y >= from.y ? 1. : -1.;
    }
};
