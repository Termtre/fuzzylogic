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
    int lenghtSmearY = ly / 2 * koef;
    if (lenghtSmearY > ly / 2) lenghtSmearY = ly / 2;

    dot borderLess(s2.x - lenghtSmearX, s3.y - lenghtSmearY);
    dot borderMore(s2.x + lenghtSmearX, s3.y + lenghtSmearY);

    std::cout << "BorderLess: " << borderLess.x << " " << borderLess.y << " " << borderLess.srQ() << std::endl;
    std::cout << "BorderMore: " << borderMore.x << " " << borderMore.y << " " << borderMore.srQ() << std::endl;

    int rr = abs(out.r - in.r);
    int gr = abs(out.g - in.g);
    int br = abs(out.b - in.b);
    int r = 0, g = 0, b = 0;

    if (rr == 0) r = in.r;
    if (gr == 0) g = in.g;
    if (br == 0) b = in.b;

    for (dot w = dot(borderLess.x + 1, borderLess.y + 1);
        w.srQ() <= borderMore.srQ() && w.srQ() < dot(width, height).srQ();
        w.x++, w.y++)
    {
        int lenghtSideY = w.y - O.y;
        int lenghtSideX = w.x - O.x;

        double f1 = straight_memFunction(w.srQ(), borderLess.srQ() - 1, borderLess.srQ(), borderMore.srQ());
        double f2 = straight_memFunction(w.srQ(), borderLess.srQ(), borderMore.srQ(), borderMore.srQ() + 1);

        if (rr != 0) r = in.r != 0 ? f1 * in.r : f2 * out.r;
        if (gr != 0) g = in.g != 0 ? f1 * in.g : f2 * out.g;
        if (br != 0) b = in.b != 0 ? f1 * in.b : f2 * out.b;

        dot left1(O.x - lenghtSideX, O.y - lenghtSideY);
        dot right1(w.x, left1.y);
        dot left2(O.x - lenghtSideX, O.y + lenghtSideY);
        dot right2(w.x, left2.y);
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

void Instruments::smearCircle(double koef)
{
    dot s1, s2, s3;
    bool flag = false;
    pixel out, in;

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            if ((x + 1) < width && image[y * width + x] != image[y * width + (x + 1)])
            {
                out = image[y * width + x];
                in = image[y * width + (x + 1)];
                s1 = std::move(dot(x + 1, y));
                flag = true;
                y = height;
                x = width;
                break;
            }
        }
    }

    if (!flag) return;
    flag = false;

    for (int y = s1.y; y < height; y++)
    {
        if ((y + 1) < height && image[y * width + s1.x] != image[(y + 1) * width + s1.x])
        {
            s2 = std::move(dot(s1.x, y));
            flag = true;
            break;
        }
    }

    if (!flag) return;
    flag = false;

    for (int x = s1.x; x < width; x++)
    {
        if ((x + 1) < width && image[s2.y * width + x] != image[s2.y *  width + x + 1])
        {
            s3 = std::move(dot(x, s2.y));
            flag = true;
            break;
        }
    }

    if (!flag) return;
    flag = false;

    std::cout << "s1: " << s1.x << " " << s1.y << std::endl;
    std::cout << "s2: " << s2.x << " " << s2.y << std::endl;
    std::cout << "s3: " << s3.x << " " << s3.y << std::endl;

    dot O((s1.x + s3.x) / 2, (s1.y + s3.y) / 2);
    int radius = hypot(O.x - s1.x, O.y - s1.y);
    std::cout << "O: " << O.x << " " << O.y << " radius: " << radius << std::endl;
    Line l1(s1, O);
    l1.calcH(dot(O.x, s1.y), O);
    std::cout << "l1: " << l1.line_type << " " << l1.line_k << " " << l1.line_sdv << " " << l1.line_h << std::endl;
    int lenghtSmear = radius * koef;
    lenghtSmear = lenghtSmear > radius ? radius : lenghtSmear;

    int rr = abs(out.r - in.r);
    int gr = abs(out.g - in.g);
    int br = abs(out.b - in.b);
    int r = 0, g = 0, b = 0;

    if (rr == 0) r = in.r;
    if (gr == 0) g = in.g;
    if (br == 0) b = in.b;

    int left = O.x + radius - lenghtSmear;
    int right = O.x + radius + lenghtSmear;

    for (int x = left; x < right; x++)
    {
        double f1 = straight_memFunction(x, left - 1, left, right);
        double f2 = straight_memFunction(x, left, right, right + 1);

        if (rr != 0) r = in.r != 0 ? f1 * in.r : f2 * out.r;
        if (gr != 0) g = in.g != 0 ? f1 * in.g : f2 * out.g;
        if (br != 0) b = in.b != 0 ? f1 * in.b : f2 * out.b;

        int newRadius = x - O.x;
        double anglef = M_PI / newRadius / 24.;
        for (double f = 0.; f < 2. * M_PI; f += anglef)
        {
            int x1 = newRadius * cos(f) + O.x;
            int y1 = newRadius * sin(f) + O.y;
            if (y1 < height && x1 < width && y1 >= 0 && x1 >= 0 && image[y1 * width + x1] != pixel(r, g, b))
                image[y1 * width + x1] = pixel(r, g, b);
        }
    }
}

void Instruments::testSmearTriangle(double koef)
{
    dot s1, s2, s3;
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

    if (!flag) s2 = std::move(dot(s1.x, height - 1));
    flag = false;

    //s1.x = s1.x + ceil(s2.x - s1.x) / 2 + 1;

    int middle = (s1.x + s2.x) / 2;

    for (int y = s1.y; y < height; y++)
    {
        if ((y + 1) != height && image[y * width + middle] != image[(y + 1) * width + middle])
        {
            s3 = std::move(dot(middle, y));
            flag = true;
        }
    }

    if (!flag) s3 = std::move(dot(s1.x, height - 1));
    flag = false;

    std::cout << "S1: " << s1.x << " " << s1.y << std::endl;
    std::cout << "S2: " << s2.x << " " << s2.y << std::endl;
    std::cout << "S3: " << s3.x << " " << s3.y << std::endl;

    image[s1.y * width + s1.x] = pixel(255, 0, 0);
    image[s2.y * width + s2.x] = pixel(255, 0, 0);
    image[s3.y * width + s3.x] = pixel(255, 0, 0);

    dot M1((s2.x + s3.x) / 2, (s2.y + s3.y) / 2);
    dot M2((s1.x + s3.x) / 2, (s1.y + s3.y) / 2);
    dot M3((s1.x + s2.x) / 2, (s1.y + s2.y) / 2);

    std::cout << "Median1: " << M1.x << " " << M1.y << std::endl;
    std::cout << "Median2: " << M2.x << " " << M2.y << std::endl;
    std::cout << "Median3: " << M3.x << " " << M3.y << std::endl;

    int lM1 = hypot(M1.x - s1.x, M1.y - s1.y) / 3;
    int lM2 = hypot(M2.x - s2.x, M2.y - s2.y) / 3;
    int lM3 = hypot(M3.x - s3.x, M3.y - s3.y) / 3;

    std::cout << "lM1: " << lM1 << std::endl;
    std::cout << "lM2: " << lM2 << std::endl;
    std::cout << "lM3: " << lM3 << std::endl;

    image[M1.y * width + M1.x] = pixel(255, 0, 0);
    image[M2.y * width + M2.x] = pixel(255, 0, 0);
    image[M3.y * width + M3.x] = pixel(255, 0, 0);

    int a = 2 * (M2.x - M1.x);
    int t = 2 * (M2.y - M1.y);
    int c = 2 * (M3.x - M1.x);
    int d = 2 * (M3.y - M1.y);
    int m = lM1 * lM1 - lM2 * lM2 + M2.x * M2.x + M2.y * M2.y - (M1.x * M1.x + M1.y * M1.y);
    int n = lM1 * lM1 - lM3 * lM3 + M3.x * M3.x + M3.y * M3.y - (M1.x * M1.x + M1.y * M1.y);

    dot O = { (m * d - t * n) / (a * d - t * c) + 1., (n * a - m * c) / (a * d - t * c) + 1. };
    std::cout << "O: " << O.x << " " << O.y << std::endl;
    image[O.y * width + abs(O.x)] = pixel(255, 0, 0);

    /*Line l1(s2, s3);
    l1.calcH(s2, s3);
    Line l2(s1, s3);
    l2.calcH(s1, s3);
    Line l3(s1, s2);
    l3.calcH(s1, s2);
    Line lOM1(s1, M1);
    lOM1.calcH(s1, M1);
    Line lOM2(s2, M2);
    lOM2.calcH(s2, M2);
    Line lOM3(s3, M3);
    lOM3.calcH(s3, M3);*/

    Line median1(s1, M1);
    median1.calcH(s1, M1);
    Line median2(s2, M2);
    median2.calcH(s2, M2);
    Line median3(s3, M3);
    median3.calcH(s3, M3);

    //std::cout << "lOM3: " << lOM3.line_type << " " << lOM3.line_k << " " << lOM3.line_sdv << " " << lOM3.line_h << std::endl;

    int rr = abs(out.r - in.r);
    int gr = abs(out.g - in.g);
    int br = abs(out.b - in.b);
    int r = 0, g = 0, b = 0;

    if (rr == 0) r = in.r;
    if (gr == 0) g = in.g;
    if (br == 0) b = in.b;

    for (dot cur(s1); cur != M1; cur = std::move(median1.nextDot(cur)))
        image[cur.y * width + cur.x] = pixel(255, 50, 0);

    for (dot cur(s2); cur != M2; cur = std::move(median2.nextDot(cur)))
        image[cur.y * width + cur.x] = pixel(255, 50, 0);

    for (dot cur(s3); cur != M3; cur = std::move(median3.nextDot(cur)))
        image[cur.y * width + cur.x] = pixel(255, 50, 0);

    Line LOM1(O, s1);
    Line LOM2(O, s2);
    Line LOM3(O, s3);
    LOM1.calcH(O, s1);
    LOM2.calcH(O, s2);
    LOM3.calcH(O, s3);

    std::cout << "lOM3: " << LOM3.line_type << " " << LOM3.line_k << " " << LOM3.line_sdv << " " << LOM3.line_h << std::endl;

    for (dot cur1 = std::move(LOM1.nextDot(O)), cur2 = std::move(LOM2.nextDot(O));
        cur1 != s1;
        cur1 = std::move(LOM1.nextDot(cur1)), cur2 = std::move(LOM2.nextDot(cur2)))
    {
        Line l1(cur1, cur2);
        l1.calcH(cur1, cur2);
        for (dot dot(cur1); dot != cur2; dot = std::move(l1.nextDot(dot)))
        {
            image[dot.y * width + dot.x] = pixel(125, 0, 38);
        }
    }

    for (dot cur1 = std::move(LOM2.nextDot(O)), cur2 = std::move(LOM3.nextDot(O));
        cur1 != s2;)
    {
        Line l1(cur1, cur2);
        l1.calcH(cur1, cur2);
        std::cout << "lOM3: " << l1.line_type << " " << l1.line_k << " " << l1.line_sdv << " " << l1.line_h << std::endl;
        std::cout << "[" << cur2.x << ", " << cur2.y << "]" << std::endl;
    
        image[cur1.y * width + cur1.x] = pixel(125, 255, 38);
        image[cur2.y * width + cur2.x] = pixel(125, 255, 38);
        for (dot dot(cur1); dot != cur2; dot = std::move(l1.nextDot(dot)))
        {
            std::cout << "[" << dot.x << ", " << dot.y << "]" << std::endl;
            image[dot.y * width + dot.x] = pixel(125, 0, 38);
        }

        if (cur1 != s2) cur1 = std::move(LOM2.nextDot(cur1));
        if (cur2 != s3) cur2 = std::move(LOM3.nextDot(cur2));
    }

    /*for (dot cur1(s1), cur2(s2), cur3(s3);
        cur1 != O && cur2 != O && cur3 != O;
        cur1 = std::move(lOM1.nextDot(cur1)), cur2 = std::move(lOM2.nextDot(cur2)), cur3 = std::move(lOM3.nextDot(cur3)))
    {
        double f1 = straight_memFunction(cur1.srQ(), O.srQ() - 1, O.srQ(), s1.srQ());
        double f2 = straight_memFunction(cur1.srQ(), O.srQ(), s1.srQ(), s1.srQ() + 1);

        if (rr != 0) r = in.r != 0 ? f1 * in.r : f2 * out.r;
        if (gr != 0) g = in.g != 0 ? f1 * in.g : f2 * out.g;
        if (br != 0) b = in.b != 0 ? f1 * in.b : f2 * out.b;

        image[cur1.y * width + cur1.x] = pixel(255, 0, 255);
        image[cur2.y * width + cur2.x] = pixel(255, 0, 255);
        image[cur3.y * width + cur3.x] = pixel(255, 0, 255);

        Line cL(cur1, cur3);
        Line cL1(cur2, cur3);
        cL.calcH(cur1, cur3);
        cL1.calcH(cur2, cur3);
        std::cout << "cL: " << cL.line_type << " " << cL.line_k << " " << cL.line_sdv << " " << cL.line_h << std::endl;
        for (dot d1(cur1); d1 != cur3; d1 = std::move(cL.nextDot(d1)))
        {
            image[d1.y * width + d1.x] = pixel(r, g, b);
        }
    }

    for (dot cur1(s2), cur2(s1), cur3(s1);
        cur1 != s3 && cur2 != s3 && cur3 != s2;
        cur1 = std::move(l1.nextDot(cur1)), cur2 = std::move(l2.nextDot(cur2)), cur3 = std::move(l3.nextDot(cur3)))
    {
        image[cur1.y * width + cur1.x] = pixel(255, 0, 255);
        image[cur2.y * width + cur2.x] = pixel(255, 0, 255);
        image[cur3.y * width + cur3.x] = pixel(255, 0, 255);
    }*/
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