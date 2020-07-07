#ifndef BOX_H
#define BOX_H

#include <QObject>
#include <QLabel>

class box : public QObject
{
    Q_OBJECT

public:
    box(int,int);
    QLabel *Label;
    void move(int,int);
    void restart(void);

    int posX,posY;
    int init_posX,init_posY;

signals:

public slots:

};


#endif // BOX_H
