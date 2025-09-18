/* Bibliotecas */
#include <stdio.h>
#include <SDL2/SDL.h>
#include "../funcoes-externas/MultiplosCliques/MultiplosCliques.h"

/* Constantes */
#define LARGURA 1280
#define ALTURA 720

/* Funções */
int Inicializador(SDL_Window** win, SDL_Renderer** ren);
int Executador(SDL_Window* win, SDL_Renderer* ren);
int Finalizador(SDL_Window** win, SDL_Renderer** ren);

/* Entry point do programa */
int main(int argc, char* argv[]) {
    // Chamada à função Inicializador() e o tratamento dos possíveis retornos associados
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    int sucesso;
    sucesso = Inicializador(&window, &renderer);
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

    // Chamada à função 'Executador()'
    Executador(window, renderer);

    // Chamada à função 'Finalizador()' e o tratamento dos possíveis retornos associados
    sucesso = Finalizador(&window, &renderer);
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
int Inicializador(SDL_Window** win, SDL_Renderer** ren) {
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

/* Função de execução do programa */
int Executador(SDL_Window* win, SDL_Renderer* ren) {

    // Declaração das variáveis que serão utilizadas durante a execução
    SDL_Event evt;
    int isevt;
    int continuar_execucao = 1;
    int n = 0;
    Uint32 espera = 250;
    MultiplosCliques mc = {0};

    // Loop de execução do programa
    while (continuar_execucao) {
        // Construção e exibição do frame
        SDL_SetRenderDrawColor(ren, 0xFF, 0xFF, 0xFF, 0x00);
        SDL_RenderClear(ren);
        SDL_RenderPresent(ren);
        
        // Captura de eventos
        isevt = SDL_WaitEventTimeout(&evt, espera);
        // Evento aconteceu
        if (isevt) {
            // Eventos de finalização do loop de captura de eventos
            if (evt.type == SDL_QUIT) {
                continuar_execucao = 0;
            }

            // Eventos de clique do mouse
            if (evt.type == SDL_MOUSEBUTTONDOWN && evt.button.button == SDL_BUTTON_LEFT) {
                MultiplosCliques_Contador(&mc);
            }

            // Eventos de usuário
            if (evt.type == SDL_USEREVENT) {
                printf("Você clicou %d vez(es) seguidas!\n", n);
                continuar_execucao = 0;
            }
        }
        // Não teve evento - Timeout
        else {
            n = MultiplosCliques_Quantidade(&mc);
            MultiplosCliques_Reiniciador(&mc);
            if (n > 0) {
                SDL_Event evt_usuario;
                evt_usuario.type = SDL_USEREVENT;
                evt_usuario.user.code = n;
                SDL_PushEvent(&evt_usuario);
            }
        }
    }
}

/* Função de finalização do programa */
int Finalizador(SDL_Window** win, SDL_Renderer** ren) {
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
