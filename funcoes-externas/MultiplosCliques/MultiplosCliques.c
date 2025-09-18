#include "MultiplosCliques.h"

void MultiplosCliques_Contador(MultiplosCliques* mc) {
    mc->qtd_cliques += 1;
}

int MultiplosCliques_Quantidade(MultiplosCliques* mc) {
    return mc->qtd_cliques;
}

void MultiplosCliques_Reiniciador(MultiplosCliques* mc) {
    mc->qtd_cliques = 0;
}