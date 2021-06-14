# pula_pirata- Marco, Diovanna, Felipe Bolfe
ATENÇÃO!!!! Organização do projeto alterada, todos os arquivos necessários para a compilação devem estar dentro da pasta raiz do clone.
Ex:

<pre>Pasta criada-> 
      projetoClonado->
                 Coisas do projeto
                 (commons e dependencias externas)
		 pula_pirata (código fonte)</pre>


<h3> REGRAS: </h3>

Existem dois jogadores, o AZUL e o ROSA (com as espadas das respectivas cores)

Cada jogador possui 2 pontos de vida (canto inferior da tela)

O Barril possui 16 buracos, 8 deles serão, aleatoriamente, escolhidos para causar dano ao pirata

Cada jogador escolhe um buraco por turno, ao escolher um buraco que causa dano ao pirata o jogador que escolheu perde um ponto de vida

O jogador que perder todos os pontos de vida primeiro perde

O turno de um jogador só acaba depois de ele escolher um buraco

Quando um dos jogadores perder, aparecerá uma mensagem na tela, dizendo que o outro jogador venceu, o jogo pode ser recomeçado pressionando ENTER

OBS:
-Uma luz vermelha será acesa no rosto do pirata ao selecionar um buraco que o causará dano, e também, o contador de vidas do jogador
que selecionou esse buraco será decrescido

-Jogo está travado para esperar, pelo menos, 16ms para desenhar o próximo quadro, podendo alcançar o máximo de 60FPS (quadros por segundo)




<h3>COMANDOS: </h3>

ENTER inicia o jogo (Reinicia caso esteja na tela de fim de jogo)

F1 até F3 altera entre as câmeras

ESPAÇO coloca em uma câmera que gira pela mesa

ARROW_UP e ARROW_DOWN altera o zoom

P altera entre as projeções

WASD movimenta as câmeras separadamente

MOUSE controla a direção da camera

ARROW_LEFT escolhe o próximo buraco a esquerda

ARROW_RIGHT escolhe o próximo buraco a direita

KEY_E coloca a espada no buraco selecionado (o buraco selecionado é aquele que a espada está na frente)
