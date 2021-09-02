#include "inimigoAtira.h"
#include "game.h"
#include <QTimer>
#include <QGraphicsScene>

InimigoAtira::InimigoAtira(Game *g): Inimigo()
{
    game = g;
    //desenhando o inimigo
    setRect(0,0,100,100);

    //conexao
    QTimer *timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));

    timer->start(40);
}

void InimigoAtira::move()
{
    //movimento do inimigo
    setPos(x(),y()+5);
    //deletando o inimigo quando sair da tela
    if(pos().y() > 600 )
    {
        //diminuindo a pontuaçao
        game->perdas->perdePonto();
        if(game->perdas->getPontos() == 0)
        {
            game->gameOver();
        }
        scene()->removeItem(this);
        delete this;
    }
}
