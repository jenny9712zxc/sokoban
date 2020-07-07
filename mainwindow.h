#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPixmap>
#include <QKeyEvent>
#include <QWidget>
#include <QLCDNumber>
#include <QMenuBar>
#include <QDebug>
#include <QDialog>

#include "player.h"
#include "box.h"
#include "hole.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void create_wall(int,int);
    void create_box(int,int);
    void create_hole(int,int);
    void keyPressEvent(QKeyEvent*);
    bool moveCheck(int ,int);
    void moveBoxOnMap(int ,int ,int ,int);
    void start(void);


    player *Player;

public slots:
    //void add();
    void restart(void);
    void changeLevel(void);
    void finish(void);
    void trigerMenu(QAction* act);

signals:
    //void add_signal();
    void finish_signal(void);

private:
    Ui::MainWindow *ui;
    int level1[9][9]= { {0, 0, 0, 0, 5, 5, 5, 5, 5},
                        {0, 0, 0, 0, 5, 0, 0, -1, 5},
                        {5, 5, 5, 0, 5, 2, 2, 0, 5},
                        {5, 1, 5, 0, 5, 0, 2, 0, 5},
                        {5, 1, 5, 5, 5, 0, 5, 5, 5},
                        {5, 1, 0, 0, 0, 0, 5, 5, 0},
                        {5, 0, 0, 5, 0, 0, 0, 5, 0},
                        {5, 5, 5, 5, 0, 0, 0, 5, 0},
                        {0, 0, 0, 5, 5, 5, 5, 5, 0}
                        };
    int level2[9][9]= { {0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 5, 5, 5, 5, 0, 0},
                        {0, 5, 5, 5, 0, -1, 5, 0, 0},
                        {0, 5, 0, 0, 2, 0, 5, 0, 0},
                        {5, 5, 0, 5, 0, 5, 5, 5, 0},
                        {5, 0, 0, 5, 0, 5, 1, 5, 0},
                        {5, 0, 5, 0, 0, 2, 1, 5, 0},
                        {5, 0, 2, 0, 0, 0, 1, 5, 0},
                        {5, 5, 5, 5, 5, 5, 5, 5, 0}
                        };
    int level3[9][9]= { {0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 5, 5, 5, 5, 5, 5, 5, 0},
                        {0, 5, 0, -1, 1, 1, 1, 5, 0},
                        {0, 5, 0, 0, 0, 5, 5, 5, 5},
                        {5, 5, 5, 2, 0, 0, 0, 0, 5},
                        {5, 0, 0, 0, 5, 2, 5, 0, 5},
                        {5, 0, 2, 0, 5, 0, 0, 0, 5},
                        {5, 0, 0, 0, 5, 5, 5, 5, 5},
                        {5, 5, 5, 5, 5, 0, 0, 0, 0}
                        };
    //-1:player init position
    //5:wall
    //2:box
    //1:hole
    int initMap[9][9];
    int map[9][9];
    int boxN=-1;
    int holeN=-1;
    int currentLevel=1;
    QLabel *wall[100];
    int wallN=-1;//wallN < 100

    //int num;
    int step;
    hole* Hole[10];
    box* Box[10];//boxN < 10

    QMenuBar* menubar;
    QMenu *menuGame,*menuLevel;
    //QAction* action;
    QDialog *dialog;

};

#endif // MAINWINDOW_H
