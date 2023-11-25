//
//  main.cpp
//  Image
//
//  Created by Дмитрий  on 25.09.2023.
//

#pragma warning(disable : 4996)

#include <iostream>
#include <iomanip>
#include "BMP.h"
#include "instruments.h"

int main(int argc, const char * argv[])
{
    std::time_t result = std::time(nullptr);
    std::string date = std::ctime(&result);
    
    std::string url = "realSquare.bmp";
    std::cout << date << std::endl;
    BMP newImage;

    try
    {
        newImage.importImage("source/" + url);
        std::cout << newImage.width() << " " << newImage.height() << std::endl;
        Instruments line(newImage);
        //line.createLine();
        line.testSmearSquare(.3);
        line.exportImage(newImage);
        newImage.exportImage("results/" + url + ".bmp");
    }
    catch (const char* msg)
    {
        std::cout << msg << std::endl;
    }
    
    return 0;
}
