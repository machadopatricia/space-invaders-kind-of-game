#ifndef DISPARO_H
#define DISPARO_H

#include "game.h"
#include <QGraphicsRectItem>
#include <QObject>

class Disparo: public QObject, public QGraphicsRectItem
{
    Q_OBJECT
    Game *game;

public:
    Disparo(Game *g);

public slots:
    void move();
};

#endif // DISPARO_H


