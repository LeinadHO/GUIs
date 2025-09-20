#include "MultiplosCliques.h"
#include <SDL2/SDL.h>

// Define o tempo de espera até o timeout
// Caso não seja passado nenhum valor, o padrão será 250
void MultiplosCliques_Iniciar(MultiplosCliques* mc, Uint32 tempo){
    mc->qtd_cliques = 0;
    mc->espera = tempo;
}

void MultiplosCliques_MudarEspera(MultiplosCliques* mc, Uint32 tempo){
    mc->espera = tempo;
}

// Adiciona 1 ao contador sempre que um clique é registrado dentro do tempo limite
// Se for o primeiro clique, também registra a posição do mouse no momento da captura
void MultiplosCliques_ContarClique(MultiplosCliques* mc, int mouseX_atual, int mouseY_atual, int tempo) {
    if (mc->qtd_cliques == 0) {
        mc->mouseX_inicial = mouseX_atual;
        mc->mouseY_inicial = mouseY_atual;
    }
    mc->qtd_cliques += 1;
    mc->espera = tempo;
}

int MultiplosCliques_QtdCliques(MultiplosCliques* mc) {
    return mc->qtd_cliques;
}

void MultiplosCliques_ReiniciarContagem(MultiplosCliques* mc) {
    mc->qtd_cliques = 0;
}

void MultiplosCliques_EmitirEventos(int n) {
    SDL_Event evt_usuario;
    evt_usuario.type = SDL_USEREVENT;
    evt_usuario.user.code = n;
    SDL_PushEvent(&evt_usuario);
}

// Retorna 1 se o movimento do mouse for maior que 5 pixels
// Retorna 0 caso contrário
int MultiplosCliques_VerificarMovimento(MultiplosCliques* mc, int x, int y) {
    return (abs(x - mc->mouseX_inicial) >= 5 || abs(y - mc->mouseY_inicial) >= 5);
}