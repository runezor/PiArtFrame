
#include "DEV_Config.h"

class MandelbrotSet
{
public:
    void InitMandelbrotSet();
    void Render(UWORD xResolution, UWORD yResolution);
    void SetRender(UBYTE* image);
    UBYTE* GetRender() { return rendered; };
    bool IsMandelPoint(double x, double y, int iterations);

private:
    UBYTE* rendered;
    double w;
    double h;
    double x;
    double y;
    UWORD renderedResX;
    UWORD renderedResY;
};

