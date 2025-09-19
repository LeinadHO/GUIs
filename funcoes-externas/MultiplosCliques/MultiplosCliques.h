#ifndef MULTIPLOSCLIQUES_H
#define MULTIPLOSCLIQUES_H

#include <SDL2/SDL.h>

// Struct que representa uma ação de múltiplos cliques
typedef struct {
    int qtd_cliques;
} MultiplosCliques;

// Função que atualiza a quantidade de cliques dados, se recebidos dentro do limite de tempo definido
void MultiplosCliques_Contador(MultiplosCliques* mc);

// Função que retona a quantidade de cliques dados no período definido
int MultiplosCliques_Quantidade(MultiplosCliques* mc);

// Função que reseta o contador de cliques
void MultiplosCliques_Reiniciador(MultiplosCliques* mc);

// Função que emite o evento relacionado aos múltiplos cliques
void MultiplosCliques_EmissorEventos(int n);

#endif
