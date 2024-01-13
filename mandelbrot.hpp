
#include "DEV_Config.h"

class MandelbrotSet
{
public:
    void InitMandelbrotSet();
    void Render(UWORD xResolution, UWORD yResolution);
    
    UBYTE* rendered;
    UWORD w;
    UWORD h;
    UWORD x;
    UWORD y;
    UWORD renderedResX;
    UWORD renderedResY;
};

