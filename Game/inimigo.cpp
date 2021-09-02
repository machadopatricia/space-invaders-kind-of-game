#include "inimigo.h"
#include "game.h"

Inimigo::Inimigo()
{
    //posição inicial do inimigo
    int random_number = rand() % 700;
    setPos(random_number, 0);

}

void Inimigo::move()
{

}
