#ifndef PONTOS_H
#define PONTOS_H

#include <QGraphicsTextItem>

class Pontos: public QGraphicsTextItem
{
protected:
    int pontos;

public:
    Pontos(QGraphicsItem *parent=0, int p=0);
    int getPontos();
    void ganhaPonto();
    void perdePonto();
};

#endif // PONTOS_H
