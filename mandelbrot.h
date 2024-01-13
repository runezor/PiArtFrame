
#include "DEV_Config.h"

typedef struct MandelbrotSetData
{
    UBYTE w;
    UBYTE h;
    UBYTE x;
    UBYTE y;
    UBYTE* rendered;
    UWORD renderedResX;
    UWORD renderedResY;
} MandelbrotSetData;

void Render(MandelbrotSetData setData, UWORD xResolution, UWORD yResolution);