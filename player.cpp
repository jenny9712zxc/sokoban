#include "player.h"
//#include "mainwindow.h"



player::player(int x,int y)
{
    posX=x;
    posY=y;
    init_posX=x;
    init_posY=y;
}

void player::move(int x,int y)
{
    posX+=x;
    posY+=y;
    Label->setGeometry(50*(posX+1),50*(posY+1),50,50);
}

void player::restart(void)
{
    //printf("player::restart\n");
    posX=init_posX;
    posY=init_posY;
    Label->setGeometry(50*(posX+1),50*(posY+1),50,50);
}
