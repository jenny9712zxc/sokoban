#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    for(int i=0; i<9; i++)
        for(int j=0; j<9; j++)
            initMap[i][j]=level1[i][j];

    //set init map
    for(int i=0; i<9; i++)
        for(int j=0; j<9; j++)
        {

            map[i][j]=initMap[i][j];
            if(map[i][j] == -1)
            {
                map[i][j]++;
                Player=new player(j,i);
            }
            if(map[i][j] == 5)
               create_wall(j,i);

            if(map[i][j] == 1)
                create_hole(j,i);
            if(map[i][j] == 2)
               create_box(j,i);


        }



    //set player label
    Player->Label= new QLabel(this);
    Player->Label->setGeometry(50*(Player->posX+1),50*(Player->posY+1),50,50);
    QPixmap pix_playerLabel(":/res/player.jpg");
    Player->Label->setPixmap(pix_playerLabel);
    Player->Label->setScaledContents(true);
    Player->Label->raise();



    //connect(ui->addButton, SIGNAL(clicked()), this, SLOT(add()));
    //connect(this, SIGNAL(add_signal()), this, SLOT(add()));
    //num=0;
    setFocusPolicy(Qt::StrongFocus);

    connect(ui->restartButton, SIGNAL(clicked()), this, SLOT(restart()));
    connect(ui->levelButton, SIGNAL(clicked()), this, SLOT(changeLevel()));
    connect(this, SIGNAL(finish_signal()), this, SLOT(finish()));
    step=0;

    //menu
    menubar =new QMenuBar(this);
    menuGame = new QMenu("Game");
    menuLevel= new QMenu("Level");
    //action = new QAction("New",this);

    menubar->addMenu(menuGame);
    menuGame->addAction("Start");
    menuGame->addAction("Quit");
    //menuGame->addAction(action);
    menubar->addMenu(menuLevel);
    menuLevel->addAction("Level1");
    menuLevel->addAction("Level2");
    menuLevel->addAction("Level3");
    menubar->setGeometry(0,0,this->width(),23);
    connect(menubar,SIGNAL(triggered(QAction*)),this,SLOT(trigerMenu(QAction*)));

    ui->lcdNumber->setPalette(Qt::blue);
    ui->lcdNumber->display(currentLevel);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::create_wall(int a,int b)
{
    wallN ++;
    int x,y;
    x=50*(a+1);
    y=50*(b+1);
    wall[wallN] = new QLabel(this);
    if(wall[wallN] == NULL) printf("fail\n");
    wall[wallN]->setGeometry(x,y,50,50);
    QPixmap pix_wall(":/res/wall.jpg");
    wall[wallN]->setPixmap(pix_wall);
    wall[wallN]->setScaledContents(true);
    wall[wallN]->show();

}

void MainWindow::create_box(int a,int b)
{
    boxN++;
    Box[boxN]=new box(a,b);

    int x,y;
    x=50*(a+1);
    y=50*(b+1);
    Box[boxN]->Label = new QLabel(this);
    Box[boxN]->Label->setGeometry(x,y,50,50);
    QPixmap pix_box(":/res/box.png");
    Box[boxN]->Label->setPixmap(pix_box);
    Box[boxN]->Label->setScaledContents(true);

    Box[boxN]->Label->raise();
    Box[boxN]->Label->show();


}

void MainWindow::create_hole(int a,int b)
{
    holeN++;
    Hole[holeN]=new hole(a,b);
    int x,y;
    x=50*(a+1);
    y=50*(b+1);
    Hole[holeN]->Label = new QLabel(this);
    Hole[holeN]->Label->setGeometry(x,y,50,50);
    QPixmap pix_hole(":/res/hole.jpg");
    Hole[holeN]->Label->setPixmap(pix_hole);
    Hole[holeN]->Label->setScaledContents(true);

    Hole[holeN]->Label->show();
    //pix_hole.fill(Qt::transparent);

}

void MainWindow::keyPressEvent(QKeyEvent* event)
{


    if(event->key() == Qt::Key_P) {

        printf("map player(%d,%d)\n",Player->posX,Player->posY);
        for(int i=0; i<9; i++)
            for(int j=0; j<9; j++)
             {   printf("%d ",map[i][j]);
                if(j==8) printf("\n");
            }
     }
/*
    if(event->key() == Qt::Key_A) {
            //emit add_signal();
            add();
     }
*/
    // move up
    if (event->key() == Qt::Key_Up)//  ||  event->key() == Qt::Key_W)
    {
        //posY=posY-50;
        if(moveCheck(0,-1))
        {
            Player->move(0,-1);
            step++;
            ui->stepLabel->setNum(step);
            //ui->lcdNumber->display(step);
        }


    }


    // move down
    if (event->key() == Qt::Key_Down)
    {
        //posY=posY+50;
        if(moveCheck(0,1))
        {
            Player->move(0,1);
            step++;
            ui->stepLabel->setNum(step);
            //ui->lcdNumber->display(step);
        }
    }

    // move right
    if (event->key() == Qt::Key_Right)
    {
        //posX=posX+50;
        if(moveCheck(1,0))
        {
            Player->move(1,0);
            step++;
            ui->stepLabel->setNum(step);
            //ui->lcdNumber->display(step);
        }
    }

    // move left
    if (event->key() == Qt::Key_Left)
    {
       //posX=posX-50;
        if(moveCheck(-1,0))
        {
            Player->move(-1,0);
            step++;
            ui->stepLabel->setNum(step);
            //ui->lcdNumber->display(step);
        }
    }

}
bool MainWindow::moveCheck(int a,int b)//move direction
{
    int x,y;//next posi2tion for player
    x=Player->posX+a;
    y=Player->posY+b;

    //check range
    if(x>8 || x<0 || y>8 || y<0)
        return false;
    //player
    if(map[y][x] < 5)
    {
        if(map[y][x] == 2 || map[y][x] == 3)//push box
        {
            //printf("push box___1\n");
            if( (x+a>-1 || x+a<9 || y+b>-1 || y+b<9) && (map[y+b][x+a] == 0 || map[y+b][x+a] == 1) )
            {
                //printf("push box___2\n");
                if(boxN>9)      printf("-----error: boxN>9\n");
                //printf("x=%d,  y=%d\n",x,y);
                for(int i=0; i<=boxN; i++)
                    if((x==Box[i]->posX) && (y==Box[i]->posY))
                    {
                        Box[i]->move(a,b);
                        //Box[boxN]->Label->raise();

                    }
                moveBoxOnMap(x,y,a,b);//set map
                return true;
            }

            else
                return false;
        }
        else
            return true;
    }

     else
        return false;

}
/*
void MainWindow::add() {
    num++;
    ui->label->setNum(num);
}
*/
void MainWindow::moveBoxOnMap(int x,int y,int a,int b)
{


    map[y][x]-=2;
    map[y+b][x+a]+=2;

    //printf("%d,%d  ->  %d,%d\n" , x, y, x+a, y+b);

    if(map[y+b][x+a] == 3)
    {
        for(int i=0; i<=holeN ;i++)
        {
            if((Hole[i]->posX == x+a) && (Hole[i]->posY == y+b))
                Hole[i]->Label->setVisible (false);
                //Hole[i]->Label->lower();
            //printf("lower\n");
        }

        int c=-1;
        for(int i=0; i<9 ;i++)
        {
            for(int j=0; j<9 ;j++)
                if(map[i][j] == 3)
                    c++;
        }
        if(c == holeN)
        {
            printf("c=%d\n",c);
            emit finish_signal();
        }

    }

    if(map[y][x] == 1)
    {
        for(int i=0; i<=holeN ;i++)
        {
            if((Hole[i]->posX == x) && (Hole[i]->posY == y))
                Hole[i]->Label->setVisible (true);
                //Hole[i]->Label->raise();//will on the top of player

            //printf("raise hole(%d,%d)\n",Hole[i]->posX,Hole[i]->posY);
        }
    }

    return ;
}

void MainWindow::restart(void)
{
    Player->restart();

    for(int i=0; i<=boxN; i++)
    {
        Box[i]->restart();
        Hole[i]->Label->setVisible (true);
    }

    for(int i=0; i<9; i++)
        for(int j=0; j<9; j++)
        {
            map[i][j]=initMap[i][j];
            if(map[i][j] == -1)
                map[i][j]++;
        }
    Player->Label->raise();

    step=0;
    ui->stepLabel->setNum(step);
    ui->lcdNumber->display(currentLevel);
    return;
}

void MainWindow::start(void)
{
    printf("MainWindow::start\n");
    boxN=-1;
    holeN=-1;
    wallN=-1;


    //set init map
    for(int i=0; i<9; i++)
        for(int j=0; j<9; j++)
        {

            map[i][j]=initMap[i][j];
            if(map[i][j] == -1)
            {
                map[i][j]++;
                Player->init_posX=j;
                Player->init_posY=i;
                Player->restart();
            }
            if(map[i][j] == 5)
               create_wall(j,i);

            if(map[i][j] == 1)
                create_hole(j,i);
            if(map[i][j] == 2)
               create_box(j,i);


        }
    printf("boxN:%d\t holeN:%d\t wallN:%d\t\n",boxN,holeN,wallN);
    Player->Label->raise();
    return;
}

void MainWindow::changeLevel(void)
{
    if(currentLevel == 1)
    {
        currentLevel = 2;

        for(int i=0; i<9; i++)
            for(int j=0; j<9; j++)
                initMap[i][j]=level2[i][j];
    }
    else if(currentLevel == 2)
    {
        currentLevel = 3;

        for(int i=0; i<9; i++)
            for(int j=0; j<9; j++)
                initMap[i][j]=level3[i][j];
    }
    else//currentLevel == 3
    {
        currentLevel = 1;

        for(int i=0; i<9; i++)
            for(int j=0; j<9; j++)
                initMap[i][j]=level1[i][j];
    }


    for (int i=0; i<= wallN; i++)
    {
        if(wall[i] != NULL)
            delete wall[i];
    }

    for (int i=0; i<= boxN; i++)
    {
        delete Box[i]->Label;
        delete Hole[i]->Label;
    }

    MainWindow::start();

     ui->msglabel->setText(" ");

     step=0;
     ui->stepLabel->setNum(step);
     ui->lcdNumber->display(currentLevel);

     return;
}

void MainWindow:: finish(void)
{
    ui->msglabel->setText("finish\nplease click \nchange level");

}


void MainWindow::trigerMenu(QAction* act)
{
    QString  str=act->text();
    qDebug()<<"action:"<<str;

    if(act->text() == "Level1")
    {
        currentLevel=3;
        changeLevel();//3 -> 1
    }

    if(act->text() == "Level2")
    {
        currentLevel=1;
        changeLevel();//1 -> 2
    }

    if(act->text() == "Level3")
    {
        currentLevel=2;
        changeLevel();//2 -> 3
    }

    if(act->text() == "Start")
    {
        currentLevel=3;
        changeLevel();//3 -> 1
    }

    if(act->text() == "Quit")
    {
        QApplication::exit();
        /*
        dialog = new QDialog();
        dialog->setAttribute(Qt::WA_DeleteOnClose, true);
        dialog->show();
        */
    }
}
