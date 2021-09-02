#include <QApplication>
#include "game.h"

int main(int argc, char *argv[])
{
    QApplication a (argc, argv);

    //game eh um singleton, entao chama metodo estatico q cria a unica instancia da classe
    Game::getInstancia()->show();

    return a.exec();
}

