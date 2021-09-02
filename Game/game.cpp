#include "game.h"
#include "player.h"
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QShortcut>
#include <QAbstractScrollArea>
#include <QPainter>
#include <QGraphicsRectItem>
#include <QKeyEvent>
#include <QFileDialog>
#include <QTextStream>

//atributo estatico - singleton
Game* Game::instancia = NULL;

//construtor cria janela inicial com opcoes que enviam sinais para slots
Game::Game(QWidget *parent) : QMainWindow(parent)
{
    //posicao inicial da janela
    QMainWindow::setGeometry(400,200,800,600);

    //adicionando barra de  menu e suas opcoes (acoes)
    QMenuBar *barra = new QMenuBar(this);

    QMenu *menuArquivo = new QMenu("Arquivo", this);
    barra->addMenu(menuArquivo);

    QAction *acaoAbrir = new QAction("Abrir", this);
    QAction *acaoSalvar = new QAction("Local", this);
    QAction *acaoSair = new QAction("Sair", this);

    menuArquivo->addAction(acaoAbrir);
    menuArquivo->addAction(acaoSalvar);
    menuArquivo->addAction(acaoSair);

    //adicionando atalhos de teclado para as opcoes
    acaoAbrir->setShortcut(Qt::CTRL + Qt::Key_O);
    acaoSalvar->setShortcut(Qt::CTRL + Qt::Key_S);
    acaoSair->setShortcut(Qt::Key_Q);

    //enviando sinais das acoes para os seus respectivos slots
    connect(acaoAbrir, SIGNAL(triggered(bool)), this, SLOT(abrir()));
    connect(acaoSalvar, SIGNAL(triggered(bool)), this, SLOT(localSalvar()));
    connect(acaoSair, SIGNAL(triggered(bool)), this, SLOT(sair()));
}

//metodo estatico que garante criacao unica do objeto
Game* Game::getInstancia()
{
    if (instancia == NULL)
        instancia = new Game();
    return instancia;
}

int Game::getIntervalo()
{
    return intervalo;
}

void Game::setIntervalo(int n)
{
    intervalo = n;
}

//cria janela e vista do jogo, adiciona player, pontuacoes e chama slot que envia inimigos num intervalo de tempo
void Game::novoJogo()
{
    QMainWindow::hide();

    //criando janela para o jogo e cena
    cena = new QGraphicsScene(this);
    view = new QGraphicsView(cena);
    view->setScene(cena);
    cena->setSceneRect(0,0,790,590);

    //impedindo que a janela dê scrool quando atira
    QAbstractScrollArea *scrool = new QAbstractScrollArea(this);
    scrool->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrool->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setFixedSize(800,600);
    view->setGeometry(400,200,800,600);

    //criando um personagem
    Player *ator = new Player(this);
    ator->QGraphicsRectItem::setRect(0,0,50,50);
    //colocando o player no centro da cena
    ator->setPos(400,550);
    //focando no personagem
    ator->setFlag(QGraphicsItem::ItemIsFocusable);
    ator->setFocus();
    //colocando o personagem na cena
    cena->addItem(ator);

    //texto de pontos e perdas
    QGraphicsTextItem *textoPontos = new QGraphicsTextItem("Pontos:");
    QGraphicsTextItem *textoPerdas = new QGraphicsTextItem("Vidas:");
    textoPontos->setPos(0,0);
    textoPerdas->setPos(0,50);
    textoPontos->setFont(QFont("times", 16));
    textoPerdas->setFont(QFont("times", 16));
    cena->addItem(textoPontos);
    cena->addItem(textoPerdas);

    //texto mostrando atalhos para salvar e sair
    QGraphicsTextItem *textoSalvar = new QGraphicsTextItem("\"S\" - Salvar");
    QGraphicsTextItem *textoSair = new QGraphicsTextItem("\"Esc\" - Sair");
    textoSalvar->setPos(680,0);
    textoSair->setPos(680,20);
    textoSalvar->setFont(QFont("times", 14));
    textoSair->setFont(QFont("times", 14));
    cena->addItem(textoSalvar);
    cena->addItem(textoSair);

    //criando a pontuacao
    //pontosIn armazena os pontos de um jogo salvo, se for maior do que zero,
    //significa que existe um jogo salvo, entao altera a pontuacao (pontos e vidas) de inicio
    if(pontosIn > 0) {
        pontos = new Pontos(0,pontosIn);
        perdas = new Pontos(0,perdasIn);
    } else {
        pontos = new Pontos();
        //player comeca com limite de 3 vidas
        int vidas = 3;
        perdas = new Pontos(0,vidas);
    }
    perdas->setPos(perdas->x(),perdas->y()+50);
    cena->addItem(pontos);
    cena->addItem(perdas);

    //spawnando inimigos
    timer = new QTimer();
    QObject::connect(timer, SIGNAL(timeout()), ator, SLOT(spawn()));
    timer->start(intervalo);

    timer2 = new QTimer();
    QObject::connect(timer2, SIGNAL(timeout()), ator, SLOT(spawn2()));
    timer2->start(intervalo + 8000);

    //criando posiçoes para o vetor incrementa
    v.push_back(0);
    v.push_back(0);

    view->show();
}

//desenho da janela inicial - sobreescrita do paint event
void Game::paintEvent(QPaintEvent *event)
{
    //desenhando tela inicial
    pintor = new QPainter(this);
    cor = QColor(Qt::black);
    QBrush baldinho(cor);
    pintor->setBrush(baldinho);
    pintor->drawRoundedRect(20,40,760,540,10,10);

    //desenhando "botao" novo jogo
    cor = QColor(Qt::white);
    baldinho = QBrush(cor);
    pintor->setBrush(baldinho);
    pintor->setOpacity(0.8);
    pintor->drawRoundedRect(300,250,200,100,5,5);
    cor = QColor(Qt::black);
    pintor->setPen(cor);
    pintor->setFont(QFont("Times", 20));
    pintor->setOpacity(1);
    pintor->drawText(325,310,"NOVO JOGO");

    //desenhando aviso para selecionar local de armazenamento (salvar como)
    cor = QColor(Qt::white);
    pintor->setPen(cor);
    pintor->setFont(QFont("Times", 14));
    pintor->setOpacity(1);
    pintor->drawText(30, 510, "1. Elimine inimigos");
    pintor->drawText(30, 530, "2. Desvie dos menores");
    pintor->drawText(30, 550, "3. Não desperdice tiros");
    pintor->setPen(Qt::red);
    pintor->drawText(30,570,"Para salvar: \"Arquivo -> Local\" - local onde será salvo o seu progresso durante o jogo");

    delete(pintor);
}

//sobreescrita do mouse event para clicar em novo jogo
void Game::mousePressEvent(QMouseEvent *event)
{
    //se o cursor estiver dentro dos limites da posicao do botao, eh possivel clicar
    if (event->button() == Qt::LeftButton &&
        event->x() > 300 && event->x() < 500 &&
        event->y() > 250 && event->y() < 350)
    {
        novoJogo();
    }
}

//para de enviar inimigos e de contar perdas e chama metodo q mostra tela do game over
void Game::gameOver()
{
    timer->stop();
    timer2->stop();
    cena->removeItem(perdas);
    displayGameOver();
}

//mostra tela de game over
void Game::displayGameOver()
{
    //escurece a tela
    QGraphicsRectItem *painel = new QGraphicsRectItem(0,0,800,600);
    QBrush baldinho;
    baldinho.setStyle(Qt::SolidPattern);
    baldinho.setColor(Qt::red);
    painel->setBrush(baldinho);
    painel->setOpacity(0.5);
    cena->addItem(painel);

    //desenha retangulo no meio da tela
    QGraphicsRectItem *painel2 = new QGraphicsRectItem(200,200,400,200);
    QBrush baldinho2;
    QPen caneta2;
    caneta2.setColor(Qt::lightGray);
    baldinho2.setStyle(Qt::SolidPattern);
    baldinho2.setColor(Qt::lightGray);
    painel2->setBrush(baldinho2);
    painel2->setOpacity(0.9);
    cena->addItem(painel2);

    //escreve dentro do retangulo
    QString mensagem = "    Game Over \n\n\n\n (ESC) para sair";
    QGraphicsTextItem *texto = new QGraphicsTextItem(mensagem);
    texto->setPos(315,230);
    texto->setFont(QFont("times", 16));
    cena->addItem(texto);


    QGraphicsTextItem *texto2 = new QGraphicsTextItem("Você eliminou:       inimigos");
    texto2->setPos(310,260);
    cena->addItem(texto2);
    QGraphicsTextItem *textoI = new QGraphicsTextItem(QString::number(v[0]));
    textoI->setPos(415,260);
    cena->addItem(textoI);
    QGraphicsTextItem *texto3 = new QGraphicsTextItem("Você desviou de:        inimigos");
    texto3->setPos(300,285);
    cena->addItem(texto3);
    QGraphicsTextItem *textoJ = new QGraphicsTextItem(QString::number(v[1]));
    textoJ->setPos(415,285);
    cena->addItem(textoJ);
}

//aqui sera definido o nome e local do jogo a ser salvo
void Game::localSalvar()
{
    nomeArquivo = QFileDialog::getSaveFileName(this, "Salvar como:");
}

//usa local ja definido anteriormente para salvar durante o jogo
//salva pontuacao, perdas e timer
void Game::salvar()
{
    QFile arquivo(nomeArquivo);
    arquivo.open(QIODevice::WriteOnly);
    QTextStream saida(&arquivo);

    saida << pontos->getPontos() << " " << perdas->getPontos() <<  " " << intervalo;

    arquivo.close();
}
//incrementa os valores do vetor quando os inimigos saem da tela ou sao eliminados
void Game::incrementa(int i)
{
    v[i] += 1;
}

//arquivo a ser aberto vai conter pontos, perdas e timer (definido pelo atributo 'intervalo')
void Game::abrir()
{
    QString nomeArquivoIn = QFileDialog::getOpenFileName(this, "Escolha o arquivo");
    QFile arquivo(nomeArquivoIn);
    arquivo.open(QIODevice::ReadOnly);
    QTextStream entrada(&arquivo);

    entrada >> pontosIn >> perdasIn >> intervalo;

    arquivo.close();
}

//fecha janela
void Game::sair()
{
    close();
    this->deleteLater();
}
