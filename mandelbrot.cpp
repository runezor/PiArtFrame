#include "mandelbrot.hpp"
#include "GUI_Paint.h"
#include <algorithm>
#include <cmath>
#include <vector>

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
    int iter = (50 + max(0.0, -log10(w)) * 100 );
    vector<vector<bool>> columns;
    vector<bool> rows;

    for(int i = yResolution-1; i>=0; --i)
    {
        for(int j = 0; j < xResolution; ++j)
        {
            double p_x = this->x - this->w / 2.0 + j / xResolution * this->w;
            double p_y = this->y - this->h / 2.0 + j / yResolution * this->h;
            rows.emplace_back(IsMandelPoint(p_x, p_y, iter));
        }
        columns.emplace_back(rows);
        rows.clear();
    }

    renderedResX = xResolution;
    renderedResY = yResolution;

    // Update rendered image
    for(unsigned int y = columns.size() - 1; y >=0; --y)
    {
        auto row = columns[y];
        for(unsigned int x = 0; x < row.size(); ++x)
        {
            auto bitSet = row[x];
            if(bitSet)
                Paint_SetPixel(x, y, BLACK);
            else
                Paint_SetPixel(x, y, WHITE);
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
        if ((z_x * z_x + z_y * z_y ) > 4)
            return true;
    }
    return false;
}