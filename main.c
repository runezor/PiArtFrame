#include <stdlib.h>     //exit()
#include <signal.h>     //signal()
#include "EPD_Test.h"   //Examples
#include "EPD_7in5_V2.h"
#include <time.h>

#include "mandelbrot.hpp"

void  Handler(int signo)
{
    //System Exit
    printf("\r\nHandler:exit\r\n");
    DEV_Module_Exit();

    exit(0);
}

int main(void)
{
    // Exception handling:ctrl + c
    signal(SIGINT, Handler);
    
    printf("Test displaying image. \r\n");
    if(DEV_Module_Init()!=0){
        return -1;
    }

    printf("e-Paper Init and Clear...\r\n");
    EPD_7IN5_V2_Init();

    EPD_7IN5_V2_Clear();

    DEV_Delay_ms(500);

    // Compute image size 
    UWORD Imagesize = ((EPD_7IN5_V2_WIDTH % 8 == 0)? (EPD_7IN5_V2_WIDTH / 8 ): (EPD_7IN5_V2_WIDTH / 8 + 1)) * EPD_7IN5_V2_HEIGHT;
    UBYTE* img = NULL;

    // Allocate memory for image
    if((img = (UBYTE *)malloc(Imagesize)) == NULL) {
        printf("Failed to apply for image memory...\r\n");
        return -1;
    }
    printf("Paint_NewImage\r\n");
    Paint_NewImage(img, EPD_7IN5_V2_WIDTH, EPD_7IN5_V2_HEIGHT, 0, WHITE);
    Paint_SelectImage(img);

    MandelbrotSet mandelbrot;
    mandelbrot.InitMandelbrotSet();
    mandelbrot.SetRender(img);

    mandelbrot.Render(EPD_7IN5_V2_WIDTH, EPD_7IN5_V2_HEIGHT);
    EPD_7IN5_V2_Display(img);
    return 0;

    // Alternate pixels test code
    int pixelCtr = 0;
    UBYTE pixelColor = WHITE;
    for(int i = 0; i < EPD_7IN5_V2_WIDTH; ++i)
    {
        pixelColor = ~pixelColor;

        for(int j = 0; j < EPD_7IN5_V2_HEIGHT; ++j)
        {
            UBYTE selectedPixelColor = pixelColor;
            if(pixelCtr % 2 == 0)
                selectedPixelColor = ~pixelColor;
            Paint_SetPixel(i, j, selectedPixelColor);
            pixelCtr++;
        }
    }

   EPD_7IN5_V2_Display(img);
#if epd7in5V2
    //EPD_7in5_V2_test();
#else
    printf("Please specify the EPD model when making. \r\n");
    printf("Example: When you run the EPD_7in5_V2_test() program, input: sudo make clean && make EPD=epd7in5V2 \r\n");
    printf("Don't know which program you need to run? Refer to the user manual (Wiki) and main.c \r\n");
#endif
    
    return 0;
}
