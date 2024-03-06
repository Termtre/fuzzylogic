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
#include <random>

int main(int argc, const char * argv[])
{
    srand(time(NULL));

    std::time_t result = std::time(nullptr);
    std::string date = std::ctime(&result);
    
    std::string url = "loh";
    std::string url2 = "Mandrill";
    std::string url3 = "sumExperiment2";
    std::string url4 = "toclear";
    std::string bmp = ".bmp";
    std::cout << date << std::endl;
    BMP newImage;
    BMP newImage2;
    BMP newImage3;
    BMP newImage4;
    double seconds;
    try
    {

        newImage.importImage("source/" + url + bmp);
        newImage2.importImage("source/" + url2 + bmp);
        //newImage4.importImage("source/" + url4 + bmp);
        std::cout << newImage.width() << " " << newImage.height() << std::endl;
        //Instruments line(newImage);
        //line.createLine();
        clock_t start = clock();
        newImage3 = newImage2 + newImage;// +newImage4;
        //line.testSmearTriangle(0.5);
        //line.testSmearSquare(1.);
        //line.smearCircle(1.);
        //line.smearSimpleLine(1.0);
        //line.makeRandomNoise(.05);
        clock_t end = clock();
        seconds = (double)(end - start) / CLOCKS_PER_SEC;
        //line.exportImage(newImage);
        newImage3.exportImage("results/" + url + url2 + bmp);
    }
    catch (const char* msg)
    {
        std::cout << msg << std::endl;
    }
    
    std::cout << "Time: " << seconds << std::endl;

    return 0;
}
