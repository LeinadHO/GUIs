#include "MultiplosCliques.h"
#include <SDL2/SDL.h>

void MultiplosCliques_Contador(MultiplosCliques* mc) {
    mc->qtd_cliques += 1;
}

int MultiplosCliques_Quantidade(MultiplosCliques* mc) {
    return mc->qtd_cliques;
}

void MultiplosCliques_Reiniciador(MultiplosCliques* mc) {
    mc->qtd_cliques = 0;
}

void MultiplosCliques_EmissorEventos(int n) {
    SDL_Event evt_usuario;
    evt_usuario.type = SDL_USEREVENT;
    evt_usuario.user.code = n;
    SDL_PushEvent(&evt_usuario);
}