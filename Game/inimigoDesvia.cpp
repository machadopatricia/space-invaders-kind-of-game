#include "inimigoDesvia.h"
#include "player.h"
#include <QTimer>

InimigoDesvia::InimigoDesvia(Game *g): Inimigo()
{
    game = g;
    //desenhando o inimigo 2
    setRect(0,0,50,50);
    setBrush(Qt::black);
    //conexao com o spawner do inimigo
    QTimer *timer2 = new QTimer();
    connect(timer2, SIGNAL(timeout()), this, SLOT(move()));

    timer2->start(40);
}

void InimigoDesvia::move()
{
    //movimento do inimigo
    setPos(x(),y()+3);
    //deletando o inimigo quando sair da tela
    if(pos().y() > 600 )
    {
        game->incrementa(1);
        scene()->removeItem(this);
        delete this;
    }
    //reduzindo pontuaçao se encostar nesse inimigo
    QList<QGraphicsItem*> itensColisao = collidingItems();
    for(int i = 0, n = itensColisao.size(); i<n;++i)
    {
        if(typeid(*(itensColisao[i]))==typeid(Player))
        {
            //deleta o inimigo e reduz vida
            game->perdas->perdePonto();
            if(game->perdas->getPontos() == 0)
            {
                game->gameOver();
            }
            scene()->removeItem(this);
            delete this;
        }
    }
}
