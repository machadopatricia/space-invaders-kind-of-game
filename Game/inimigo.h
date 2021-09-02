#ifndef INIMIGOS_H
#define INIMIGOS_H

#include "game.h"
#include <QGraphicsRectItem>
#include <QObject>
#include <QVector>

class Inimigo: public QObject, public QGraphicsRectItem// Classe mãe
{
    Q_OBJECT
public:
    Inimigo();

public slots:
    virtual void move() = 0;
};

#endif // INIMIGOS_H
