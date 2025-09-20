# Ideia do programa
A cor de fundo da janela é trocada toda vez que um conjunto de cliques rápidos e no mesmo ponto é registrado.

# Como o programa funciona?
1. Quando o usuário clica com o botão esquerdo do mouse pela primeira vez, a biblioteca **MultiplosCliques** registra esse e todos os próximos cliques que forem capturados dentro do tempo-limite (timeout) e sem que o mouse tenha se movido desde o primeiro clique;
   
2. Caso alguma das condições anteriores não sejam cumpridas (clique dentro do tempo de timeout e sem mover o mouse) a biblioteca emite um *evento de usuário* para o programa. O evento possui como código a quantidade de cliques sequenciais registrados;
 
3. Ao receber o evento, o programa utiliza o código (qtd. de cliques) para calcular, um a cada evento recebido, o valor de vermelho (R), verde(G) e azul(B) a serem usados para definir a cor da janela.
   *  A fórmula para definir o valor é: **numero_aleatorio x qtd_cliques) mod 256**;
   *  *numero_aleatorio* é um valor inteiro escolhido aleatoriamente pela função **rand()**.

