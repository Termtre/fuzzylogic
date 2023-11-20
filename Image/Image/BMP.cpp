//
//  BMP.cpp
//  Image
//
//  Created by Дмитрий  on 25.09.2023.
//

#include "BMP.hpp"
#define _USE_MATH_DEFINES

#include "line.hpp"

void BMP::create_horizontal_clear_rainbow()
{
    heightColor = bmp_height / 8;
    int r = 255, g = 255, b = 255;
    int def = 0;
    
    for (int y = 0; y < bmp_height; y++)
    {
        if (!(y % heightColor))
        {
            def % 2 == 1 ? b = 255 : b = 0;
            if (!(def % 2)) g == 0 ? g = 255 : g = 0;
            if (!(def % 4)) r == 0 ? r = 255 : r = 0;
            def++;
        }
     
        for (int x = 0; x < bmp_width; x++)
        {
            image[(bmp_height - y - 1) * bmp_width + (bmp_width - x - 1)] = pixel(r, g, b);
            greyImage[(bmp_height - y - 1) * bmp_width + (bmp_width - x - 1)] = image[(bmp_height - y - 1) * bmp_width + (bmp_width - x - 1)];
        }
    }
}

void BMP::create_vertical_clear_rainbow()
{
    heightColor = bmp_width / 8;
    int r = 255, g = 255, b = 255;
    int def = 0;
    
    for (int x = 0; x < bmp_width; x++)
    {
        if (!(x % heightColor))
        {
            def % 2 == 1 ? b = 255 : b = 0;
            if (!(def % 2)) g == 0 ? g = 255 : g = 0;
            if (!(def % 4)) r == 0 ? r = 255 : r = 0;
            def++;
        }
     
        for (int y = 0; y < bmp_height; y++)
        {
            image[(bmp_height - y - 1) * bmp_width + (bmp_width - x - 1)] = pixel(r, g, b);
            greyImage[(bmp_height - y - 1) * bmp_width + (bmp_width - x - 1)] = image[(bmp_height - y - 1) * bmp_width + (bmp_width - x - 1)];
        }
    }
}


void BMP::create_circle(int radius)
{
    int x0 = bmp_width / 2;
    int y0 = bmp_height / 2;
    int y1;
    int R = pow(floor(bmp_height / 2), 2);
    
    for (int y = 0 ; y < bmp_height; y++)
    {
        y1 = pow(y - y0, 2);
        
        for (int x = 0; x < bmp_width; x++)
        {
            if (pow(x - x0, 2) + y1 <= R)
            {
                image[y * bmp_width + x] = pixel(255, 0, 0);
                greyImage[y * bmp_width + x] = pixel(255, 0, 0);
            }
            else
            {
                image[y * bmp_width + x] = pixel(255, 255, 255);
                greyImage[y * bmp_width + x] = pixel(255, 255, 255);
            }
        }
    }
}

void BMP::create_square(int side, pixel out_color, pixel in_color)
{
    int x0 = bmp_width / 2;
    int y0 = bmp_height / 2;
    int y1;
    
    for (int y = 0 ; y < bmp_height; y++)
    {
        y1 = abs(y - y0);
        
        for (int x = 0; x < bmp_width; x++)
        {
            int x1 = abs(x - x0);
            if ((abs(x1 - y1) + abs(x1 + y1)) <= side)
            {
                image[y * bmp_width + x] = in_color;
                greyImage[y * bmp_width + x] = in_color;
            }
            else
            {
                image[y * bmp_width + x] = out_color;
                greyImage[y * bmp_width + x] = out_color;
            }
        }
    }
}

void BMP::create_triangle(int side, pixel out_color, pixel in_color)
{
    int x0 = bmp_width / 2;
    int y0 = bmp_height / 2.5;
    int y1;
    
    for (int y = 0 ; y < bmp_height; y++)
    {
        y1 = abs(y - y0);
        
        for (int x = 0; x < bmp_width; x++)
        {
            int x1 = abs(x - x0);
            if (y > y0 && x1 + y1 <= side)
            {
                image[y * bmp_width + x] = in_color;
                greyImage[y * bmp_width + x] = in_color;
            }
            else
            {
                image[y * bmp_width + x] = out_color;
                greyImage[y * bmp_width + x] = out_color;
            }
        }
    }
}

void trash()
{
    std::vector<std::pair<pixel, int>> temp = {std::pair<pixel, int>(pixel(255, 255, 0), 10)};
    //create_vertical_streakes(4,)
    
    //heightColor = bmp_height / 8;
    //int r = 255, g = 255, b = 255;
    //int def = 0;
    //pixel rgb;
    
    
    //for (int i = 0; i < bmp_width * bmp_height; i++)
    //{
    //    image[i] = pixel(r, 128, 0);
    //    greyImage[i] = image[i];
    //}
    /*for (int y = 0; y < bmp_height; y++)
     {
     if (!(y % heightColor))
     {
     def % 2 == 1 ? b = 255 : b = 0;
     if (!(def % 2)) g == 0 ? g = 255 : g = 0;
     if (!(def % 4)) r == 0 ? r = 255 : r = 0;
     def++;
     }
     
     for (int x = 0; x < bmp_width; x++)
     {
     image[(bmp_height - y - 1) * bmp_width + (bmp_width - x - 1)] = pixel(r, g, b);
     greyImage[(bmp_height - y - 1) * bmp_width + (bmp_width - x - 1)] = image[(bmp_height - y - 1) * bmp_width + (bmp_width - x - 1)];
     }
     }*/
    
    /*for (int y = 0; y < bmp_height; y++)
     {
     for (int x = 0; x < bmp_width; x++)
     {
     int x1 = (bmp_width - x - 1);
     int y1 = (bmp_height - y - 1);
     
     if (y < bmp_height / 4)
     {
     image[y1 * bmp_width + x1].r = 0;
     image[y1 * bmp_width + x1].g = 255;
     image[y1 * bmp_width + x1].b = 0;
     }
     else if (y >= bmp_height / 4 && y < bmp_height / 2)
     {
     image[y1 * bmp_width + x1].r = 255;
     image[y1 * bmp_width + x1].g = 0;
     image[y1 * bmp_width + x1].b = 0;
     }
     else
     {
     image[y1 * bmp_width + x1].r = 0;
     image[y1 * bmp_width + x1].g = 255;
     image[y1 * bmp_width + x1].b = 255;
     }
     
     greyImage[y1 * bmp_width + x1] = image[y1 * bmp_width + x1];
     }
     }*/
    
    /*for (int y = 0; y < bmp_height; y++)
    {
        int y1 = (bmp_height - y - 1);
        
        if (y < bmp_height / 7) rgb = pixel(255, 0, 0);
        else if (y >= bmp_height / 7 && y < 2 * bmp_height / 7) rgb = pixel(255, 128, 0);
        else if (y >= 2 * bmp_height / 7 && y < 3 * bmp_height / 7) rgb = pixel(255, 255, 0);
        else if (y >= 3 * bmp_height / 7 && y < 4 * bmp_height / 7) rgb = pixel(0, 255, 0);
        else if (y >= 4 * bmp_height / 7 && y < 5 * bmp_height / 7) rgb = pixel(0, 255, 255);
        else if (y >= 5 * bmp_height / 7 && y < 6 * bmp_height / 7) rgb = pixel(0, 0, 255);
        else rgb = pixel(255, 0, 255);
        
        for (int x = 0; x < bmp_width; x++)
        {
            int x1 = (bmp_width - x - 1);

            image[y1 * bmp_width + x1] = rgb;
        }
    }*/
}

void BMP::createImage(int _width, int _height)
{
    clear();
    bmp_width = _width;
    bmp_height = _height;
    bmp_padding = (4 - (bmp_width * 3) % 4) % 4;
    bmp_size = 54 + bmp_width * bmp_height * 3 + bmp_padding * bmp_width;
    image = std::vector<pixel>(bmp_width * bmp_height);
    greyImage = std::vector<pixel>(bmp_width * bmp_height);
    
    // BMP name
    header[0] = 'B';
    header[1] = 'M';
    //File size
    header[2] = bmp_size;
    header[3] = bmp_size >> 8;
    header[4] = bmp_size >> 16;
    header[5] = bmp_size >> 24;
    //Reserved
    header[6] = 0;
    header[7] = 0;
    header[8] = 0;
    header[9] = 0;
    //Padding to Colors matrix
    header[10] = 54;
    header[11] = 0;
    header[12] = 0;
    header[13] = 0;
    //Header size
    header[14] = 40;
    header[15] = 0;
    header[16] = 0;
    header[17] = 0;
    //Width
    header[18] = bmp_width;
    header[19] = bmp_width >> 8;
    header[20] = bmp_width >> 16;
    header[21] = bmp_width >> 24;
    //Height
    header[22] = bmp_height;
    header[23] = bmp_height >> 8;
    header[24] = bmp_height >> 16;
    header[25] = bmp_height >> 24;
    //For windows
    header[26] = 1;
    header[27] = 0;
    //Bits per pixel
    header[28] = 24;
    header[29] = 0;
    //Compression
    header[30] = 0;
    header[31] = 0;
    header[32] = 0;
    header[33] = 0;
    //Compression
    header[34] = 0;
    header[35] = 0;
    header[36] = 0;
    header[37] = 0;
    //X per meter
    header[38] = 2834;
    header[39] = 2834 >> 8;
    header[40] = 2834 >> 16;
    header[41] = 2834 >> 24;
    //Y per meter
    header[42] = 2834;
    header[43] = 2834 >> 8;
    header[44] = 2834 >> 16;
    header[45] = 2834 >> 24;
    //Total colors
    header[46] = 0;
    header[47] = 0;
    header[48] = 0;
    header[49] = 0;
    //Important colors
    header[50] = 0;
    header[51] = 0;
    header[52] = 0;
    header[53] = 0;
    
    //create_square(300, pixel(255, 255, 0), pixel(0, 255, 255));
    //create_vertical_clear_rainbow();
    //create_triangle(200, pixel(255, 255, 0), pixel(0, 255, 255));
    for (int y = 0; y < bmp_height; y++)
    {
        pixel color = y < bmp_height / 2 ? pixel(255, 0, 0) : pixel(0, 0, 255);
        
        for (int x = 0; x < bmp_width; x++)
        {
            image[y * bmp_width + x] = pixel(color.r, color.g, color.b);
        }
    }
}

void BMP::interpretationHeader()
{
    if (!isEmpty())
    {
        std::cout << header[0] << header[1] << std::endl;
        std::cout << *reinterpret_cast<int*>(&header[2]) << std::endl;
        std::cout << *reinterpret_cast<int*>(&header[6]) << std::endl;
        std::cout << *reinterpret_cast<int*>(&header[10]) << std::endl;
        std::cout << *reinterpret_cast<int*>(&header[14]) << std::endl;
        std::cout << *reinterpret_cast<int*>(&header[18]) << std::endl;
        std::cout << *reinterpret_cast<int*>(&header[22]) << std::endl;
        std::cout << *reinterpret_cast<int*>(&header[26]) << std::endl;
        std::cout << *reinterpret_cast<int*>(&header[28]) << std::endl;
        std::cout << *reinterpret_cast<int*>(&header[30]) << std::endl;
        std::cout << *reinterpret_cast<int*>(&header[34]) << std::endl;
        std::cout << *reinterpret_cast<int*>(&header[38]) << std::endl;
        std::cout << *reinterpret_cast<int*>(&header[42]) << std::endl;
        std::cout << *reinterpret_cast<int*>(&header[46]) << std::endl;
        std::cout << *reinterpret_cast<int*>(&header[50]) << std::endl;


    }
}

void BMP::importImage(std::string url)
{
    if (!isEmpty()) clear();
    
    std::ifstream openFile(url, std::ios::in | std::ios::binary);
    
    if (!openFile.is_open())
    {
        throw "File didn't open!";
    }
    
    openFile.read(reinterpret_cast<char*>(header), 54);
    
    if (header[0] != 'B' || header[1] != 'M')
    {
        throw "This file isn't BMP format!";
    }
    
    bmp_size = *reinterpret_cast<int*>(&header[0x02]);
    bmp_width = *reinterpret_cast<int*>(&header[0x12]);
    bmp_height = *reinterpret_cast<int*>(&header[0x16]);
    
    bmp_padding = (4 - (bmp_width * 3) % 4) % 4;
    
    for (int y = 0; y < bmp_height; y++)
    {
        for (int x = 0; x < bmp_width; x++)
        {
            uchar color[3];
            
            openFile.read(reinterpret_cast<char*>(color), 3);
            
            image.push_back(pixel(color[2], color[1], color[0]));
            greyImage.push_back(image.back());
        }
        
        openFile.ignore(bmp_padding);
    }
    
    openFile.close();
}

void BMP::exportImage(std::string url)
{
    if (isEmpty())
    {
        throw "Image hasn't been found!";
    }
    
    std::ofstream openFile(url, std::ios::out | std::ios::binary);
    
    if (!openFile.is_open())
    {
        throw "File didn't open!";
    }
    
    openFile.write(reinterpret_cast<char*>(header), 54);
    
    for (int y = 0; y < bmp_height; y++)
    {
        for (int x = 0; x < bmp_width; x++)
        {
            uchar color[3];
            color[0] = image[y * bmp_width + x].b;
            color[1] = image[y * bmp_width + x].g;
            color[2] = image[y * bmp_width + x].r;
            //color[0] = greyImage[y * bmp_width + x].b;
            //color[1] = greyImage[y * bmp_width + x].g;
            //color[2] = greyImage[y * bmp_width + x].r;
            //color[0] = mask[y * bmp_width + x].b;
            //color[1] = mask[y * bmp_width + x].g;
            //color[2] = mask[y * bmp_width + x].r;
            openFile.write(reinterpret_cast<char*>(color), 3);
        }
        
        openFile.write(reinterpret_cast<char*>(padding), bmp_padding);
    }
    
    openFile.close();
}

int BMP::size()
{
    return bmp_size;
}

int BMP::width()
{
    return bmp_width;
}

int BMP::height()
{
    return bmp_height;
}

void BMP::greyFilter(double _r, double _g, double _b)
{
    for (int i = 0; i < bmp_width * bmp_height; i++)
    {
        int grey = greyImage[i].r * _r + greyImage[i].g * _g + greyImage[i].b * _b;
        
        image[i] = pixel(grey, grey, grey);
    }
}

void BMP::sobel(int a, int b, double d)
{
    // r = 0.3 g = 0.59 b = 0.11
    
    greyFilter(0.3, 0.59, 0.11);
    
    int Sy[9] = { a, b, a, 0, 0, 0, -a, -b, -a };
    int Sx[9] = { a, 0, -a, b, 0, -b, a, 0, -a };
    
    for(int y = 0; y < bmp_height; y++)
    {
        for (int x = 0; x < bmp_width; x++)
        {
            int jacob[9];
            
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    if ((y - 1 + i) < 0 ||
                        (x - 1 + j) < 0 ||
                        (y - 1 + i) >= bmp_height ||
                        (x - 1 + j) >= bmp_width)
                    {
                        jacob[i * 3 + j] = 0;
                    }
                    else
                    {
                        jacob[i * 3 + j] = static_cast<int>(greyImage[(y - 1 + i) * bmp_width + (x - 1 + j)].r);
                    }
                }
            }
            
            int Gx = 0;
            int Gy = 0;
            
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    Gx += jacob[i * 3 + j] * Sx[i * 3 + j];
                    Gy += jacob[i * 3 + j] * Sy[i * 3 + j];
                }
            }
            
            int G = static_cast<int>(sqrt(Gx * Gx + Gy * Gy)) / d;
            
            G > 127 ? mask.push_back(pixel(255, 255, 255)) : mask.push_back(pixel(0, 0, 0));
        }
    }
}

void BMP::cartoonFilter()
{
    if (isEmpty())
    {
        throw "Image haven't found!";
    }
    
    sobel(1, 2, 0.3);
    
    for (int i = 0; i < bmp_width * bmp_height; i++)
    {
        if (mask[i].r == 255)  image[i].setPixel(0, 0, 0);
    }
}

void BMP::clearColor()
{
    if (isEmpty())
    {
        throw "Image haven't found!";
    }
    
    int k = 169;
    int r, g, b;
    
    for (int y = 0; y < bmp_height; y++)
    {
        r = image[y * bmp_width].r >= k ? 255 : 0;
        g = image[y * bmp_width].g >= k ? 255 : 0;
        b = image[y * bmp_width].b >= k ? 255 : 0;
        
        for (int x = 0; x < bmp_width; x++)
        {
            image[y * bmp_width + x] = pixel(r, g, b);
        }
    }
}

bool BMP::isEmpty()
{
    return image.empty();
}

void BMP::clear()
{
    if (!isEmpty())
    {
        image.clear();
        mask.clear();
        greyImage.clear();
        bmp_size = 0;
        bmp_width = 0;
        bmp_height = 0;
    }
}

void BMP::horizontalSmear(int left, int middle, int right, const pixel& leftColor, const pixel& rightColor)
{
    int r1 = leftColor.r;
    int g1 = leftColor.g;
    int b1 = leftColor.b;
    int r2 = rightColor.r;
    int g2 = rightColor.g;
    int b2 = rightColor.b;
    int rr = std::abs(r1 - r2);
    int gr = std::abs(g1 - g2);
    int br = std::abs(b1 - b2);
    int r = 0, g = 0, b = 0;
    
    if (rr == 0) r = r1;
    if (gr == 0) g = g1;
    if (br == 0) b = b1;

    std::cout << r << " " << g << " " << b << std::endl;
    for (int i = left; i < right; i++)
    {
        double f1 = straight_memFunction(i, left - 1, left, right); // Верхний цвет(нижний)
        double f2 = straight_memFunction(i, left, right, right + 1); // Нижний цвет(верхний)
        
        if (rr != 0) r = r1 != 0 ? f1 * r1 : f2 * r2;
        if (gr != 0) g = g1 != 0 ? f1 * g1 : f2 * g2;
        if (br != 0) b = b1 != 0 ? f1 * b1 : f2 * b2;
        
        for (int y = 0; y < bmp_height; y++)
        {
            image[y * bmp_width + i] = pixel(r, g, b);
        }
    }
}

void BMP::verticalSmear(int down, int middle, int up, const pixel& downColor, const pixel& upColor)
{
    int r1 = downColor.r;
    int g1 = downColor.g;
    int b1 = downColor.b;
    int r2 = upColor.r;
    int g2 = upColor.g;
    int b2 = upColor.b;
    int rr = std::abs(r1 - r2);
    int gr = std::abs(g1 - g2);
    int br = std::abs(b1 - b2);
    int r = 0, g = 0, b = 0;
    
    if (rr == 0) r = r1;
    if (gr == 0) g = g1;
    if (br == 0) b = b1;

    std::cout << r << " " << g << " " << b << std::endl;
    for (int i = down; i < up; i++)
    {
        double f1 = straight_memFunction(i, down - 1, down, up); // Верхний цвет(нижний)
        double f2 = straight_memFunction(i, down, up, up + 1); // Нижний цвет(верхний)
        
        if (rr != 0) r = r1 != 0 ? f1 * r1 : f2 * r2;
        if (gr != 0) g = g1 != 0 ? f1 * g1 : f2 * g2;
        if (br != 0) b = b1 != 0 ? f1 * b1 : f2 * b2;
        
        for (int x = 0; x < bmp_width; x++)
        {
            image[i * bmp_width + x] = pixel(r, g, b);
        }
    }
}

void BMP::horSmear()
{
    int left = 0, middle = 0, right = 0, x1;
    
    for (int x = 0; x < bmp_width; x++)
    {
        if ((x + 1) < bmp_width && image[x] != image[x + 1])
        {
            x1 = x;
            left = !right ? ceil(x / 2) + 1 : right;
            middle = x + 1;
            x++;
            
            while ((x + 1) < bmp_width && image[x + 1] == image[x])
            {
                x++;
            }
            
            right = x - ceil((x - middle) / 2);
            x = right - 1;
            
            std::cout << "right: " << right << " middle: " << middle << " left: " << left << std::endl;
            
            horizontalSmear(left, middle, right, image[x1], image[x1 + 1]);
        }
    }
}

void BMP::vertSmear()
{
    int down = 0, middle = 0, up = 0, y1;
    
    for (int y = 0; y < bmp_height; y++)
    {
        if ((y + 1) < bmp_height && image[y * bmp_width] != image[(y + 1) * bmp_width])
        {
            y1 = y;
            down = !up ? ceil(y / 2) + 1 : up;
            middle = y + 1;
            y++;
            
            while ((y + 1) < bmp_height && image[(y + 1) * bmp_width] == image[y * bmp_width])
            {
                y++;
            }
            
            up = y - ceil((y - middle) / 2);
            y = up - 1;
            
            std::cout << "up: " << up << " middle: " << middle << " down: " << down << std::endl;
            
            verticalSmear(down, middle, up, image[y1 * bmp_width], image[(y1 + 1) * bmp_width]);
        }
    }
}

void BMP::triangleSmear(const std::vector<std::pair<int, int>>& sides, double angle, const pixel& in, const pixel& out)
{
    double matrixRotation[2][2] = { { cos(angle), -sin(angle) }, { sin(angle), cos(angle) } };
    
    int rr = std::abs(out.r - in.r);
    int gr = std::abs(out.g - in.g);
    int br = std::abs(out.b - in.b);
    int r = 0, g = 0, b = 0;
    
    if (rr == 0) r = out.r;
    if (gr == 0) g = out.g;
    if (br == 0) b = out.b;

    std::cout << r << " " << g << " " << b << std::endl;
    
    for (int i = std::get<1>(sides[0]), j = 0; i < std::get<1>(sides[1]); i++, j++)
    {
        double f1y = straight_memFunction(i, std::get<1>(sides[0]) - 1, std::get<1>(sides[0]), std::get<1>(sides[1])); // Верхний цвет(нижний)
        double f2y = straight_memFunction(i, std::get<1>(sides[0]), std::get<1>(sides[1]), std::get<1>(sides[1]) + 1); // Нижний цвет(верхний)
        
        //if (rr != 0) r = out.r != 0 ? f1 * out.r : f2 * in.r;
        //if (gr != 0) g = out.g != 0 ? f1 * out.g : f2 * in.g;
        //if (br != 0) b = out.b != 0 ? f1 * out.b : f2 * in.b;
        
        for (int x = std::get<0>(sides[0]) + j; x < std::get<0>(sides[2]) - j + 1; x++)
        {
            double f1x;
            double f2x;
            if (x < (std::get<0>(sides[2])) / 2)
            {
                f1x = straight_memFunction(x, std::get<0>(sides[0]) - 1, std::get<0>(sides[0]), std::get<0>(sides[1]));
                f2x = straight_memFunction(x, std::get<0>(sides[0]), std::get<0>(sides[1]), std::get<0>(sides[1]) + 1);
            }
            else
            {
                f1x = straight_memFunction(x, std::get<0>(sides[2]) - 1, std::get<0>(sides[2]), std::get<0>(sides[1]));
                f2x = straight_memFunction(x, std::get<0>(sides[2]), std::get<0>(sides[1]), std::get<0>(sides[1]) + 1);
            }
            
            double Rs1 = sqrt(pow(f1y, 2) + pow(f1x, 2));
            double Rs2 = sqrt(pow(f2y, 2) + pow(f2x, 2));
            
            //double Rs1 = (f1y + f1x) / 2;
            //double Rs2 = (f2y + f2x) / 2;
            
            std::cout << Rs1 << " " << Rs2 << std::endl;
            
            if (rr != 0) r = out.r != 0 ? Rs1 * out.r : Rs2 * in.r;
            if (gr != 0) g = out.g != 0 ? Rs1 * out.g : Rs2 * in.g;
            if (br != 0) b = out.b != 0 ? Rs1 * out.b : Rs2 * in.b;
            
            image[i * bmp_width + x] = pixel(r, g, b);
        }
    }
}

/*std::pair<int, int> BMP::lineFunc(int type, std::pair<int, int> cur, double k, double b, int h)
{
    if (type == normalLine)
    {
        if (std::get<0>(cur) >= std::get<1>(cur)) return std::pair<int, int>(std::get<0>(cur) + h, k * (std::get<0>(cur) + h) + b);
        else return std::pair<int, int>((std::get<1>(cur) - b) / k, std::get<1>(cur) + h);
    }
    else if (type == yconst) return std::pair<int, int>(std::get<0>(cur) + h, std::get<1>(cur));
    else return std::pair<int, int>(std::get<0>(cur), std::get<1>(cur) + h);
 
 if ((std::get<0>(sides[1]) - xM == 0) && (std::get<1>(sides[1]) - yM == 0))
 {
     throw "Invalid coordinates of triangle vertices";
 }
 
 else if (abs(std::get<0>(sides[1]) - xM) < 5)
 {
     type = xconst;
     h = (std::get<1>(sides[1]) - yM) < 0 ? 1 : -1;
     xM = std::get<0>(sides[1]);
     k = std::numeric_limits<double>::max();
 }
 
 else if (abs(std::get<1>(sides[1]) - yM) < 5)
 {
     type = yconst;
     h = (std::get<0>(sides[1]) - xM) < 0 ? 1 : -1;
     yM = std::get<1>(sides[1]);
 }
 
 else
 {
     type = normalLine;
     k = (std::get<1>(sides[1]) - yM) / (std::get<0>(sides[1]) - xM);
     sdv = std::get<1>(sides[1]) - k * xM;
     h = (std::get<0>(sides[1]) - xM) > 0 ? 1 : -1;
 }
}*/

void BMP::testTriangleSmear(const std::vector<std::pair<int, int>>& sides, double angle, const pixel& in, const pixel& out)
{
    std::pair<int, int> dotMedian((std::get<0>(sides[0]) + std::get<0>(sides[2])) / 2, (std::get<1>(sides[0]) + std::get<1>(sides[2])) / 2);
    
    Line median(sides[1], dotMedian);
    
    std::cout << median.getType() << " " << median.getK() << " " << median.getSdv() << " " << median.getH() << std::endl;
    std::cout << std::get<0>(dotMedian) << " " << std::get<1>(dotMedian) << std::endl;
    std::cout << std::get<0>(sides[1]) << " " << std::get<1>(sides[1]) << std::endl;
    
    pixel lessPixel, morePixel;
    
    if (std::get<0>(dotMedian) >= std::get<0>(sides[1]) && std::get<1>(dotMedian) <= std::get<1>(sides[1]))
    {
        lessPixel = out;
        morePixel = in;
    }
    
    else
    {
        lessPixel = in;
        morePixel = out;
    }
    
    int rr = std::abs(lessPixel.r - morePixel.r);
    int gr = std::abs(lessPixel.g - morePixel.g);
    int br = std::abs(lessPixel.b - morePixel.b);
    int r = 0, g = 0, b = 0;
    
    if (rr == 0) r = out.r;
    if (gr == 0) g = out.g;
    if (br == 0) b = out.b;
    
    int lessX, lessY;
    int moreX, moreY;
    
    if (std::get<0>(sides[1]) >= std::get<0>(dotMedian))
    {
        lessX = std::get<0>(dotMedian);
        moreX = std::get<0>(sides[1]);
    }
    
    else
    {
        moreX = std::get<0>(dotMedian);
        lessX = std::get<0>(sides[1]);
    }
    
    if (std::get<1>(sides[1]) >= std::get<1>(dotMedian))
    {
        lessY = std::get<1>(dotMedian);
        moreY = std::get<1>(sides[1]);
    }
    
    else
    {
        moreY = std::get<1>(dotMedian);
        lessY = std::get<1>(sides[1]);
    }
    
    for (int x = std::get<0>(sides[1]), y = std::get<1>(sides[1]); x != std::get<0>(dotMedian) || y != std::get<1>(dotMedian);)
    {
        std::pair<int, int> cur = median.nextDot(std::pair<int, int>(x, y));
        x = std::get<0>(cur);
        y = std::get<1>(cur);
        std::cout << x << " " << y << std::endl;
        double f1, f2;
        
        if (abs(median.getK()) < 0.00001)
        {
            f2 = straight_memFunction(x, lessX - 1, lessX, moreX); // Левый цвет
            f1 = straight_memFunction(x, lessX, moreX, moreX + 1); // Правый цвет
        }
        
        else
        {
            f1 = straight_memFunction(y, lessY - 1, lessY, moreY); // Верхний цвет на картинке (нижний в массиве)
            f2 = straight_memFunction(y, lessY, moreY, moreY + 1); // Нижний цвет на картинке (верхний в массиве)
        }
        
        if (rr != 0) r = lessPixel.r != 0 ? f1 * lessPixel.r : f2 * morePixel.r;
        if (gr != 0) g = lessPixel.g != 0 ? f1 * lessPixel.g : f2 * morePixel.g;
        if (br != 0) b = lessPixel.b != 0 ? f1 * lessPixel.b : f2 * morePixel.b;
        
        image[y * bmp_width + x] = pixel(r, g, b);
        
        //for (int i = )
    }
}

void BMP::p2triangleSmear(std::vector<std::pair<int, int>> sides, double angle, const pixel& in, const pixel& out)
{
    double matrixRotation[2][2] = { { cos(angle), -sin(angle) }, { sin(angle), cos(angle) } };
    
    int rr = std::abs(out.r - in.r);
    int gr = std::abs(out.g - in.g);
    int br = std::abs(out.b - in.b);
    int r = 0, g = 0, b = 0;
    
    if (rr == 0) r = out.r;
    if (gr == 0) g = out.g;
    if (br == 0) b = out.b;

    std::cout << r << " " << g << " " << b << std::endl;
    
    for (int x = std::get<0>(sides[0]), j = 0; x < std::get<0>(sides[1]); x++, j++)
    {
        double f1 = straight_memFunction(x, std::get<0>(sides[0]) - 1, std::get<0>(sides[0]), std::get<0>(sides[1])); // Верхний цвет(нижний)
        double f2 = straight_memFunction(x, std::get<0>(sides[0]), std::get<0>(sides[1]), std::get<0>(sides[1]) + 1); // Нижний цвет(верхний)
        
        if (rr != 0) r = out.r != 0 ? f1 * out.r : f2 * in.r;
        if (gr != 0) g = out.g != 0 ? f1 * out.g : f2 * in.g;
        if (br != 0) b = out.b != 0 ? f1 * out.b : f2 * in.b;
        
        for (int y = std::get<1>(sides[2]) + j; y < std::get<1>(sides[0]) - j + 1; y++)
        {
            image[y * bmp_width + x] = pixel(r, g, b);
        }
    }
}

void BMP::_3p2triangleSmear(std::vector<std::pair<int, int>> sides, double angle, const pixel& in, const pixel& out)
{
    double matrixRotation[2][2] = { { cos(angle), -sin(angle) }, { sin(angle), cos(angle) } };
    
    int rr = std::abs(out.r - in.r);
    int gr = std::abs(out.g - in.g);
    int br = std::abs(out.b - in.b);
    int r = 0, g = 0, b = 0;
    
    if (rr == 0) r = out.r;
    if (gr == 0) g = out.g;
    if (br == 0) b = out.b;

    std::cout << r << " " << g << " " << b << std::endl;
    
    for (int i = std::get<1>(sides[0]), j = 0; i > std::get<1>(sides[1]); i--, j++)
    {
        double f1 = straight_memFunction(i, std::get<1>(sides[1]) - 1, std::get<1>(sides[1]), std::get<1>(sides[0])); // Верхний цвет(нижний)
        double f2 = straight_memFunction(i, std::get<1>(sides[1]), std::get<1>(sides[0]), std::get<1>(sides[0]) + 1); // Нижний цвет(верхний)
        
        if (rr != 0) r = out.r != 0 ? f1 * out.r : f2 * in.r;
        if (gr != 0) g = out.g != 0 ? f1 * out.g : f2 * in.g;
        if (br != 0) b = out.b != 0 ? f1 * out.b : f2 * in.b;
        
        for (int x = std::get<0>(sides[2]) + j; x < std::get<0>(sides[0]) - j + 1; x++)
        {
            image[i * bmp_width + x] = pixel(r, g, b);
        }
    }
}

void BMP::_2ptriangleSmear(std::vector<std::pair<int, int>> sides, double angle, const pixel& in, const pixel& out)
{
    double matrixRotation[2][2] = { { cos(angle), -sin(angle) }, { sin(angle), cos(angle) } };
    
    int rr = std::abs(out.r - in.r);
    int gr = std::abs(out.g - in.g);
    int br = std::abs(out.b - in.b);
    int r = 0, g = 0, b = 0;
    
    if (rr == 0) r = out.r;
    if (gr == 0) g = out.g;
    if (br == 0) b = out.b;

    std::cout << r << " " << g << " " << b << std::endl;
    
    for (int x = std::get<0>(sides[0]), j = 0; x > std::get<0>(sides[1]); x--, j++)
    {
        double f1 = straight_memFunction(x, std::get<0>(sides[1]) - 1, std::get<0>(sides[1]), std::get<0>(sides[0])); // Верхний цвет(нижний)
        double f2 = straight_memFunction(x, std::get<0>(sides[1]), std::get<0>(sides[0]), std::get<0>(sides[0]) + 1); // Нижний цвет(верхний)
        
        if (rr != 0) r = out.r != 0 ? f1 * out.r : f2 * in.r;
        if (gr != 0) g = out.g != 0 ? f1 * out.g : f2 * in.g;
        if (br != 0) b = out.b != 0 ? f1 * out.b : f2 * in.b;
        
        for (int y = std::get<1>(sides[0]) + j; y < std::get<1>(sides[2]) - j + 1; y++)
        {
            image[y * bmp_width + x] = pixel(r, g, b);
        }
    }
}

void triangleSmear()
{
    
}

void BMP::smearTriangle()
{
    std::pair<int, int> s1, s2, s3;
    bool flag = false;
    
    for (int y = 0; y < bmp_height; y++)
    {
        for (int x = 0; x < bmp_width; x++)
        {
            if ((y + 1) != bmp_height && (x + 1) != bmp_width && image[y * bmp_width + x] != image[y * bmp_width + (x + 1)])
            {
                s1 = std::pair<int, int>(x, y);
                flag = true;
                break;
            }
        }
        
        if (flag) break;
    }
    
    if (!flag) return;
    flag = false;
    
    int x0 = std::get<0>(s1);
    int y0 = std::get<1>(s1);
    
    for (int x = x0; x < bmp_width; x++)
    {
        if ((x + 1) != bmp_width && image[y0 * bmp_width + x] != image[y0 * bmp_width + (x + 1)])
        {
            s2 = std::pair(x, y0);
            flag = true;
        }
    }
    
    if (!flag) s2 = std::pair(x0, bmp_height - 1);
    flag = false;
    
    x0 = x0 + ceil(std::get<0>(s2) - x0) / 2 + 1;
    
    for (int y = y0; y < bmp_width; y++)
    {
        if ((y + 1) != bmp_height && image[y * bmp_width + x0] != image[(y + 1) * bmp_width + x0])
        {
            s3 = std::pair(x0, y);
            flag = true;
        }
    }
    
    if (!flag) s3 = std::pair(x0, bmp_height - 1);
    flag = false;
    
    std::cout << "S1: " << std::get<0>(s1) << " " << std::get<1>(s1) << std::endl;
    std::cout << "S2: " << std::get<0>(s2) << " " << std::get<1>(s2) << std::endl;
    std::cout << "S3: " << std::get<0>(s3) << " " << std::get<1>(s3) << std::endl;
    
    std::pair<int, int> M1, M2, M3;
    
    M1 = std::pair<int, int>(std::get<0>(s3), std::get<1>(s1));
    M2 = std::pair<int, int>((std::get<0>(s1) + std::get<0>(s3)) / 2, (std::get<1>(s1) + std::get<1>(s3)) / 2);
    M3 = std::pair<int, int>((std::get<0>(s2) + std::get<0>(s3)) / 2, (std::get<1>(s2) + std::get<1>(s3)) / 2);
    
    std::cout << "Median1: " << std::get<0>(M1) << " " << std::get<1>(M1) << std::endl;
    std::cout << "Median2: " << std::get<0>(M2) << " " << std::get<1>(M2) << std::endl;
    std::cout << "Median3: " << std::get<0>(M3) << " " << std::get<1>(M3) << std::endl;
    
    int lM1 = abs(std::get<1>(M1) - std::get<1>(s3)), lM2, lM3;
    std::cout << "lM1: " << lM1 << std::endl;
    
    std::pair<int, int> O = {std::get<0>(M1), std::get<1>(M1) + lM1 / 3};
    std::cout << "O: " << std::get<0>(O) << " " << std::get<1>(O) << std::endl;
    
    int ysm1 = 2 * std::get<1>(s1) - std::get<1>(O);
    
    if (ysm1 < 0) ysm1 = 0;
    else if (ysm1 >= bmp_height) ysm1 = bmp_height - 1;
    
    int xsm1 = 2 * std::get<0>(s1) - std::get<0>(O);
    
    if (xsm1 < 0) xsm1 = 0;
    else if (xsm1 >= bmp_width) xsm1 = bmp_width - 1;
    
    int ysm2 = 2 * std::get<1>(s2) - std::get<1>(O);
    
    if (ysm2 < 0) ysm2 = 0;
    else if (ysm2 >= bmp_height) ysm2 = bmp_height - 1;
    
    int xsm2 = 2 * std::get<0>(s2) - std::get<0>(O);
    
    if (xsm2 < 0) xsm2 = 0;
    else if (xsm2 >= bmp_width) xsm2 = bmp_width - 1;
    
    int ysm3 = 2 * std::get<1>(s3) - std::get<1>(O);
    
    if (ysm3 < 0) ysm3 = 0;
    else if (ysm3 >= bmp_height) ysm3 = bmp_height - 1;
    
    int xsm3 = 2 * std::get<0>(s3) - std::get<0>(O);
    
    if (xsm3 < 0) xsm3 = 0;
    else if (xsm3 >= bmp_width) xsm3 = bmp_width - 1;
    
    std::cout << "xsm1: " << xsm1 << " ysm1: " << ysm1 << std::endl;
    std::cout << "xsm2: " << xsm2 << " ysm2: " << ysm2 << std::endl;
    std::cout << "xsm3: " << xsm3 << " ysm3: " << ysm3 << std::endl;

    
    std::pair<int, int> smS1 = {xsm1, ysm1};
    std::pair<int, int> smS2 = {xsm2, ysm2};
    std::pair<int, int> smS3 = {xsm3, ysm3};
    
    std::vector<std::pair<int, int>> triangle1 = {smS1, O, smS2};
    std::vector<std::pair<int, int>> triangle2 = {smS2, O, smS3};
    std::vector<std::pair<int, int>> triangle3 = {smS3, O, smS1};
    
    triangleSmear(triangle1, 0., pixel(0, 255, 255), pixel(255, 255, 0));
    triangleSmear(triangle2, 0., pixel(0, 255, 255), pixel(255, 255, 0));
    triangleSmear(triangle3, 0., pixel(0, 255, 255), pixel(255, 255, 0));
    
    image[ysm1 * bmp_width + xsm1] = pixel(255, 0, 0);
    image[ysm2 * bmp_width + xsm2] = pixel(255, 0, 0);
    image[ysm3 * bmp_width + xsm3] = pixel(255, 0, 0);
    
}

void BMP::smearSquare()
{
    std::pair<int, int> s1, s2, s3, s4;
    bool flag = false;
    
    for (int y = 0; y < bmp_height; y++)
    {
        for (int x = 0; x < bmp_width; x++)
        {
            if ((y + 1) != bmp_height && (x + 1) != bmp_width && image[y * bmp_width + x] != image[y * bmp_width + (x + 1)])
            {
                s1 = std::pair<int, int>(x, y);
                flag = true;
                break;
            }
        }
        
        if (flag) break;
    }
    
    if (!flag) return;
    flag = false;
    
    int x0 = std::get<0>(s1);
    int y0 = std::get<1>(s1);
    
    for (int x = x0; x < bmp_width; x++)
    {
        if ((x + 1) != bmp_width && image[y0 * bmp_width + x] != image[y0 * bmp_width + (x + 1)])
        {
            s2 = std::pair(x, y0);
            flag = true;
        }
    }
    
    if (!flag) s2 = std::pair(y0, bmp_width - 1);
    flag = false;
    
    for (int y = y0; y < bmp_width; y++)
    {
        if ((y + 1) != bmp_height && image[y * bmp_width + x0] != image[(y + 1) * bmp_width + x0])
        {
            s4 = std::pair(x0, y);
            flag = true;
        }
    }
    
    if (!flag) s4 = std::pair(x0, bmp_height - 1);
    flag = false;
    
    int xSide = std::get<0>(s2) - x0;
    int ySide = std::get<1>(s4) - y0;
    
    s3 = std::pair(x0 + xSide, y0 + ySide);
    
    std::cout << "S1: " << std::get<0>(s1) << " " << std::get<1>(s1) << std::endl;
    std::cout << "S2: " << std::get<0>(s2) << " " << std::get<1>(s2) << std::endl;
    std::cout << "S3: " << std::get<0>(s3) << " " << std::get<1>(s3) << std::endl;
    std::cout << "S4: " << std::get<0>(s4) << " " << std::get<1>(s4) << std::endl;
    
    int l = std::get<0>(s2) - std::get<0>(s1);
    
    std::pair<int, int> O = {std::get<0>(s1) + l / 2, std::get<1>(s1) + l / 2};
    std::cout << "O: " << std::get<0>(O) << " " << std::get<1>(O) << std::endl;
    
    int ysm1 = 2 * std::get<1>(s1) - std::get<1>(O);
    
    if (ysm1 < 0) ysm1 = 0;
    else if (ysm1 >= bmp_height) ysm1 = bmp_height - 1;
    
    int xsm1 = 2 * std::get<0>(s1) - std::get<0>(O);
    
    if (xsm1 < 0) xsm1 = 0;
    else if (xsm1 >= bmp_width) xsm1 = bmp_width - 1;
    
    int ysm2 = 2 * std::get<1>(s2) - std::get<1>(O);
    
    if (ysm2 < 0) ysm2 = 0;
    else if (ysm2 >= bmp_height) ysm2 = bmp_height - 1;
    
    int xsm2 = 2 * std::get<0>(s2) - std::get<0>(O);
    
    if (xsm2 < 0) xsm2 = 0;
    else if (xsm2 >= bmp_width) xsm2 = bmp_width - 1;
    
    int ysm3 = 2 * std::get<1>(s3) - std::get<1>(O);
    
    if (ysm3 < 0) ysm3 = 0;
    else if (ysm3 >= bmp_height) ysm3 = bmp_height - 1;
    
    int xsm3 = 2 * std::get<0>(s3) - std::get<0>(O);
    
    if (xsm3 < 0) xsm3 = 0;
    else if (xsm3 >= bmp_width) xsm3 = bmp_width - 1;
    
    int ysm4 = 2 * std::get<1>(s4) - std::get<1>(O);
    
    if (ysm4 < 0) ysm4 = 0;
    else if (ysm4 >= bmp_height) ysm4 = bmp_height - 1;
    
    int xsm4 = 2 * std::get<0>(s4) - std::get<0>(O);
    
    if (xsm4 < 0) xsm4 = 0;
    else if (xsm4 >= bmp_width) xsm4 = bmp_width - 1;
    
    std::cout << "xsm1: " << xsm1 << " ysm1: " << ysm1 << std::endl;
    std::cout << "xsm2: " << xsm2 << " ysm2: " << ysm2 << std::endl;
    std::cout << "xsm3: " << xsm3 << " ysm3: " << ysm3 << std::endl;
    std::cout << "xsm4: " << xsm4 << " ysm4: " << ysm4 << std::endl;
    
    image[std::get<1>(O) * bmp_width + std::get<0>(O)] = pixel(255, 0, 0);
    image[ysm1 * bmp_width + xsm1] = pixel(255, 0, 0);
    image[ysm2 * bmp_width + xsm2] = pixel(255, 0, 0);
    image[ysm3 * bmp_width + xsm3] = pixel(255, 0, 0);
    //image[ysm4 * bmp_width + xsm4] = pixel(255, 0, 0);
    
    std::pair<int, int> smS1 = {xsm1, ysm1};
    std::pair<int, int> smS2 = {xsm2, ysm2};
    std::pair<int, int> smS3 = {xsm3, ysm3};
    std::pair<int, int> smS4 = {xsm4, ysm4};
    
    std::vector<std::pair<int, int>> triangle1 = {smS1, O, smS2};
    std::vector<std::pair<int, int>> triangle2 = {smS2, O, smS3};
    std::vector<std::pair<int, int>> triangle3 = {smS3, O, smS4};
    std::vector<std::pair<int, int>> triangle4 = {smS4, O, smS1};
    
    testTriangleSmear(triangle1, M_PI / 4., pixel(0, 255, 255), pixel(255, 255, 0));
    testTriangleSmear(triangle2, 3. * M_PI / 4., pixel(0, 255, 255), pixel(255, 255, 0));
    testTriangleSmear(triangle3, M_PI, pixel(0, 255, 255), pixel(255, 255, 0));
    testTriangleSmear(triangle4, 3. * M_PI / 2., pixel(0, 255, 255), pixel(255, 255, 0));
    
    /*triangleSmear(triangle1, 0, pixel(0, 255, 255), pixel(255, 255, 0));
    p2triangleSmear(triangle4, 0, pixel(0, 255, 255), pixel(255, 255, 0));
    _3p2triangleSmear(triangle3, 0, pixel(255, 255, 0), pixel(0, 255, 255));
    _2ptriangleSmear(triangle2, 0, pixel(255, 255, 0), pixel(0, 255, 255));
    
    double angle = 3.14 / 2.;
    
    double matrixRotation[2][2] = { { cos(angle), sin(angle) }, { -sin(angle), cos(angle) } };
    
    x0 = 200;
    y0 = 200;
    
    for (int x = x0, y = y0; y < 400; y++)
    {
        //int x1 = x * cos(angle);
        int x1 = x0 + (x - x0) * matrixRotation[0][0] + (y - y0) * matrixRotation[0][1];
        int y1 = y0 + (x - x0) * matrixRotation[1][0] + (y - y0) * matrixRotation[1][1];
        //int y1 = y * sin(angle);
        image[y1 * bmp_width + x1] = pixel(0, 0, 0);
    }*/
}
