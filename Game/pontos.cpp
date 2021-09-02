#include "pontos.h"
#include <QFont>

Pontos::Pontos(QGraphicsItem *parent, int p): QGraphicsTextItem(parent)
{
    pontos = p;

    //imprimindo na tela
    setPlainText(QString::number(pontos));
    setDefaultTextColor(Qt::black);
    setFont(QFont("times", 16));
    setPos(75,0);
}

int Pontos::getPontos()
{
    return pontos;
}

void Pontos::ganhaPonto()
{
    pontos++;
    //atualizando a pontuaçao na tela
    setPlainText(QString::number(pontos));
}

void Pontos::perdePonto()
{
    pontos--;
    //atualizando a pontuaçao na tela
    setPlainText(QString::number(pontos));
}
