#ifndef PLAYER_H
#define PLAYER_H

#include <QKeyEvent>
#include <QObject>
#include <QGraphicsRectItem>
#include "game.h"

class Player : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
    Game *game;
    QTimer *timer;
    int aux = 0;
public:
    Player(Game *g);
    void keyPressEvent(QKeyEvent *event);
    QGraphicsTextItem *teclaInvalida;

public slots:
    void spawn();
    void spawn2();
    void remove();
};

#endif // PLAYER_H
