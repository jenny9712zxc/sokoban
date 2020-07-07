#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QLabel>



class player : public QObject
{
    Q_OBJECT

public:
    player(int,int);
    QLabel *Label;
    void move(int,int);
    void restart(void);

    int posX,posY;
    int init_posX,init_posY;

signals:

public slots:

};

#endif // PLAYER_H
