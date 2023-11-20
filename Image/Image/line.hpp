//
//  line.hpp
//  Image
//
//  Created by Дмитрий  on 16.11.2023.
//

#pragma once

#include "includes.h"

class Line
{
private:
    int line_type, line_h;
    double line_k, line_sdv;
    enum { normalLine = 1, yconst = 2, xconst = 3 };
    
public:
    Line(const std::pair<int, int>& dot1, const std::pair<int, int>& dot2);
    std::pair<int, int> nextDot(const std::pair<int, int>& cur);
    int getType() { return line_type; }
    int getH() { return line_h; }
    double getK() { return line_k; }
    double getSdv() { return line_sdv;}
    
};

Line::Line(const std::pair<int, int>& dot1, const std::pair<int, int>& dot2)
{
    if ((std::get<0>(dot2) - std::get<0>(dot1) == 0) && (std::get<1>(dot2) - std::get<1>(dot1) == 0))
    {
        throw "Invalid coordinates of triangle vertices";
    }
    
    else if (abs(std::get<0>(dot2) - std::get<0>(dot1)) < 2)
    {
        line_type = xconst;
        line_h = (std::get<1>(dot2) - std::get<1>(dot1)) > 0 ? 1 : -1;
        //std::get<0>(dot2) = std::get<0>(dot1);
        line_k = std::numeric_limits<double>::max();
    }
    
    else if (abs(std::get<1>(dot2) - std::get<1>(dot1)) < 2)
    {
        line_type = 2;
        line_h = (std::get<0>(dot2) - std::get<0>(dot1)) > 0 ? 1 : -1;
        //std::get<1>(dot2) = std::get<1>(dot1);
    }
    
    else
    {
        line_type = 1;
        line_k = (std::get<1>(dot2) - std::get<1>(dot1)) / (std::get<0>(dot2) - std::get<0>(dot1));
        line_sdv = std::get<1>(dot2) - line_k * std::get<1>(dot2);
        line_h = (std::get<0>(dot2) - std::get<0>(dot1)) < 0 ? 1 : -1;
    }
}

std::pair<int, int> Line::nextDot(const std::pair<int, int>& cur)
{
    if (line_type == 1)
    {
        if (std::get<0>(cur) >= std::get<1>(cur)) return std::pair<int, int>(std::get<0>(cur) + line_h, line_k * (std::get<0>(cur) + line_h) + line_sdv);
        else return std::pair<int, int>((std::get<1>(cur) - line_sdv) / line_k, std::get<1>(cur) + line_h);
    }
    else if (line_type == 2) return std::pair<int, int>(std::get<0>(cur) + line_h, std::get<1>(cur));
    else return std::pair<int, int>(std::get<0>(cur), std::get<1>(cur) + line_h);
}
