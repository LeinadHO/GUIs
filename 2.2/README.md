# Drag, Click or Cancel

## Funcionamento do programa
O programa consiste em um retângulo, inicialmente no centro da janela, que possui diferentes interações dependendo do que for feito. É possível:
* Clicar no retângulo
* Mover o retângulo
* Cancelar o movimento do retângulo

### Clicando no retângulo
- O evento mais simples: Ao pressionar e soltar o botão (esquerdo ou direito) do mouse com o cursor na área de exibição do retângulo **sem mover o cursor**, o programa indica que houve um **CLIQUE** no retângulo.

### Movendo o retângulo
- Ao pressionar o botão (esquerdo ou direito) do mouse com o cursor na área de exibição do retângulo e **movê-lo**, o programa atualizará a posição do retângulo baseado na posição em que o cursor se encontra enquanto permanece com o botão pressionado;
- O movimento é calculado para que o retângulo seja recriado a partir da posição de onde houve o clique, a fim de evitar que o seu canto superior esquerdo se "teletransporte" para a posição do mouse;
- Soltar o botão do mouse após o movimento faz com que o retângulo pare de se mover, e faz com que o programa indique que houve um **ARRASTO** no retângulo.

### Cancelando o movimento do retângulo
- Enquanto o retângulo está em estado de movimento, é possível pressionar a tecla "*ESC*" do teclado para cancelar a movimentação;
- Na prática o que isso faz é:
  1. Resetar todas as flags que indicam que alguma ação/evento está ocorrendo;
  2. Definir a posição do retângulo como a mesma de quando o programa foi iniciado.
- O programa indica que houve um **CANCELAMENTO** nas ações sobre o retângulo.

