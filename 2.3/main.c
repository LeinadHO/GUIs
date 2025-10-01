#include <stdio.h>
#include <SDL2/SDL.h>

#define LARGURA 600
#define ALTURA 300

int InicializaPrograma(SDL_Window** win, SDL_Renderer** ren);
void ExecutaPrograma(SDL_Window* win, SDL_Renderer* ren);
int FinalizaPrograma(SDL_Window** win, SDL_Renderer** ren);

int main(int argc, char* argv[]) {

    // Chamada à função InicializaPrograma() e o tratamento dos possíveis retornos associados
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    int sucessoInicio;
    sucessoInicio = InicializaPrograma(&window, &renderer);
    switch (sucessoInicio) {
        case 1:
            printf("SDL inicializado corretamente!\n");
            break;
        case -1:
            printf("Erro ao inicializar os subsistemas do SDL!\n");
            return sucessoInicio;
        case -2:
            printf("Erro ao criar a janela!\n");
            return sucessoInicio;
        case -3:
            printf("Erro ao criar o renderizador!\n");
            return sucessoInicio;
    }
    return 0;

    // Chamada à função 'ExecutaPrograma()'
    ExecutaPrograma(window, renderer);

    // Chamada à função 'FinalizaPrograma()' e o tratamento dos possíveis retornos associados
    int sucessoFim;
    sucessoFim = FinalizaPrograma(&window, &renderer);
    switch (sucessoFim) {
        case 1:
            printf("SDL finalizado com sucesso!\n");
            break;
        case -1:
            printf("Janela passada é inválida!\n");
            return sucessoFim;
        case -2:
            printf("Renderizador passado é inválido!\n");
            return sucessoFim;
    }
    return 0;
}

int InicializaPrograma(SDL_Window** win, SDL_Renderer** ren) {

    // Inicialização dos subsistemas do SDL
    int iniciou;
    iniciou = SDL_Init(SDL_INIT_EVERYTHING);
    if (iniciou < 0) {
        return -1;
    }

    // Criação da janela
    *win = SDL_CreateWindow("2.1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, LARGURA, ALTURA, 0);
    if (*win == NULL) {
        return -2;
    }

    // Criação do renderizador
    *ren = SDL_CreateRenderer(*win, -1, 0);
    if (*ren == NULL) {
        return -3;
    }

    // Retorna 1 caso não haja nenhuma falha durante a inicialização
    return 1;
}

void ExecutaPrograma(SDL_Window* win, SDL_Renderer* ren) {
    printf("TUDO FUNCIONANDO!\n");
}

int FinalizaPrograma(SDL_Window** win, SDL_Renderer** ren) {

    // Verifica se os componentes foram passados corretamente
    if (*win == NULL) {
        return -1;
    }
    if(*ren == NULL) {
        return -2;
    }

    // Desaloca os espaços de memória usados pelos componentes e finaliza os subsistemas utilizados
    SDL_DestroyRenderer(*ren);
    SDL_DestroyWindow(*win);
    SDL_Quit();
    return 1; 
}



