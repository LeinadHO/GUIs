/* Bibliotecas */
#include <stdio.h>
#include <SDL2/SDL.h>

/* Constantes */
#define LARGURA 1280
#define ALTURA 720

/* Funções */
int inicializador(SDL_Window** win, SDL_Renderer** ren);
int executador();
int finalizador(SDL_Window** win, SDL_Renderer** ren);

/* Entry point do programa */
int main(int argc, char* argv[]) {
    // Chamada à função inicializador() e o tratamento dos possíveis retornos associados
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    int sucesso;
    sucesso = inicializador(&window, &renderer);
    switch (sucesso) {
        case 1:
            printf("SDL inicializado corretamente!\n");
            break;
        case -1:
            printf("Erro ao inicializar os subsistemas do SDL!\n");
            return sucesso;
        case -2:
            printf("Erro ao criar a janela!\n");
            return sucesso;
        case -3:
            printf("Erro ao criar o renderizador!\n");
            return sucesso;
    }

    // Chamada à função 'executador()'

    // Chamada à função 'finalizador()' e o tratamento dos possíveis retornos associados
    sucesso = finalizador(&window, &renderer);
    switch (sucesso) {
        case 1:
            printf("SDL finalizado com sucesso!\n");
            break;
        case -1:
            printf("Janela passada é inválida!\n");
            return sucesso;
        case -2:
            printf("Renderizador passado é inválido!\n");
            return sucesso;
    }
    return 0;
}

/* Função de inicialização do programa */
int inicializador(SDL_Window** win, SDL_Renderer** ren) {
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

/* Função de finalização do programa */
int finalizador(SDL_Window** win, SDL_Renderer** ren) {
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
