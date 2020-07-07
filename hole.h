#ifndef HOLE_H
#define HOLE_H

#include <QObject>
#include <QLabel>

class hole : public QObject
{
    Q_OBJECT

public:
    hole(int, int);

    int posX,posY;
    QLabel *Label;
};

#endif // HOLE_H
