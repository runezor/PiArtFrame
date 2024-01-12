#include <stdlib.h>     //exit()
#include <signal.h>     //signal()
#include "EPD_Test.h"   //Examples
#include "EPD_7in5_V2.h"
#include <time.h>

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

    struct timespec start={0,0}, finish={0,0}; 
    //clock_gettime(CLOCK_REALTIME,&start);
    EPD_7IN5_V2_Clear();
    //clock_gettime(CLOCK_REALTIME,&finish);
    //printf("%ld S\r\n",finish.tv_sec-start.tv_sec);
    DEV_Delay_ms(500);



    UWORD Imagesize = ((EPD_7IN5_V2_WIDTH % 8 == 0)? (EPD_7IN5_V2_WIDTH / 8 ): (EPD_7IN5_V2_WIDTH / 8 + 1)) * EPD_7IN5_V2_HEIGHT;

    UBYTE* img = malloc(Imagesize*sizeof(UWORD));
    for(int i = 0; i < Imagesize*sizeof(UWORD); ++i)
    {
        if(i%2 == 0)
            img[i] = 1;
        else
            img[i] = 0;

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
