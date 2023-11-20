//
//  main.cpp
//  Image
//
//  Created by Дмитрий  on 25.09.2023.
//

#include <iostream>
#include <iomanip>
#include "BMP.hpp"
#include "line.hpp"

int main(int argc, const char * argv[])
{
    /*std::time_t result = std::time(nullptr);
    std::string date = std::ctime(&result);
    
    std::string url = "square";
    BMP newImage;
    newImage.createImage(600, 600);
    //newImage.importImage("source/" + url + ".bmp");
    //newImage.greyFilter(0.30, 0.63, 0.07);
    //newImage.horSmear();
    //newImage.smearTriangle();
    //newImage.smearSquare();
    //newImage.clearColor();
    //newImage.exportImage("source/" + url + ".bmp");
    newImage.vertSmear();
    newImage.exportImage("results/" + date + ".bmp");*/
    
    Line line1(std::pair<int, int>());
    
    return 0;
}
