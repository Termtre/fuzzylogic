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
#include <ctime>

int main(int argc, const char * argv[])
{
    std::time_t result = std::time(nullptr);
    std::string date = std::ctime(&result);
    
    std::string url = "triangle.bmp";
    std::cout << date << std::endl;
    BMP newImage;
    double seconds;
    try
    {

        newImage.importImage("source/" + url);
        std::cout << newImage.width() << " " << newImage.height() << std::endl;
        Instruments line(newImage);
        //line.createLine();
        clock_t start = clock();
        line.testSmearTriangle(0.5);
        clock_t end = clock();
        seconds = (double)(end - start) / CLOCKS_PER_SEC;
        line.exportImage(newImage);
        newImage.exportImage("results/" + url + ".bmp");
    }
    catch (const char* msg)
    {
        std::cout << msg << std::endl;
    }
    
    std::cout << "Time: " << seconds << std::endl;

    return 0;
}
