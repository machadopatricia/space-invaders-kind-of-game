#ifndef INIMIGODESVIA_H
#define INIMIGODESVIA_H

#include "game.h"
#include "inimigo.h"
#include <QGraphicsRectItem>
#include <QObject>

class InimigoDesvia: public Inimigo //Herança de Inimigos
{
    Q_OBJECT
    Game *game;
public:
    InimigoDesvia(Game *g);
public slots:
    void move();
};

#endif
