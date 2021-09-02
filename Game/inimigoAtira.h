#ifndef INIMIGOATIRA_H
#define INIMIGOATIRA_H

#include "game.h"
#include "inimigo.h"
#include <QGraphicsRectItem>
#include <QObject>

class InimigoAtira: public Inimigo //Herança de inimigos
{
    Q_OBJECT
    Game *game;
public:
    InimigoAtira(Game *g);
public slots:
    void move();
};

#endif // INIMIGO_H
