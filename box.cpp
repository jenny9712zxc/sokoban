#include "box.h"

box::box(int x,int y)
{
    posX=x;
    posY=y;
    init_posX=x;
    init_posY=y;
}

void box::move(int x,int y)
{
    printf("move(%d,%d)\n",x,y);
    posX+=x;
    posY+=y;
    Label->setGeometry(50*(posX+1),50*(posY+1),50,50);
}

void box::restart(void)
{
    posX=init_posX;
    posY=init_posY;
    Label->setGeometry(50*(posX+1),50*(posY+1),50,50);
}
