//
//  main.cpp
//  Image
//
//  Created by Дмитрий  on 25.09.2023.
//

#include <iostream>
#include <iomanip>
#include "instruments.h"

int main(int argc, const char * argv[])
{
    std::time_t result = std::time(nullptr);
    std::string date = std::ctime(&result);
    
    std::string url = "square.bmp";
    BMP newImage;
    newImage.importImage("source/" + url);
    
    Instruments line(newImage);
    //line.createLine();
    //line.exportImage(newImage);
    //newImage.exportImage("results/" + date + ".bmp");
    
    return 0;
}
