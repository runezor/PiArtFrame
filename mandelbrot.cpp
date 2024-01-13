#include "mandelbrot.hpp"
#include <cmath>

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