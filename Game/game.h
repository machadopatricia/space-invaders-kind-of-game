#ifndef GAME_H
#define GAME_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include <QObject>
#include <QTimer>
#include <QPainter>
#include "pontos.h"
#include <QVector>

class Game : public QMainWindow
{

private:
    Q_OBJECT

    //singleton: atributo estatico para poder criar um soh objeto da classe
    static Game *instancia;
    //privatizando construtor, construtor de copia e operador igual
    Game(QWidget *parent = nullptr);
    Game(const Game &);
    Game operator=(Game);

    int intervalo = 2000;
    int pontosIn = 0;
    int perdasIn = 0;
    QPainter *pintor;
    QColor cor;
    QString nomeArquivo;
    QVector<int> v;

public:
    static Game* getInstancia();
    int getIntervalo();
    void setIntervalo(int n);
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void novoJogo();
    void gameOver();
    void displayGameOver();
    void salvar();
    void incrementa(int i);

    QTimer *timer;
    QTimer *timer2;
    QGraphicsScene *cena;
    QGraphicsView *view;
    Pontos *pontos;
    Pontos *perdas;

public slots:
    void sair();
    void abrir();
    void localSalvar();
};
#endif // GAME_H
