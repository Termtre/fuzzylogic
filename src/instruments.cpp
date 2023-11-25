//
//  instruments.cpp
//  fuzzylogic
//
//  Created by Дмитрий  on 20.11.2023.
//

#include "instruments.h"
# define M_PI           3.14159265358979323846

Instruments::Instruments(const BMP& bmpImage)
{
    this->width = bmpImage.bmp_width;
    this->height = bmpImage.bmp_height;
    
    for (auto it = bmpImage.image.begin(); it != bmpImage.image.end(); ++it)
        this->image.push_back(*it);
}

void Instruments::exportImage(BMP& bmpImage)
{
    bmpImage.image.clear();

    for (auto it = this->image.begin(); it != this->image.end(); ++it)
        bmpImage.image.push_back(*it);
}

void Instruments::testSmearSquare(double koef)
{
    if (koef < 0) throw "Wrong smear koef";

    dot s1, s2, s3, s4;
    bool flag = false;
    pixel out, in;

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            if ((x + 1) != width && image[y * width + x] != image[y * width + (x + 1)])
            {
                out = image[y * width + x];
                in = image[y * width + (x + 1)];
                s1 = std::move(dot(x + 1, y));
                flag = true;
                break;
            }
        }

        if (flag) break;
    }

    if (!flag) return;
    flag = false;

    for (int x = s1.x; x < width; x++)
    {
        if ((x + 1) != width && image[s1.y * width + x] != image[s1.y * width + (x + 1)])
        {
            s2 = std::move(dot(x, s1.y));
            flag = true;
        }
    }

    if (!flag) s2 = std::move(dot(s1.y, width - 1));
    flag = false;

    for (int y = s1.y; y < height; y++)
    {
        if ((y + 1) != height && image[y * width + s1.x] != image[(y + 1) * width + s1.x])
        {
            s4 = std::move(dot(s1.x, y));
            flag = true;
        }
    }

    if (!flag) s4 = std::move(dot(s1.x, height - 1));
    flag = false;

    s3 = std::move(dot(s2.x, s4.y));

    std::cout << "S1: " << s1.x << " " << s1.y << std::endl;
    std::cout << "S2: " << s2.x << " " << s2.y << std::endl;
    std::cout << "S3: " << s3.x << " " << s3.y << std::endl;
    std::cout << "S4: " << s4.x << " " << s4.y << std::endl;

    image[s3.y * width + s3.x] = pixel(0, 0, 0);
    image[s4.y * width + s4.x] = pixel(0, 0, 0);

    int lx = abs(s2.x - s1.x);
    int ly = abs(s3.y - s1.y);

    dot O(s1.x + lx / 2, s1.y + ly / 2);
    std::cout << "O: " << O.x << " " << O.y << std::endl;

    int lenghtSmearX = lx / 2 * koef;
    if (lenghtSmearX > lx / 2) lenghtSmearX = lx / 2;
    dot borderRightX(s2.x + lenghtSmearX, O.y);
    dot borderLeftX(s2.x - lenghtSmearX, O.y);

    std::cout << "BorderRight: " << borderRightX.x << " " << borderRightX.y << std::endl;
    std::cout << "BorderLeft: " << borderLeftX.x << " " << borderLeftX.y << std::endl;

    int rr = abs(out.r - in.r);
    int gr = abs(out.g - in.g);
    int br = abs(out.b - in.b);
    int r = 0, g = 0, b = 0;

    if (rr == 0) r = in.r;
    if (gr == 0) g = in.g;
    if (br == 0) b = in.b;

    for (int x = borderLeftX.x + 1; x <= borderRightX.x && x < width; x++)
    { 
        int lenghtSide = x - O.x;
        double f1 = straight_memFunction(x, borderLeftX.x - 1, borderLeftX.x, borderRightX.x); // Левый цвет
        double f2 = straight_memFunction(x, borderLeftX.x, borderRightX.x, borderRightX.x + 1); // Правый цвет

        if (rr != 0) r = in.r != 0 ? f1 * in.r : f2 * out.r;
        if (gr != 0) g = in.g != 0 ? f1 * in.g : f2 * out.g;
        if (br != 0) b = in.b != 0 ? f1 * in.b : f2 * out.b;

        dot left1(O.x - lenghtSide, O.y - lenghtSide);
        dot right1(x, left1.y);
        dot left2(O.x - lenghtSide, O.y + lenghtSide);
        dot right2(x, left2.y);
        dot down1 = left1;
        dot up1 = left2;
        dot down2 = right1;
        dot up2 = right2;

        Line l1(left1, right1), l2(down1, up1), l3(left2, right2), l4(down2, up2);
        l1.calcH(left1, right1);
        l2.calcH(down1, up1);
        l3.calcH(left2, right2);
        l4.calcH(down2, up2);
        
        for (dot cur1 = left1, cur2 = left2;
            cur1.x <= right1.x;
            cur1 = std::move(l1.nextDot(cur1)), cur2 = std::move(l3.nextDot(cur2)))
        {
            if (cur1.x >= 0)
            {
                if (cur1.y >= 0 && cur1.y < height) image[cur1.y * width + cur1.x] = pixel(r, g, b);
                if (cur2.y >= 0 && cur2.y < height) image[cur2.y * width + cur2.x] = pixel(r, g, b);
            }
        }

        for (dot cur1 = down1, cur2 = down2;
            cur1.y <= up1.y;
            cur1 = std::move(l2.nextDot(cur1)), cur2 = std::move(l4.nextDot(cur2)))
        {
            if (cur1.y >= 0 && cur1.y < height)
            {
                if (cur1.x >= 0 && cur1.x < width) image[cur1.y * width + cur1.x] = pixel(r, g, b);
                if (cur2.x >= 0 && cur2.x < width) image[cur2.y * width + cur2.x] = pixel(r, g, b);
            }
        }
    }
}

void Instruments::smearSquare(double koef)
{
    dot s1, s2, s3, s4;
    bool flag = false;
    pixel out, in;

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            if ((x + 1) != width && image[y * width + x] != image[y * width + (x + 1)])
            {
                out = image[y * width + x];
                in = image[y * width + (x + 1)];
                s1 = std::move(dot(x + 1, y));
                flag = true;
                break;
            }
        }

        if (flag) break;
    }

    if (!flag) return;
    flag = false;

    for (int x = s1.x; x < width; x++)
    {
        if ((x + 1) != width && image[s1.y * width + x] != image[s1.y * width + (x + 1)])
        {
            s2 = std::move(dot(x, s1.y));
            flag = true;
        }
    }

    if (!flag) s2 = std::move(dot(s1.y, width - 1));
    flag = false;

    for (int y = s1.y; y < height; y++)
    {
        if ((y + 1) != height && image[y * width + s1.x] != image[(y + 1) * width + s1.x])
        {
            s4 = std::move(dot(s1.x, y));
            flag = true;
        }
    }

    if (!flag) s4 = std::move(dot(s1.x, height - 1));
    flag = false;

    //int xSide = s2.x - s1.x;
    //int ySide = s4.y - s1.y;

    s3 = std::move(dot(s2.x, s4.y));

    std::cout << "S1: " << s1.x << " " << s1.y << std::endl;
    std::cout << "S2: " << s2.x << " " << s2.y << std::endl;
    std::cout << "S3: " << s3.x << " " << s3.y << std::endl;
    std::cout << "S4: " << s4.x << " " << s4.y << std::endl;

    image[s3.y * width + s3.x] = pixel(0, 0, 0);
    image[s4.y * width + s4.x] = pixel(0, 0, 0);

    int lx = s2.x - s1.x;
    int ly = s3.y - s1.y;

    dot O(s1.x + lx / 2, s1.y + ly / 2);
    std::cout << "O: " << O.x << " " << O.y << std::endl;

    dot smS1(koef * (2 * s1.x - O.x), koef * (2 * s1.y - O.y));
    dot smS2(koef * (2 * s2.x - O.x), koef * (2 * s2.y - O.y));
    dot smS3(koef * (2 * s3.x - O.x), koef * (2 * s3.y - O.y));
    dot smS4(koef * (2 * s4.x - O.x), koef * (2 * s4.y - O.y));

    std::cout << "xsm1: " << smS1.x << " ysm1: " << smS1.y << std::endl;
    std::cout << "xsm2: " << smS2.x << " ysm2: " << smS2.y << std::endl;
    std::cout << "xsm3: " << smS3.x << " ysm3: " << smS3.y << std::endl;
    std::cout << "xsm4: " << smS4.x << " ysm4: " << smS4.y << std::endl;

    image[O.y * width + O.x] = pixel(255, 255, 255);

    std::vector<dot> triangle1 = { smS1, O, smS2 };
    std::vector<dot> triangle2 = { smS2, O, smS3 };
    std::vector<dot> triangle3 = { smS3, O, smS4 };
    std::vector<dot> triangle4 = { smS4, O, smS1 };

    std::cout << "                       triangle1" << std::endl;
    triangleSmear(triangle1, in, out);
    std::cout << "                          triangle2" << std::endl;
    triangleSmear(triangle2, in, out);
    std::cout << "                             triangle3" << std::endl;
    triangleSmear(triangle3, in, out);
    std::cout << "                                triangle4" << std::endl;
    triangleSmear(triangle4, in, out);
}

void Instruments::triangleSmear(const std::vector<dot>& sides, const pixel& in, const pixel& out)
{
    dot dotMedian((sides[0].x + sides[2].x) / 2 + 1, (sides[0].y + sides[2].y) / 2);
    if (abs(dotMedian.x - sides[1].x) <= 2) dotMedian.x = sides[1].x;
    if (abs(dotMedian.y - sides[1].y) <= 2) dotMedian.y = sides[1].y;
    Line median(sides[1], dotMedian);
    median.calcH(sides[1], dotMedian);
    Line l1(sides[1], sides[0]);
    l1.calcH(sides[1], sides[0]);
    std::cout << "l1: " << l1.line_type << " " << l1.line_k << " " << l1.line_sdv << " " << l1.line_h << std::endl;
    Line l2(sides[1], sides[2]);
    l2.calcH(sides[1], sides[2]);
    std::cout << "l2: " << l2.line_type << " " << l2.line_k << " " << l2.line_sdv << " " << l2.line_h << std::endl;
    std::cout << "Median: " << dotMedian.x << " " << dotMedian.y << std::endl;
    std::cout << "O: " << sides[1].x << " " << sides[1].y << std::endl;
    std::cout << "Median: " << median.line_type << " " << median.line_k << " " << median.line_sdv << " " << median.line_h << std::endl;
    std::cout << sides[1].x << " " << sides[1].y << std::endl;

    pixel lessPixel = out, morePixel = in;

    if (dotMedian.x < sides[1].x || dotMedian.x == sides[1].x && dotMedian.y <= sides[1].y)
    {
        lessPixel = out;
        morePixel = in;
    }

    else
    {
        lessPixel = in;
        morePixel = out;
    }

    int rr = abs(lessPixel.r - morePixel.r);
    int gr = abs(lessPixel.g - morePixel.g);
    int br = abs(lessPixel.b - morePixel.b);
    int r = 0, g = 0, b = 0;

    if (rr == 0) r = out.r;
    if (gr == 0) g = out.g;
    if (br == 0) b = out.b;

    int lessX, lessY;
    int moreX, moreY;

    if (sides[1].x >= dotMedian.x)
    {
        lessX = dotMedian.x;
        moreX = sides[1].x;
    }

    else
    {
        moreX = dotMedian.x;
        lessX = sides[1].x;
    }

    if (sides[1].y >= dotMedian.y)
    {
        lessY = dotMedian.y;
        moreY = sides[1].y;
    }

    else
    {
        moreY = dotMedian.y;
        lessY = sides[1].y;
    }

    for (dot prev(sides[1].x, sides[1].y), cur1 = l1.nextDot(prev),
        cur2 = l2.nextDot(prev), cur = prev;//cur = std::move(median.nextDot(prev));
        (abs(cur.x - dotMedian.x) > 1 || abs(cur.y - dotMedian.y) > 1) &&
        cur.x < width && cur.y < height && cur.x >= 0 && cur.y >= 0;
        cur1 = l1.nextDot(cur1), cur2 = l2.nextDot(cur2), cur = std::move(median.nextDot(cur)))
    {
        //std::cout << cur.x << " " << cur.y << std::endl;
        double f1, f2;

        if (abs(median.line_k) == 0)
        {
            f1 = straight_memFunction(cur.x, lessX - 1, lessX, moreX); // Левый цвет
            f2 = straight_memFunction(cur.x, lessX, moreX, moreX + 1); // Правый цвет
        }

        else
        {
            f1 = straight_memFunction(cur.y, lessY - 1, lessY, moreY); // Верхний цвет на картинке (нижний в массиве)
            f2 = straight_memFunction(cur.y, lessY, moreY, moreY + 1); // Нижний цвет на картинке (верхний в массиве)
        }

        if (rr != 0) r = lessPixel.r != 0 ? f1 * lessPixel.r : f2 * morePixel.r;
        if (gr != 0) g = lessPixel.g != 0 ? f1 * lessPixel.g : f2 * morePixel.g;
        if (br != 0) b = lessPixel.b != 0 ? f1 * lessPixel.b : f2 * morePixel.b;



        //std::cout << "prev: " << prev.x << " " << prev.y << std::endl;
        std::cout << "cur1: " << cur1.x << " " << cur1.y << std::endl;
        std::cout << "cur2: " << cur2.x << " " << cur2.y << std::endl;
        Line l3(cur1, cur2);
        l3.calcH(cur1, cur2);
        std::cout << "l3: " << l3.line_type << " " << l3.line_k << " " << l3.line_sdv << " " << l3.line_h << std::endl;
        image[cur.y * width + cur.x] = pixel(0, 0, 0);
        if (cur1.y < height && cur1.x < width && cur1.y >= 0 && cur1.x >= 0)
            image[cur1.y * width + cur1.x] = pixel(0, 0, 0);
        if (cur2.y < height && cur2.x < width && cur2.y >= 0 && cur2.x >= 0)
            image[cur2.y * width + cur2.x] = pixel(0, 0, 0);

        if (cur1.x < 0) cur1.x = 0;
        if (cur1.y < 0) cur1.y = 0;
        if (cur2.x < 0) cur2.x = 0;
        if (cur2.y < 0) cur2.y = 0;
        if (cur1.x >= width) cur1.x = width - 1;
        if (cur1.y >= height) cur1.y = height - 1;
        if (cur2.x >= width) cur2.x = width - 1;
        if (cur2.y >=  height) cur2.y = height - 1;

        for (dot cur3(cur1);
            (abs(cur3.x - l2.nextDot(cur2).x) > 1 || abs(cur3.y - l2.nextDot(cur2).y) > 1) &&
            cur3.x >= 0 && cur3.y >= 0 && cur3.x < width && cur3.y < height;
            cur3 = std::move(l3.nextDot(cur3)))
        {     
            //image[cur3.y * width + cur3.x] = pixel(r, g, b);       
        }
    }
}

void Instruments::smearTriangle(double koef)
{
    dot s1, s2, s3;
    bool flag = false;
    pixel out, in;

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            if ((y + 1) != height && (x + 1) != width && image[y * width + x] != image[y * width + (x + 1)])
            {
                out = image[y * width + x];
                in = image[y * width + (x + 1)];
                s1 = std::move(dot(x, y));
                flag = true;
                break;
            }
        }

        if (flag) break;
    }

    if (!flag) return;
    flag = false;

    for (int x = s1.x; x < width; x++)
    {
        if ((x + 1) != width && image[s1.y * width + x] != image[s1.y * width + (x + 1)])
        {
            s2 = std::move(dot(x, s1.y));
            flag = true;
        }
    }

    if (!flag) s2 = std::move(dot(s1.x, height - 1));
    flag = false;

    s1.x = s1.x + ceil(s2.x - s1.x) / 2 + 1;

    for (int y = s1.y; y < height; y++)
    {
        if ((y + 1) != height && image[y * width + s1.x] != image[(y + 1) * width + s1.x])
        {
            s3 = std::move(dot(s1.x, y));
            flag = true;
        }
    }

    if (!flag) s3 = std::move(dot(s1.x, height - 1));
    flag = false;

    std::cout << "S1: " << s1.x << " " << s1.y << std::endl;
    std::cout << "S2: " << s2.x << " " << s2.y << std::endl;
    std::cout << "S3: " << s3.x << " " << s3.y << std::endl;

    dot M1, M2, M3;

    M1 = std::move(dot(s3.x, s1.y));
    M2 = std::move(dot((s1.x + s3.x) / 2, (s1.y + s3.y) / 2));
    M3 = std::move(dot((s2.x + s3.x) / 2, (s2.y + s3.y) / 2));

    std::cout << "Median1: " << M1.x << " " << M1.y << std::endl;
    std::cout << "Median2: " << M2.x << " " << M2.y << std::endl;
    std::cout << "Median3: " << M3.x << " " << M3.y << std::endl;

    int lM1 = abs(M1.y - s3.y), lM2, lM3;
    std::cout << "lM1: " << lM1 << std::endl;

    dot O = { M1.x, M1.y + lM1 / 3 };
    std::cout << "O: " << O.x << " " << O.y << std::endl;

    dot smS1(koef * (2 * s1.x - O.x), koef * (2 * s1.y - O.y));
    dot smS2(koef * (2 * s2.x - O.x), koef * (2 * s2.y - O.y));
    dot smS3(koef * (2 * s3.x - O.x), koef * (2 * s3.y - O.y));

    std::cout << "xsm1: " << smS1.x << " ysm1: " << smS1.y << std::endl;
    std::cout << "xsm2: " << smS2.x << " ysm2: " << smS2.y << std::endl;
    std::cout << "xsm3: " << smS3.x << " ysm3: " << smS3.y << std::endl;

    std::vector<dot> triangle1 = { smS1, O, smS2 };
    std::vector<dot> triangle2 = { smS2, O, smS3 };
    std::vector<dot> triangle3 = { smS3, O, smS1 };

    triangleSmear(triangle1, pixel(0, 255, 255), pixel(255, 255, 0));
    triangleSmear(triangle2, pixel(0, 255, 255), pixel(255, 255, 0));
    triangleSmear(triangle3, pixel(0, 255, 255), pixel(255, 255, 0));
}