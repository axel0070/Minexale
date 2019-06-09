/* Keep these headers */
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <tice.h>

/* Standard headers */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fileioc.h>
#include <graphx.h>

int Inv[21]; //Inv[ID]=Nombre d'item
int map[50][128];
int Hbar[6]={1,2,3,4,5,17}; //Hbar[Position]=ID
int X=5,Y=0,touches=0,move=20,height=20,legs=0,falling=0,directions=0,jump=0,Hand=1;
void save(void);
void load(void);

/* Declare some variables */
const char *appvarName = "MySAVE";

#define VAR1_VALUE 10
#define VAR2_VALUE 20

/* Main Function */
void save(void) {

    ti_var_t myAppVar;


    /* Close any files that may be open already */
    ti_CloseAll();

    /* Open a new variable; deleting it if it already exists */
    myAppVar = ti_Open(appvarName, "w");

    /* Make sure we opened okay */
    if (!myAppVar)                                          goto err;

    /* Write the structure to the appvar */
    if (ti_Write(&map, sizeof(map), 1, myAppVar) != 1)  goto err;
    if (ti_Write(&Inv, sizeof(Inv), 1, myAppVar) != 1)  goto err;
    if (ti_Write(&move, sizeof(move), 1, myAppVar) != 1)  goto err;
    if (ti_Write(&height, sizeof(height), 1, myAppVar) != 1)  goto err;
    if (ti_Write(&X, sizeof(X), 1, myAppVar) != 1)  goto err;
    if (ti_Write(&Y, sizeof(Y), 1, myAppVar) != 1)  goto err;

    /* Go back to the start of the file */
    if (ti_Rewind(myAppVar) == EOF)                         goto err;

    /* Let's read it just to make sure we wrote it correctly */
    if (ti_Read(&map, sizeof(map), 1, myAppVar) != 1)   goto err;

    goto noerr;

err:
return;
noerr:

    /* Close all open files */
    ti_CloseAll();

}




void load(void)
{


    ti_var_t myAppVar;

    /* Close any files that may be open already */
    ti_CloseAll();

    /* Open a new variable; deleting it if it already exists */
    myAppVar = ti_Open(appvarName, "w");

    /* Make sure we opened okay */
    if (!myAppVar)                                          goto err;

    /* Let's read it just to make sure we wrote it correctly */
    if (ti_Read(&map, sizeof(map), 1, myAppVar) != 1)   goto err;
    if (ti_Read(&Inv, sizeof(Inv), 1, myAppVar) != 1)   goto err;
    if (ti_Read(&move, sizeof(move), 1, myAppVar) != 1)   goto err;
    if (ti_Read(&height, sizeof(height), 1, myAppVar) != 1)   goto err;
    if (ti_Read(&X, sizeof(X), 1, myAppVar) != 1)   goto err;
    if (ti_Read(&Y, sizeof(Y), 1, myAppVar) != 1)   goto err;
    goto noerr;

err:

noerr:
    /* Pause */

    /* Close all open files */
    ti_CloseAll();



}