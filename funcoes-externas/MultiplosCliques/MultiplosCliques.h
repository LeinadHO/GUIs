#ifndef MULTIPLOSCLIQUES_H
#define MULTIPLOSCLIQUES_H

#include <SDL2/SDL.h>

// Struct que representa uma ação de múltiplos cliques
typedef struct {
    int qtd_cliques;
    int mouseX_inicial, mouseY_inicial;
    Uint32 espera;
} MultiplosCliques;

// Função que inicializa algumas variáveis do evento
void MultiplosCliques_Iniciar(MultiplosCliques* mc, Uint32 tempo);

// Função que modifica o tempo de espera até emitir um timeout
void MultiplosCliques_MudarEspera(MultiplosCliques* mc, Uint32 tempo);

// Função que atualiza a quantidade de cliques dados, se recebidos dentro do limite de tempo definido
void MultiplosCliques_ContarClique(MultiplosCliques* mc, int mouseX_atual, int mouseY_atual, int tempo);

// Função que retona a quantidade de cliques dados no período definido
int MultiplosCliques_QtdCliques(MultiplosCliques* mc);

// Função que reseta o contador de cliques
void MultiplosCliques_ReiniciarContagem(MultiplosCliques* mc);

// Função que emite o evento relacionado aos múltiplos cliques
void MultiplosCliques_EmitirEventos(int n);

// Função que verifica se o movimento foi dentro do limite de tolerância
int MultiplosCliques_VerificarMovimento(MultiplosCliques* mc, int x, int y);

#endif
