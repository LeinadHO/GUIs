/* Bibliotecas */
#include <stdio.h>
#include <SDL2/SDL.h>

/* Constantes */
#define LARGURA 1280
#define ALTURA 720

/* Funções */
int inicializador(SDL_Window* win, SDL_Renderer* ren);
int executador();
int finalizador();

/* Entrypoint do programa */
int main(int argc, char* argv[]) {
    // Chamada a função inicializador() e o tratamento de possíveis erros relacionados
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    int sucesso;
    sucesso = inicializador(window, renderer);
    switch (sucesso) {
        case -1:
            printf("Erro ao inicializar os subsistemas da biblioteca!");
            return -1;
        case -2:
            printf("Erro ao criar a janela!");
            return -2;
        case -3:
            printf("Erro ao criar o renderizador!");
            return -3;
        default:
            break;
    }

    // Execução
    // Finalização
    return 0;
}

/* Função de inicialização do programa */
int inicializador(SDL_Window* win, SDL_Renderer* ren) {

    // Inicialização dos subsistemas do SDL
    int iniciou;
    iniciou = SDL_Init(SDL_INIT_EVERYTHING);
    if (iniciou < 0) {
        return -1;
    }

    // Criação da janela
    win = SDL_CreateWindow("2.1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, LARGURA, ALTURA, 0);
    if (win == NULL) {
        return -2;
    }

    // Criação do renderizador
    ren = SDL_CreateRenderer(win, -1, 0);
    if (ren == NULL) {
        return -3;
    }

    // Retorna 0 caso não haja nenhuma falha durante a inicialização
    return 0;
}
