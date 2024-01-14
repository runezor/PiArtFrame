
#include "DEV_Config.h"

class MandelbrotSet
{
public:
    void InitMandelbrotSet();
    void Render(UWORD xResolution, UWORD yResolution);
    void SetRender(UBYTE* image);
    UBYTE* GetRender() { return rendered; };
    void ZoomOnInterestingArea();

private:
    bool IsMandelPoint(double x, double y, int iterations);
    unsigned long long GetUniformnessOfArea(double fW, double fH, int xOffset, int yOffset, int wDiv, int hDiv);
    bool IsAreaUniform(int xOffset, int yOffset, double fW, double fH,  int wDiv, int hDiv, double wStart, double hStart);

    UBYTE* rendered;
    double w;
    double h;
    double x;
    double y;
    UWORD renderedResX;
    UWORD renderedResY;
};

