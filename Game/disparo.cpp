#include "disparo.h"
#include "inimigoAtira.h"
#include "inimigoDesvia.h"
#include <QTimer>

Disparo::Disparo(Game *g)
{
    game = g;

    //desenhando o tiro
    setRect(0,0,10,15);

    //conexao
    QTimer *timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));

    timer->start(40);
}

void Disparo::move()
{
    //COLISAO COM INIMIGO
    QList<QGraphicsItem*> itensColisao = collidingItems();
    for(int i = 0, n = itensColisao.size(); i<n;++i)
    {
        if(typeid(*(itensColisao[i]))==typeid(InimigoAtira))
        {
            //pontuando
            game->pontos->ganhaPonto();

            //aumentando dificuldade a cada 10 pontos
            if(game->pontos->getPontos() % 10 == 0)
            {
                game->timer->setInterval(game->getIntervalo() - 150);
                game->setIntervalo(game->getIntervalo() - 150);
            }

            //deleta o inimigo e o tiro
            scene()->removeItem(itensColisao[i]);
            scene()->removeItem(this);
            game->incrementa(0);
            delete itensColisao[i];
            delete this;
            return;
        }
        else if(typeid(*(itensColisao[i]))==typeid(InimigoDesvia))
        {

            //deleta o tiro
            scene()->removeItem(this);
            delete this;
            return;
        }
    }

    //atirando
    setPos(x(),y()-20);
     //deletando o tiro quando sair da tela
    if(pos().y() < 0)
    {
        scene()->removeItem(this);
        game->pontos->perdePonto();
        delete this;
    }
}
