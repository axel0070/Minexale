#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <tice.h>

/* Standard headers */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <graphx.h>
#include "images_gfx.h"
#include "fonctions.c"
#include "save.c"

int k=0,j=1;

//fonctions
void Generate(void);
void fix(void);
void tree(void);
void PrintBlock(int j, int k,int X, int Y);
void PrintFullMap(int PosX, int PosY);
int Detect(void);
void fixmove(void);
void mvt(void);
void fixheight(void);
void Coals(void);
void Gravity(void);
void Falling(void);
int HeadFree(void);
void LaunchJump(void);
void StartMenu(int save);
void Destroy(void);
void Inventory(void);
void HotBar(int Open);
void PrintSprite(int ID,int X,int Y);





void Generate(void)
{
int Random=0;
srand(rtc_Time());

for(j=0;j<8;j++) //debut ciel
{
for (k=0;k<128;k++)
{
map[j][k]=0;  //ciel
}
} //Fin pour ciel j=8



for (k=0;k<128;k++) //Debut sol j=8
{
Random=randInt(1,2);
if(Random==1)
{
map[j][k]=0; //Air
}

if(Random==2)
{
map[j][k]=2; //Grass
}
}
j++; //j=9

for (k=0;k<128;k++)
{
map[j][k]=3;  //Dirt
}

for(j=10;j<12;j++)
{
for (k=0;k<128;k++)
{
Random=randInt(1,2);
if(Random==1)
{
map[j][k]=1; //Stone
}

if(Random==2)
{
map[j][k]=3; //Dirt
}
}
} //Fin j de 10 à 12

for(j=12;j<50;j++) //debut sol
{
for (k=0;k<128;k++)
{
map[j][k]=1;  //roche
}
}                 //Fin sol

fix();
tree();
Coals();
//Bedrock
for(j=0;j<50;j++)
{
map[j][0]=7;
map[j][127]=7;
}

for(k=0;k<127;k++)
{
map[49][k]=7;
}
} //Fin Generate


void fix(void)
{
int i=0;
    for(i=0;i<126;i++)
{
if(map[8][i]==2 && map[8][i+1]==0 && map[8][i+2]==2)
{
    map[8][i+1]=2;
}

if(map[8][i]==0 && map[8][i+1]==2 && map[8][i+2]==0)
{
    map[8][i+1]=0;

}

if(map[8][i]==0 && map[9][i]==3)
{
map[9][i]=2;
}




    } //Fin For



} //Fin fonction


void tree(void)
{
    int X,i=0;
    srand(rtc_Time());

        for(i=0;i<5;i++)
{
X = randInt(i*25+5,25+i*25);
map[8][X]=17; //tronc
map[7][X]=17; //tronc
map[6][X]=17; //tronc
map[5][X]=18;
map[5][X-2]=18;
map[5][X-1]=18;
map[5][X+1]=18;
map[5][X+2]=18;
map[4][X]=18;
map[4][X-1]=18;
map[4][X+1]=18;
map[4][X+2]=18;
map[3][X]=18;
        }
}

void Coals(void)
{
    int C,i=0;
    srand(rtc_Time());

for(i=0;i<4;i++)
{
C = randInt(i*30+5,30+i*25);
map[15][C-3]=16;
map[15][C-2]=16;
map[15][C]=16;
map[15][C+1]=16;
map[16][C]=16;
map[16][C-1]=16;
map[14][C-1]=16;
map[14][C+1]=16;
map[14][C]=16;
map[13][C]=16;
}

}

void Golds(void)
{


}


void PrintBlock(int j, int k,int X, int Y)
{

if(map[j][k]==0) //air
{
gfx_Sprite(Air_0, X, Y);
return;
}

if(map[j][k]==1) //Stone
{
gfx_Sprite(Stone, X, Y);
return;
}

if(map[j][k]==2) //Grass
{
gfx_Sprite(Grass, X, Y);
return;
}
if(map[j][k]==3) //Dirt
{
gfx_Sprite(Dirt, X, Y);
return;
}
if(map[j][k]==4) //Cobblestone
{
gfx_Sprite(Cobblestone, X, Y);
return;
}
if(map[j][k]==5) //Oak
{
gfx_Sprite(Oak, X, Y);
return;
}
if(map[j][k]==6) //Sappling
{
gfx_Sprite(Sapling, X, Y);
return;
}
if(map[j][k]==7) //Bedrock
{
gfx_Sprite(Bedrock, X, Y);
return;
}
if(map[j][k]==8) //Water
{
gfx_Sprite(Water, X, Y);
return;
}

/*WATER FALLING HERE*/


if(map[j][k]==10) //lava
{
gfx_Sprite(Lava, X, Y);
return;
}

/*LAVA FALLING HERE*/

if(map[j][k]==12) //Sand
{
gfx_Sprite(Sand, X, Y);
return;
}
if(map[j][k]==13) //Gravel
{
gfx_Sprite(Gravel, X, Y);
return;
}
if(map[j][k]==14) //Gold
{
gfx_Sprite(Gold, X, Y);
return;
}
if(map[j][k]==15) //Iron
{
gfx_Sprite(Iron, X, Y);
return;
}
if(map[j][k]==16) //Coal
{
gfx_Sprite(Coal, X, Y);
return;
}
if(map[j][k]==17) //Log
{
gfx_Sprite(Log, X, Y);
return;
}
if(map[j][k]==18) //Leaves
{
gfx_Sprite(Leaves, X, Y);
return;
}
if(map[j][k]==19) //Sponge
{
gfx_Sprite(Sponge, X, Y);
return;
}
if(map[j][k]==20) //Glass
{
gfx_Sprite(Glass, X, Y);
return;
}


}


void PrintFullMap(int PosX, int PosY) //X/Y = coordonnée fenetres
{
int BX=0,BY=0; //Coordonnées blocs à poser

j=0;
k=0;

while(j+PosY != 12+PosY)
{

    while(k+PosX != (16+PosX))
{
BX=20*k-(move-20);
BY=20*j-(height-20);
PrintBlock(j+PosY,k+PosX,BX,BY);
k++;
    }

j++;
k=0;
}

fixmove();
fixheight();
}

int Detect(void)
{
    /*DETECT TOUCHE NUMEROTE*/

if(touches==92)
{Hand=0;
return 0;}

if(touches==93)
{Hand=1;
return 0;}

if(touches==94)
{Hand=2;
return 0;}

if(touches==82)
{Hand=3;
return 0;}

if(touches==83)
{Hand=4;
return 0;}

if(touches==84)
{Hand=5;
return 0;}


if(touches==72)
{
save();
return 0;}

if(touches==73)
{
load();
PrintFullMap(X,Y);
return 0;}

                                    /*DETECT JUMP TOUCH PRESSED*/

    if(touches==22)
{

if(HeadFree()==1 && jump==0 && falling==0)
{
jump=1;
LaunchJump();
return 0;
}

return 2;}

                                /*FIN JUMP*/

 if(touches==25) //vers le haut
{
directions=1;
PrintFullMap(X,Y);
gfx_Sprite(Steve_2, 160, 120);
return 0;}
if(touches==24) //vers la gauche
{
directions=4;
    Gravity();
}
if(touches==26) //vers la droite
{
directions=2;
    Gravity();
}
if(touches==34) //vers le bas
{
directions=3;
PrintFullMap(X,Y);
gfx_Sprite(Steve_3, 160, 120);
return 0;}





    /*BOUGER A DROITE*/
    if(touches==26 && X==112)
    {
    return 2;}

    if(touches==26 && height>20 && move==20)
    {
    if(map[Y+8][X+9]!=0)
    {
    return 2;}
    }

        if(touches==24 && height>20 && move==20)
    {
    if(map[Y+8][X+7]!=0)
    {
    return 2;}
    }


    if(touches==26 && X<112 && map[Y+6][X+9]==0 && map[Y+7][X+9]==0)
{

if(move==20)
{
move=24;
PrintFullMap(X,Y);
mvt();
return 0;}

if(move==36)
{
move=20;
X++;
PrintFullMap(X,Y);
mvt();
return 0;}

if(move>=4 && move <36)
{
move+=4;
PrintFullMap(X,Y);
mvt();
return 0;}

} //Fin touche == 26
                                        /*BOUGER A GAUCHE*/
    if(touches==24 && X==0)
    {
    return 2;}


    if(touches==24 && X>0 && map[Y+6][X+7]==0 && map[Y+7][X+7]==0)
{
if(move==20)
{
move=16;
PrintFullMap(X,Y);
mvt();
return 0;}

if(move==4)
{
X--;
move=20;
PrintFullMap(X,Y);
mvt();
return 0;}

if(move>4 && move <=36)
{
move-=4;
PrintFullMap(X,Y);
mvt();
return 0;}

} //Fin touche == 24






                                    /*TOUCHE ALPHA CASSER BLOCK*/
if(touches==31)
{nopwait(50000);
Destroy();
return 0;
}
                                                                   /*FIN ALPHA*/


                                    /*TOUCHE 2NDE POSER BLOCK*/
if(touches==21  && Inv[Hbar[Hand]] != 0)
{nopwait(50000);
                    /*POSER BLOCK DECALER SUR LA DROITE*/
    if(move>20)
{
if(directions==1) //POSER block en haut
{map[Y+5][X+9]=Hbar[Hand];
Inv[Hbar[Hand]]--;
PrintFullMap(X,Y);
gfx_Sprite(Steve_2, 160, 120);
return 0;}

if(directions==2) //POSER block a droite
{
if(map[Y+7][X+10]==0)
{map[Y+7][X+10]=Hbar[Hand];
Inv[Hbar[Hand]]--;
PrintFullMap(X,Y);
gfx_Sprite(Steve_1, 160, 120);
return 0;}

if(map[Y+6][X+10]==0)
{map[Y+6][X+10]=Hbar[Hand];
Inv[Hbar[Hand]]--;
PrintFullMap(X,Y);
gfx_Sprite(Steve_1, 160, 120);
return 0;}
}

if(directions==3 && height==20 && map[Y+8][X+9]==0) //POSER block en bas
{map[Y+8][X+9]=Hbar[Hand];
Inv[Hbar[Hand]]--;
PrintFullMap(X,Y);
gfx_Sprite(Steve_3, 160, 120);
return 0;}

if(directions==4) //POSER block a gauche
{
if(map[Y+7][X+8]==0)
{map[Y+7][X+7]=Hbar[Hand];
Inv[Hbar[Hand]]--;
PrintFullMap(X,Y);
gfx_Sprite(Steve_0, 160, 120);
return 0;}

if(map[Y+6][X+8]==0)
{map[Y+6][X+7]=Hbar[Hand];
Inv[Hbar[Hand]]--;
PrintFullMap(X,Y);
gfx_Sprite(Steve_0, 160, 120);
return 0;}
}

gfx_Sprite(Steve_3, 160, 120);
return 0;
}
                         /*POSER BLOCK DECALER SUR LA GAUCHE*/
if(move<20)
{
if(directions==1) //POSER block en haut
{map[Y+5][X+7]=Hbar[Hand];
Inv[Hbar[Hand]]--;
PrintFullMap(X,Y);
gfx_Sprite(Steve_2, 160, 120);
return 0;}

if(directions==2) //POSER block a droite
{
if(map[Y+7][X+9]==0)
{map[Y+7][X+9]=Hbar[Hand];
Inv[Hbar[Hand]]--;
PrintFullMap(X,Y);
gfx_Sprite(Steve_1, 160, 120);
return 0;}

if(map[Y+6][X+9]==0)
{map[Y+6][X+9]=Hbar[Hand];
Inv[Hbar[Hand]]--;
PrintFullMap(X,Y);
gfx_Sprite(Steve_1, 160, 120);
return 0;}
}

if(directions==3 && height==20 && map[Y+8][X+7]==0) //POSER block en bas
{map[Y+8][X+7]=Hbar[Hand];
Inv[Hbar[Hand]]--;
PrintFullMap(X,Y);
gfx_Sprite(Steve_3, 160, 120);
return 0;}

if(directions==4) //POSER block a gauche
{
if(map[Y+7][X+5]==0)
{map[Y+7][X+6]=Hbar[Hand];
Inv[Hbar[Hand]]--;
PrintFullMap(X,Y);
gfx_Sprite(Steve_0, 160, 120);
return 0;}

if(map[Y+6][X+5]==0)
{map[Y+6][X+6]=Hbar[Hand];
Inv[Hbar[Hand]]--;
PrintFullMap(X,Y);
gfx_Sprite(Steve_0, 160, 120);
return 0;}
}

gfx_Sprite(Steve_3, 160, 120);
return 0;
}
/*POSER BLOCK CENTRER (un peu pret)*/

if(directions==1) //POSER block en haut
{map[Y+5][X+8]=Hbar[Hand];
Inv[Hbar[Hand]]--;
PrintFullMap(X,Y);
gfx_Sprite(Steve_2, 160, 120);
return 0;}

if(directions==2) //POSER block a droite
{
if(map[Y+7][X+9]==0)
{map[Y+7][X+9]=Hbar[Hand];
Inv[Hbar[Hand]]--;
PrintFullMap(X,Y);
gfx_Sprite(Steve_1, 160, 120);
return 0;}

if(map[Y+6][X+9]==0)
{map[Y+6][X+9]=Hbar[Hand];
Inv[Hbar[Hand]]--;
PrintFullMap(X,Y);
gfx_Sprite(Steve_1, 160, 120);
return 0;}
}

if(directions==3 && height==20 &&map[Y+8][X+8]==0) //POSER block en bas
{map[Y+8][X+8]=Hbar[Hand];
Inv[Hbar[Hand]]--;
PrintFullMap(X,Y);
gfx_Sprite(Steve_3, 160, 120);
return 0;}

if(directions==4) //POSER block a gauche
{
if(map[Y+7][X+7]==0)
{map[Y+7][X+7]=Hbar[Hand];
Inv[Hbar[Hand]]--;
PrintFullMap(X,Y);
gfx_Sprite(Steve_0, 160, 120);
return 0;}

if(map[Y+6][X+7]==0)
{map[Y+6][X+7]=Hbar[Hand];
Inv[Hbar[Hand]]--;
PrintFullMap(X,Y);
gfx_Sprite(Steve_0, 160, 120);
return 0;}
}
    /*FIN POSER*/


}
/*FIN 2nde*/



if(touches==11)
{

Inventory();
return 0;

}





return 2;
}
/*FIN MODE DETECT*/



void fixmove(void)
{

if(move==24)
{
for(j=0;j<12;j++)
{
PrintBlock(j+Y,16+X,316,20*j-(height-20));
}
    return;}

if(move==28)
{
for(j=0;j<12;j++)
{
PrintBlock(j+Y,16+X,312,20*j-(height-20));
}
    return;}

if(move==32)
{
for(j=0;j<12;j++)
{
PrintBlock(j+Y,16+X,308,20*j-(height-20));
}
    return;}

if(move==36)
{
for(j=0;j<12;j++)
{
PrintBlock(j+Y,16+X,304,20*j-(height-20));
}
    return;}



if(move==16)
{
for(j=0;j<12;j++)
{
PrintBlock(j+Y,X-1,-16,20*j-(height-20));
}
    return;}

if(move==12)
{
for(j=0;j<12;j++)
{
PrintBlock(j+Y,X-1,-12,20*j-(height-20));
}
    return;}

if(move==8)
{
for(j=0;j<12;j++)
{
PrintBlock(j+Y,X-1,-8,20*j-(height-20));
}
    return;}

if(move==4)
{
for(j=0;j<12;j++)
{
PrintBlock(j+Y,X-1,-4,20*j-(height-20));
}
    return;}



} //Fin fonction fixmove

void fixheight(void)
{

    if(height==24)
{
for(k=0;k<17;k++)
{
PrintBlock(Y+12,X+k,20*k-(move-20),236);
}
    return;
}

    if(height==28)
{
for(k=0;k<17;k++)
{
PrintBlock(Y+12,X+k,20*k-(move-20),232);
}
    return;
}

    if(height==32)
{
for(k=0;k<17;k++)
{
PrintBlock(Y+12,X+k,20*k-(move-20),228);
}
    return;
}

    if(height==36)
{
for(k=0;k<17;k++)
{
PrintBlock(Y+12,X+k,20*k-(move-20),224);
}
    return;
}

    if(height==16)
{
for(k=0;k<17;k++)
{
PrintBlock(Y,X+k,20*k-(move-20),-16);
}
    return;
}


    if(height==12)
{
for(k=0;k<17;k++)
{
PrintBlock(Y,X+k,20*k-(move-20),-12);
}
    return;
}

    if(height==8)
{
for(k=0;k<17;k++)
{
PrintBlock(Y,X+k,20*k-(move-20),-8);
}
    return;
}

    if(height==4)
{
for(k=0;k<17;k++)
{
PrintBlock(Y,X+k,20*k-(move-20),-4);
}
    return;
}





}






void mvt(void)
{

if(touches==26 && legs != 2)
{
gfx_Sprite(Steve_1, 160, 120);
legs++;
return;}

if(touches==26 && legs == 2)
{
gfx_Sprite(Steve_4, 160, 120);
legs=0;
    return;}

if(touches==24 && legs != 2)
{
gfx_Sprite(Steve_5, 160, 120);
legs++;
    return;}

if(touches==24 && legs == 2)
{
gfx_Sprite(Steve_0, 160, 120);
legs=0;
    return;}

if(touches==25)
{
gfx_Sprite(Steve_2, 160, 120);
legs=0;
    return;}

if(touches==34)
{
gfx_Sprite(Steve_3, 160, 120);
legs=0;
    return;}


}


void Gravity(void)
{

if(move==20 && map[Y+8][X+8]==0)
{
falling=1;
return;}

if(move==20 && map[Y+8][X+8]!=0)
{
falling=0;
return;}

if (move>20 && move <=36)
{

    if (map[Y+8][X+8]==0 && map[Y+8][X+9]==0)
    {falling=1;
    return;}

    if (map[Y+8][X+8]!=0 && map[Y+8][X+9]==0)
    {falling=0;
    return;}

    if (map[Y+8][X+8]==0 && map[Y+8][X+9]!=0)
    {falling=0;
    return;}

    if (map[Y+8][X+8]!=0 && map[Y+8][X+9]!=0)
    {falling=0;
    return;}
}

if (move<20 && move >=4)
{

    if (map[Y+8][X+8]==0 && map[Y+8][X+7]==0)
    {falling=1;
    return;}

    if (map[Y+8][X+8]!=0 && map[Y+8][X+7]==0)
    {falling=0;
    return;}

    if (map[Y+8][X+8]==0 && map[Y+8][X+7]!=0)
    {falling=0;
    return;}

    if (map[Y+8][X+8]!=0 && map[Y+8][X+7]!=0)
    {falling=0;
    return;}

}




}

void Falling(void)
{
                              /*BOUGER EN BAS*/
    if(falling==1 && Y<38)
{
if(height==20)
{
height=24;
PrintFullMap(X,Y);
if(directions==2)
{gfx_Sprite(Steve_1, 160, 120);
}
if(directions==4)
{gfx_Sprite(Steve_0, 160, 120);
}
if(directions==3)
{gfx_Sprite(Steve_3, 160, 120);
}
if(directions==1)
{gfx_Sprite(Steve_2, 160, 120);
}
return;}

if(height==36)
{
Y++;
height=20;
PrintFullMap(X,Y);
if(directions==2)
{gfx_Sprite(Steve_1, 160, 120);
}
if(directions==4)
{gfx_Sprite(Steve_0, 160, 120);
}
if(directions==3)
{gfx_Sprite(Steve_3, 160, 120);
}
if(directions==1)
{gfx_Sprite(Steve_2, 160, 120);
}
return;}

if(height>=4 && height <36)
{
height+=4;
PrintFullMap(X,Y);
if(directions==2)
{gfx_Sprite(Steve_1, 160, 120);
}
if(directions==4)
{gfx_Sprite(Steve_0, 160, 120);
}
if(directions==3)
{gfx_Sprite(Steve_3, 160, 120);
}
if(directions==1)
{gfx_Sprite(Steve_2, 160, 120);
}
return;}

} //Fin falling == 1

}

int HeadFree(void)
{
if(move==20 && map[Y+5][X+8]==0)
{return 1;
}
if (move>20 && move <=36)
{

    if (map[Y+5][X+8]==0 && map[Y+5][X+9]==0)
    {
    return 1;}

    if (map[Y+5][X+8]!=0 && map[Y+5][X+9]==0)
    {
    return 0;}

    if (map[Y+5][X+8]==0 && map[Y+5][X+9]!=0)
    {
    return 0;}

    if (map[Y+8][X+8]!=0 && map[Y+8][X+9]!=0)
    {
    return 0;}
}

if (move<20 && move >=4)
{

    if (map[Y+5][X+8]==0 && map[Y+5][X+7]==0)
    {
    return 1;}

    if (map[Y+5][X+8]!=0 && map[Y+5][X+7]==0)
    {
    return 0;}

    if (map[Y+5][X+8]==0 && map[Y+5][X+7]!=0)
    {
    return 0;}

    if (map[Y+5][X+8]!=0 && map[Y+5][X+7]!=0)
    {
    return 0;}

}

return 0;
}

void LaunchJump(void)
{ //gfx_SetDrawBuffer(); - gfx_SwapDraw();
    /* Key variable */
    kb_key_t key;
    kb_key_t key2;
if(jump==1)
{ //TRUC A FAIRE =
  //Deplacer vers le haut en considerant le déplacement possible
  //Prevoir la destruction d'objet ?
  //Activé la gravité ou crée un module indépendant ?
  //Modifier le module de gravité pour le rendre indé et évité lag

    while(height>0)
{gfx_SetDrawBuffer();
height-=4;
            /**/
        kb_Scan();
        key = kb_Data[7];
        key2= kb_Data[1];
        if(key2)
        {
        switch (key) {
            case kb_Down:           /* Change screen color to black */
                //rien
                break;
            case kb_Right:          /* Change screen color to red */
                if(map[Y+5][X+9]==0 && map[Y+6][X+9]==0 && map[Y+7][X+9]==0)
                {
                move+=4;
                }
                break;
            case kb_Up:             /* Change screen color to white */
                //rien
                break;
            case kb_Left:           /* Change screen color to a different red */
                if(map[Y+5][X+7]==0 && map[Y+6][X+7]==0 && map[Y+7][X+7]==0)
                {
                move-=4;
                }
                break;
            default:
                break;
        }
        }
        else
        {
switch (key) {
            case kb_Down:           /* Change screen color to black */
                //rien
                break;
            case kb_Right:          /* Change screen color to red */
                if(map[Y+5][X+9]==0 && map[Y+6][X+9]==0 && map[Y+7][X+9]==0)
                {
                move+=4;
                }
                break;
            case kb_Up:             /* Change screen color to white */
                //rien
                break;
            case kb_Left:           /* Change screen color to a different red */
                if(map[Y+5][X+7]==0 && map[Y+6][X+7]==0 && map[Y+7][X+7]==0)
                {
                move-=4;
                }
                break;
            default:
                break;
        }

        }
if(move<=4)
{
X--;
move=20;
}
if(move>=36)
{
X++;
move=20;
}
/**/
PrintFullMap(X,Y);
gfx_Sprite(Steve_0, 160, 120);
gfx_SwapDraw();} //FIN WHILE

/*LE JOUEUR EST EN HAUT*/
gfx_SetDrawBuffer();
Y--;
height=16;
PrintFullMap(X,Y);
gfx_Sprite(Steve_0, 160, 120);
gfx_SwapDraw();

//Have to detect posé block
kb_Scan();
key2= kb_Data[1];

        /* Print the current arrow key input */
        if (key2 & kb_2nd)
        { if(key2 & kb_Mode)
        {
    if(Inv[Hbar[Hand]]>0 && map[Y+8][X+8]==0)
    {
    map[Y+8][X+8]=Hbar[Hand];
    Inv[Hbar[Hand]]--;
    gfx_SetDrawBuffer();
    height=20;
    PrintFullMap(X,Y);
    gfx_Sprite(Steve_0, 160, 120);
    gfx_SwapDraw();
    }
    }
        }

/*START FALLING YEAH*/
Gravity();
while(falling!=0)
{
gfx_SetDrawBuffer();
height+=4;
            /**/
        kb_Scan();
        key = kb_Data[7];
        key2= kb_Data[1];
        if(key2)
        {
        switch (key) {
            case kb_Down:
                //rien
                break;
            case kb_Right:
                if(map[Y+6][X+9]==0 && map[Y+7][X+9]==0)
                {
                move+=4;
                }
                break;
            case kb_Up:
                //rien
                break;
            case kb_Left:
                if(map[Y+6][X+7]==0 && map[Y+7][X+7]==0)
                {
                move-=4;
                }
                break;
            default:
                break;
        }
        }
        else
        {
switch (key) {
            case kb_Down:
                //rien
                break;
            case kb_Right:
                if(map[Y+6][X+9]==0 && map[Y+7][X+9]==0)
                {
                move+=4;
                }
                break;
            case kb_Up:
                //rien
                break;
            case kb_Left:
                if(map[Y+6][X+7]==0 && map[Y+7][X+7]==0)
                {
                move-=4;
                }
                break;
            default:
                break;
        }

        }
if(move<=4)
{
X--;
move=20;
}
if(move>=36)
{
X++;
move=20;
}


if(height>=36)
{Y++;
height=20;
}
PrintFullMap(X,Y);
gfx_Sprite(Steve_0, 160, 120);
gfx_SwapDraw();
Gravity();
} //Fin falling


    /*Pour être sur*/
if(height>=32)
{Y++;
height=20;
}
if(height<=16)
{
height=20;
}
gfx_SetDrawBuffer();
PrintFullMap(X,Y);
gfx_Sprite(Steve_0, 160, 120);
gfx_SwapDraw();

jump=0;
} //Fin si jump=1
    return;





}







void StartMenu(int save)
{
int i=0,j=0,touches=0; //Coordonnées blocs à poser
for(j=0;j<12;j++)
{
    for(i=0;i<16;i++)
    {
    gfx_Sprite(Stone, i*20, j*20);
    }




}
gfx_SetColor(34);
gfx_FillRectangle(100,0,60,20);
gfx_FillRectangle(0,20,20,40);
gfx_FillRectangle(40,80,120,20);
gfx_FillRectangle(60,100,80,80);
gfx_FillRectangle(220,80,40,20);
gfx_FillRectangle(280,80,20,20);
gfx_FillRectangle(300,40,20,20);
gfx_FillRectangle(220,80,40,20);
gfx_FillRectangle(200,160,80,60);

gfx_Sprite(Stone, 60, 160);
gfx_Sprite(Stone, 120, 140);
gfx_Sprite(Stone, 120, 160);
gfx_Sprite(Water, 220, 85);
gfx_Sprite(Water, 240, 85);
gfx_Sprite(Water, 280, 85);
gfx_Sprite(Lava, 200, 205);
gfx_Sprite(Lava, 220, 205);
gfx_Sprite(Stone,240, 200);
gfx_Sprite(Stone, 200, 160);
gfx_Sprite(Stone,260, 200);

gfx_Sprite(Bedrock,0, 220);
gfx_Sprite(Bedrock,80, 220);
gfx_Sprite(Bedrock,100, 220);
gfx_Sprite(Bedrock,180, 220);
gfx_Sprite(Bedrock,200, 220);
gfx_Sprite(Bedrock,220, 220);
gfx_Sprite(Bedrock,240, 220);
gfx_Sprite(Bedrock,280, 220);
gfx_Sprite(Bedrock,280, 200);
gfx_Sprite(Bedrock,20, 200);
gfx_Sprite(Bedrock,140, 200);

gfx_Sprite(Gravel,20, 80);
gfx_Sprite(Gravel,40, 100);
gfx_Sprite(Gravel,20, 100);
gfx_Sprite(Gravel,20, 120);
gfx_Sprite(Gravel,0, 100);
gfx_Sprite(Gravel,0, 120);
gfx_Sprite(Gravel,0, 140);

gfx_Sprite(Dirt,20,0);
gfx_Sprite(Dirt,160,0);
gfx_Sprite(Dirt,300,0);
gfx_Sprite(Dirt,300,20);

gfx_Sprite(Iron,140,120);
gfx_Sprite(Iron,160,120);
gfx_Sprite(Iron,140,140);

if(save!=0)
{    gfx_PrintStringXY("Graph to load the save",90,230);

}



gfx_Sprite(Logo_0, 20, 20);
gfx_Sprite(Logo_1, 160, 20);


    while(touches!=13)
{
touches=key();
    nopwait(50000);
    gfx_SetTextFGColor(randInt(0,255));
    gfx_PrintStringXY("Zoom to play",125,140);


if(touches==15 && save !=0)
{
load();
 gfx_SetTextFGColor(0);
 gfx_PrintStringXY("MySAVE loaded",120,150);
}
}
}



void Destroy(void)
{

int Xdecal=0,Ydecal=0,block;

if(move>28)
{Xdecal=9;
}

if(move<=28 && move>=12)
{Xdecal=8;
}

if(move<12)
{Xdecal=7;
}



if(directions==1)
{Ydecal=5;
 if(move>28)
 {Xdecal=9;
 }
  if(move<12)
 {Xdecal=7;
 }
}

if(directions==2 && map[Y+7][X+Xdecal+1]!=0)
{Ydecal=7;
Xdecal++;
}
if(directions==2 && map[Y+7][X+Xdecal]==0)
{Ydecal=6;
Xdecal++;
}

if(directions==3)
{Ydecal=8;
  if(move>28)
 {Xdecal=9;
 }
  if(move<12)
 {Xdecal=7;
 }
}

if(directions==4 && map[Y+7][X+Xdecal-1]!=0)
{Ydecal=7;
Xdecal--;
}
if(directions==4 && map[Y+7][X+Xdecal]==0)
{Ydecal=6;
Xdecal--;
}
if(map[Y+Ydecal][X+Xdecal]!=0)
{

    block=map[Y+Ydecal][X+Xdecal];

    if(block !=1 && block != 2 && block !=7 && block != 8 && block !=9 && block !=10 && block !=11 && block !=18 && block !=20)

       {
Inv[map[Y+Ydecal][X+Xdecal]]++;
map[Y+Ydecal][X+Xdecal]=0;}

if(block==1) //Si stone cassé gagné 1 cobble
{Inv[4]++;
map[Y+Ydecal][X+Xdecal]=0;}

if(block==2)
{Inv[3]++;
map[Y+Ydecal][X+Xdecal]=0;}

if(block==7)
{
return;}

if(block==8 || block==9 || block==10 || block==11)
{
return;}

if(block==18)
{Inv[6]++;
map[Y+Ydecal][X+Xdecal]=0;}

if(block==20)
{
map[Y+Ydecal][X+Xdecal]=0;}

PrintFullMap(X,Y);
return;}


return;}


void Inventory(void)
{
    int i=1,Yb=0,Xb=0,touches=0;
    nopwait(50000);


while(touches!=11)
{
touches=key();
    gfx_SetDrawBuffer();
    PrintFullMap(X,Y);

if(touches==26 && i<20)
{i++;
}

if(touches==24 && i>0)
{i--;
}

if(touches==34 && i<=12)
{i+=8;
}

if(touches==25 && i>=9)
{i-=8;
}

        if(touches==92)
    {Hbar[0]=i;
    }
        if(touches==93)
    {Hbar[1]=i;
    }
        if(touches==94)
    {Hbar[2]=i;
    }
        if(touches==82)
    {Hbar[3]=i;
    }
        if(touches==83)
    {Hbar[4]=i;
    }
        if(touches==84)
    {Hbar[5]=i;
    }
    gfx_SetColor(152);
    gfx_SetTextFGColor(0);

gfx_FillRectangle(20,20,280,200);

gfx_SetColor(71);

if(i<=8 && i>0)
{
Xb=i;
Yb=1;
}

if(i>8 && i<=16)
{
Xb=i-8;
Yb=2;
}

if(i>16 && i<=20)
{
Xb=i-16;
Yb=3;
}

    if(i==0)
    {i=1;
    }
    gfx_FillRectangle(12+Xb*30,7+30*Yb,26,26);

    gfx_Sprite(Stone, 45, 40);
printIntXY(Inv[1],53,55,2);

    gfx_Sprite(Grass, 75, 40);
printIntXY(Inv[2],83,55,2);

    gfx_Sprite(Dirt, 105, 40);
printIntXY(Inv[3],113,55,2);

    gfx_Sprite(Cobblestone, 135, 40);
printIntXY(Inv[4],143,55,2);

    gfx_Sprite(Oak, 165, 40);
printIntXY(Inv[5],173,55,2);

    gfx_Sprite(Sapling, 195, 40);
printIntXY(Inv[6],203,55,2);

    gfx_Sprite(Bedrock, 225, 40);
printIntXY(Inv[7],233,55,2);

    gfx_Sprite(Water, 255, 45);
printIntXY(Inv[8],263,55,2);

        gfx_Sprite(Water, 45, 75);
printIntXY(Inv[9],53,85,2);

    gfx_Sprite(Lava, 75, 75);
printIntXY(Inv[10],83,85,2);

    gfx_Sprite(Lava, 105, 75);
printIntXY(Inv[11],113,85,2);

    gfx_Sprite(Sand, 135, 70);
printIntXY(Inv[12],143,85,2);

    gfx_Sprite(Gravel, 165, 70);
printIntXY(Inv[13],173,85,2);

    gfx_Sprite(Gold, 195, 70);
printIntXY(Inv[14],203,85,2);

    gfx_Sprite(Iron, 225, 70);
printIntXY(Inv[15],233,85,2);

    gfx_Sprite(Coal, 255, 70);
printIntXY(Inv[16],263,85,2);

    gfx_Sprite(Log, 45, 100);
printIntXY(Inv[17],53,115,2);

    gfx_Sprite(Leaves, 75, 100);
printIntXY(Inv[18],83,115,2);

    gfx_Sprite(Sponge, 105, 100);
printIntXY(Inv[19],113,115,2);

    gfx_Sprite(Glass, 135, 100);
printIntXY(Inv[20],143,115,2);


HotBar(1);
gfx_SetColor(255);
gfx_Rectangle(60,195,190,30);

    gfx_SwapDraw();
}
    nopwait(50000);

PrintFullMap(X,Y);
}


void HotBar(int Open)
{
int i =0;

gfx_SetTextFGColor(0);
gfx_SetColor(152);
gfx_FillRectangle(60,195,190,30);
gfx_SetColor(71);
if(Open==0)
{

    if(Hand==0)
{
gfx_FillRectangle(67,197,26,26);
}
    if(Hand==1)
{
gfx_FillRectangle(97,197,26,26);
}
    if(Hand==2)
{
gfx_FillRectangle(127,197,26,26);
}
    if(Hand==3)
{
gfx_FillRectangle(157,197,26,26);
}
    if(Hand==4)
{
gfx_FillRectangle(187,197,26,26);
}
    if(Hand==5)
{
gfx_FillRectangle(217,197,26,26);
}
}

for(i=0;i<6;i++)
{
PrintSprite(Hbar[i],30*i+70,200);
printIntXY(Inv[Hbar[i]],30*i+70+8,215,2);
}



}

void PrintSprite(int ID,int X,int Y)
{
 if(ID==0) {gfx_Sprite(Air_0, X, Y);
return;}

 if(ID==1) {gfx_Sprite(Stone, X, Y);
return;}

 if(ID==2) {gfx_Sprite(Grass, X, Y);
return;}

 if(ID==3) {gfx_Sprite(Dirt, X, Y);
return;}

 if(ID==4) {gfx_Sprite(Cobblestone, X, Y);
return;}

 if(ID==5) {gfx_Sprite(Oak, X, Y);
return;}

 if(ID==6) {gfx_Sprite(Sapling, X, Y);
return;}

 if(ID==7) {gfx_Sprite(Bedrock, X, Y);
return;}

 if(ID==8) {gfx_Sprite(Water, X, Y);
return;}

 if(ID==10) {gfx_Sprite(Lava, X, Y);
return;}

 if(ID==12) {gfx_Sprite(Sand, X, Y);
return;}

 if(ID==13) {gfx_Sprite(Gravel, X, Y);
return;}

 if(ID==14) {gfx_Sprite(Gold, X, Y);
return;}

 if(ID==15) {gfx_Sprite(Iron, X, Y);
return;}

 if(ID==16) {gfx_Sprite(Coal, X, Y);
return;}

 if(ID==17) {gfx_Sprite(Log, X, Y);
return;}

 if(ID==18) {gfx_Sprite(Leaves, X, Y);
return;}

 if(ID==19) {gfx_Sprite(Sponge, X, Y);
return;}

 if(ID==20) {gfx_Sprite(Glass, X, Y);
return;}

}