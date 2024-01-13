
#include "DEV_Config.h"

class MandelbrotSet
{
public:
    void InitMandelbrotSet();
    void Render(UWORD xResolution, UWORD yResolution);

    UBYTE w;
    UBYTE h;
    UBYTE x;
    UBYTE y;
    UBYTE* rendered;
    UWORD renderedResX;
    UWORD renderedResY;
};

