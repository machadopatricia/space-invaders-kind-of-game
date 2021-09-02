# space-invaders-kind-of-game
A shooting game with the style of the classic Space Invaders. Created with QtCreator.

Descrição da aplicação: A aplicação desenvolvida se trata de um jogo no estilo Space Invaders, em que um Player (jogador, que é o quadrado na parte inferior da tela) recebe inimigos (dois tipos: um quadrado maior e outro menor) na tela. Esses inimigos devem ser destruídos por meio de disparos, que são acionados ao pressionar espaço. O jogo aumenta de dificuldade conforme a pontuação aumenta. O jogador perde pontos se encosta no quadrado menor preto e se não elimina um quadrado maior. O jogo acaba quando a quantidade de vidas chega a zero.

Funcionalidades exigidas e suas implementações:
    • Desenhar objetos na janela: A sobreescrita do método paintEvent é utilizada na classe Game para desenhar a janela inicial. Os outros desenhos e textos são criados através da QGraphicsRectItem QGraphicsTextItem, respectivamente.

    • Permitir ao usuário inserir e remover objetos: Nesta aplicação, a inserção e remoção de objetos é feita de forma dinâmica. Por essa razão, não existem opções para o usuário inserir ou remover objetos.

    • Permitir ao usuário manipular os objetos de alguma forma, necessariamente com o mouse: A sobreescrita do método mousePressEvent é utilizada para clicar no botão "NOVO JOGO", dentro da classe Game.

    • Permitir ao usuário salvar o que estiver na janela em um arquivo, e abrir um arquivo salvo anteriormente: As classes QFile, QFileDialog e QTextStream são utilizadas na classe Game para abrir e salvar arquivos. Existe uma opção no menu inicial para selecionar o diretório que será utilizado para salvar o jogo durante a execução (pressionando S). Para abrir um jogo salvo anteriormente, também é possível selecionar essa opção no menu inicial.

    • Tratar exceções, alertando o usuário quando alguma ação inválida é realizada: Esta funcionalidade está dentro da classe Player. Ela é acionada quando o usuário digita alguma tecla inválida (tecla que não tem função no jogo), gerando um alerta que aparece temporariamente na tela (durante o jogo).

São criadas e utilizadas classes, objetos, construtores, getters e setters. A herança é utilizada na classe Inimigo, que também é uma classe abstrata. São sobreescritos métodos da biblioteca do Qt e também o método virtual puro "move()" da classe Inimigo, usando o polimorfismo dinâmico. A sobrecarga do operador igual é feita durante a criação do singleton Game. A estrutura da STL é um QVector, que é utilizado para armazenar o número de inimigos desviados e eliminados.
