#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <tice.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "images_gfx.h"
#include "map.c"

void main(void)
{
    ti_var_t file;
    int ReturnDetect=0,save=0;
    srand(rtc_Time());
    gfx_Begin( gfx_8bpp );
    gfx_SetPalette(images_gfx_pal, sizeof_images_gfx_pal, 0);

    /*Are there a save ?*/
    ti_CloseAll();
	file = ti_Open("MySAVE", "r");
	if ( file ) save=1;

    Generate();
    StartMenu(save);


    PrintFullMap(X,Y);

while(touches!=105)
{
    Gravity();
    if(falling==1)
{gfx_SetDrawBuffer();
    Gravity();
Falling();
gfx_SwapDraw();}
    touches=key();



gfx_SetDrawBuffer();
ReturnDetect=Detect();
if(ReturnDetect!=2)
{
gfx_SetColor(13);
gfx_FillRectangle(0,0,40,90);
printIntXY(X,10,0,3);
printIntXY(Y,10,10,3);
printIntXY(move,10,30,3);
printIntXY(height,10,40,3);
printIntXY(falling,10,50,3);
printIntXY(Hbar[Hand],10,70,3);
printIntXY(Hand,10,80,3);
HotBar(0);
gfx_SwapDraw();

}




}    //Fin while

    gfx_End();
    prgm_CleanUp();
}
