#include "player.h"
#include "disparo.h"
#include "inimigoAtira.h"
#include "inimigoDesvia.h"

//constutor recebe ponteiro para o game para poder executar algumas funcoes
Player::Player(Game *g)
{
    game = g;
}

//movimentação do personagem e acoes para disparar, fechar e salvar
void Player::keyPressEvent(QKeyEvent *event)
{
    try {
        //move para a esquerda enquanto o player não esta no limite esquerdo da tela
        if (event->key() == Qt::Key_Left)
        {
            if(pos().x() > 0)
                setPos(x()-15, y());
        }
        //move para a direita enquanto o player não esta no limite direito da tela
        else if (event->key() == Qt::Key_Right)
        {
            if(pos().x()+100 < 840)
                setPos(x()+15, y());
        }
        //se pressiona espaco, cria novo objeto disparo e o adiciona a cena
        else if(event->key() == Qt::Key_Space)
        {
            //criando a arma
            Disparo *tiro = new Disparo(game);
            tiro->setPos(x()+20,y());
            scene()->addItem(tiro);
        }
        //se pressiona esc, deleta cena e view e sai do jogo
        else if(event->key() == Qt::Key_Escape)
        {
            game->cena->deleteLater();
            game->view->deleteLater();
            game->sair();
        }
        //se pressiona S, salva jogo durante a execucao
        else if(event->key() == Qt::Key_S)
        {
            game->salvar();
        }
        //caso nenhuma das teclas acima seja pressionada, gera excecao de tecla invalida
        else
        {
            throw QString("Tecla inválida");
        }
    }
    catch (QString mensagem)
    {
        if(aux == 1)
        {
            return;
        }
        teclaInvalida = new QGraphicsTextItem(mensagem);
        teclaInvalida->setPos(0, 500);
        teclaInvalida->setFont(QFont("times", 10));
        game->cena->addItem(teclaInvalida);
        aux = 1;
        timer = new QTimer(this);
        timer->start(1000);
        connect(timer, SIGNAL(timeout()), this, SLOT(remove()));
    }
}

//spawn envia inimigo que eh destruido com disparo
void Player::spawn()
{
    Inimigo *enemy= new InimigoAtira(game);
    scene()->addItem(enemy);
}

//spawn2 envia inimigo2 que nao pode ser destruido por disparo, e sim desviado
//caso o player encoste nesse inimigo, perde-se uma vida
void Player::spawn2()
{
    Inimigo *enemy2 = new InimigoDesvia(game);
    scene()->addItem(enemy2);
}

void Player::remove()
{
    game->cena->removeItem(teclaInvalida);
    timer->stop();
    aux = 0;
}
