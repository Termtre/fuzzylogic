//
//  instruments.h
//  fuzzylogic
//
//  Created by Дмитрий  on 20.11.2023.
//

#ifndef instruments_h
#define instruments_h

#include "BMP.h"
#include "fuzzylogic.h"

class Instruments : protected BMP
{
private:
    std::vector<pixel> image;
    int width;
    int height;
    
private:
    
public:
    Instruments(const BMP& bmpImage);
    ~Instruments();
    
    void exportImage(BMP& bmpImage);
    
    void createLine();
};

#endif /* instruments_h */
