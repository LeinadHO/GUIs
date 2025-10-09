# Ideia do programa
A cor de fundo da janela é trocada toda vez que um conjunto de cliques rápidos e no mesmo ponto é registrado.

# Como o programa funciona?
1. Quando o usuário clica na janela com o botão do mouse pela primeira vez, o programa começa a incrementar um contador de cliques;
   
2. Para que os cliques continuem a ser computados, eles devem ser emitidos dentro de um intervalo de 250ms entre cada, e não pode haver movimento do mouse durante os cliques;

3. Caso haja um intervalo maior que 250ms entre cliques ou caso o mouse se mexa depois de iniciada a contagem de cliques, o programa para de contar os cliques e emite um evento de usuário. O código desse evento emitido é a quantidade de cliques registrados dentro das condições estabelecidas;
 
4. Ao receber o evento, o programa utiliza a quantidade de cliques contados para atualizar a cor de fundo da janela. Os valores de Vermelho (R), Verde (G) e Azul (B) são atualizados nessa ordem e um de cada vez em cada emissão de evento.
   *  A fórmula para definir o valor é: **(numero_aleatorio x qtd_cliques) mod 256**;
   *  *numero_aleatorio* é um valor inteiro escolhido aleatoriamente pela função **rand()**.

