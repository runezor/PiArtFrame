#include "mandelbrot.hpp"
#include "GUI_Paint.h"
#include <algorithm>
#include <cmath>
#include <vector>
#include <iostream>

using namespace std;
void MandelbrotSet::InitMandelbrotSet()
{
    w = 4;
    h = 2;
    x = -1;
    y = 0;
    rendered = NULL;
    renderedResX = 0;
    renderedResY = 0;
}

void MandelbrotSet::SetRender(UBYTE* image)
{
    rendered = image;
}

void MandelbrotSet::Render(UWORD xResolution, UWORD yResolution)
{
    // Approximation for number of iterations
    int iter = (50 + max(0.0, log10(w)) * 100 );
    vector<vector<bool>> columns;
    vector<bool> rows;

    for(int i = yResolution-1; i>=0; --i)
    {
        for(int j = 0; j < xResolution; ++j)
        {
            double p_x = this->x - this->w / 2.0 + j / (double)xResolution * this->w;
            double p_y = this->y - this->h / 2.0 + i / (double)yResolution * this->h;
            rows.emplace_back(IsMandelPoint(p_x, p_y, iter));
        }
        columns.emplace_back(rows);
        rows.clear();
    }

    renderedResX = xResolution;
    renderedResY = yResolution;

    // Update rendered image
    for(unsigned int y = 0; y < columns.size(); ++y)
    {
        auto row = columns[y];
        for(unsigned int x = 0; x < row.size(); ++x)
        {
            auto bitSet = row[x];
            if(bitSet)
            {
                Paint_SetPixel(x, y, BLACK);
            }
            else
            {
                Paint_SetPixel(x, y, WHITE);
            }
        }
    }

}

bool MandelbrotSet::IsMandelPoint(double x, double y, int iterations)
{
    double z_x = x;
    double z_y = y;
    for(int i = 0; i < iterations; ++i)
    {
        int z_x_old = z_x;
        z_x = z_x * z_x - z_y * z_y + x;
        z_y = 2 * z_x_old * z_y + y;
        if ((pow(z_x, 2) + pow(z_y, 2)) > 4)
        {
            return true;
        }
    }
    return false;
}

int MandelbrotSet::GetUniformnessOfArea(double fW, double fH, int xOffset, int yOffset, int wDiv, int hDiv)
{
    int uniformness = 0;
    for(int wStart = 0; wStart < wDiv; ++wStart)
    {
        for(int hStart = 0; hStart < hDiv; ++hStart)
        {
            if(IsAreaUniform(xOffset, yOffset, fW, fH, wDiv, hDiv, wStart, hStart))
            {
                ++uniformness;
            }
        }
    }

    return uniformness;
}

bool MandelbrotSet::IsAreaUniform(int xOffset, int yOffset, double fW, double fH,  int wDiv, int hDiv, double wStart, double hStart)
{
    int yInit = yOffset + static_cast<int>(fH / hDiv) * hStart;
    int xInit = xOffset + static_cast<int>(fW / wDiv) * wStart;
    auto firstPoint = Paint_GetPixel(xInit , yInit);

    for(unsigned int i = 0; i < static_cast<unsigned int>(fW / wDiv); ++i )
    {
        for(unsigned int j = 0; j < static_cast<unsigned int>(fH / hDiv); ++j )
        {
            int yTest = yOffset + static_cast<int>(fH / hDiv) * hStart + j;
            int xTest = xOffset + static_cast<int>(fW / wDiv) * wStart;
            auto testPoint = Paint_GetPixel(xTest , yTest);
            if(testPoint != firstPoint)
                return false;
        }        
    }

    return true;
}