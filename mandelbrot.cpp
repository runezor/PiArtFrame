#include "mandelbrot.hpp"
#include "GUI_Paint.h"
#include <algorithm>
#include <cmath>
#include <vector>
#include <tuple>
#include <iostream>
#include <fstream>
#include <random>

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

    for(int i = yResolution-1; i>=0; --i)
    {
        vector<bool> rows;
        for(int j = 0; j < xResolution; ++j)
        {
            double p_x = this->x - this->w / 2.0 + (double)j / (double)xResolution * this->w;
            double p_y = this->y - this->h / 2.0 + (double)(i+1) / (double)yResolution * this->h;
            rows.emplace_back(IsMandelPoint(p_x, p_y, iter));
        }
        columns.emplace_back(rows);
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
                Paint_SetPixel(x, y, WHITE);
            }
            else
            {
                Paint_SetPixel(x, y, BLACK);
            }
        }
    }
}

bool MandelbrotSet::IsMandelPoint(double fX, double fY, int iterations)
{
    double z_x = fX;
    double z_y = fY;

    for(int i = 0; i < iterations; ++i)
    {
        double z_x_old = z_x;
        z_x = z_x * z_x - z_y * z_y + fX;
        z_y = 2.0 * z_x_old * z_y + fY;
        auto sumSquared = pow(z_x, 2) + pow(z_y, 2);
        if (sumSquared > 4)
        {
            return true;
        }
    }
    return false;
}

unsigned long long MandelbrotSet::GetUniformnessOfArea(double fW, double fH, int xOffset, int yOffset, int wDiv, int hDiv)
{
    unsigned long long uniformness = 0;
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
            int xTest = xOffset + static_cast<int>(fW / wDiv) * wStart + i;
            auto testPoint = Paint_GetPixel(xTest , yTest);
            if(testPoint != firstPoint)
                return false;
        }        
    }

    return true;
}

void MandelbrotSet::ZoomOnInterestingArea()
{   
    tuple<double, double, unsigned long long> choice;
    vector<tuple<double, double, unsigned long long>> choices;

    auto uniformness = GetUniformnessOfArea(this->renderedResX / 2, this->renderedResY / 2, 0, 0, 2, 2);
    choice = {this->x - this->w/4, this->y + this->h/4, uniformness};

    choices.emplace_back(choice);

    uniformness = GetUniformnessOfArea(this->renderedResX / 2, this->renderedResY / 2, this->renderedResX / 2, 0, 2, 2);
    choice = {this->x + this->w/4, this->y + this->h/4, uniformness};

    choices.emplace_back(choice);

    uniformness = GetUniformnessOfArea(this->renderedResX / 2, this->renderedResY / 2, 0, this->renderedResY / 2, 2, 2);
    choice = {this->x - this->w/4, this->y - this->h/4, uniformness};
    choices.emplace_back(choice);

    uniformness = GetUniformnessOfArea(this->renderedResX / 2, this->renderedResY / 2, this->renderedResX / 2, this->renderedResY / 2, 2, 2);
    choice = {this->x + this->w/4, this->y - this->h/4, uniformness};
    choices.emplace_back(choice);     

    w = w / 2.0;
    h = h / 2.0;

    choices.erase(std::remove_if(
        choices.begin(),
        choices.end(),
        [](const tuple<double, double, unsigned long long>& x) { 
            return (std::get<unsigned long long>(x) >= 4); 
        }), choices.end());

    auto lessUniformChoices = choices;
    lessUniformChoices.erase(std::remove_if(
        lessUniformChoices.begin(),
        lessUniformChoices.end(),
        [](const tuple<double, double, unsigned long long>& x) { 
            return (std::get<unsigned long long>(x) >= 3); 
        }), lessUniformChoices.end());
    
    // Seed
    random_device rd;
    mt19937 g(rd());

    if(lessUniformChoices.size() > 0)
    {
            shuffle(lessUniformChoices.begin(), lessUniformChoices.end(), g);
            auto selection = lessUniformChoices[0];
            this->x = get<0>(selection);
            this->y = get<1>(selection);
    }
    else
    {
            shuffle(choices.begin(), choices.end(), g);
            auto selection = choices[0];
            this->x = get<0>(selection);
            this->y = get<1>(selection);
    }
}

