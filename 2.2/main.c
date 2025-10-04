#include <stdio.h>
#include <SDL2/SDL.h>
#include "AUX_WaitEventTimeoutCount.h"

#define LARGURA_JANELA 600
#define ALTURA_JANELA 300

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
    *win = SDL_CreateWindow("2.2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, LARGURA_JANELA, ALTURA_JANELA, 0);
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

    /* VARIÁVEIS DA EXECUÇÃO */
    int posIncialRectX = (LARGURA_JANELA/2)-40;
    int posInicialRectY = (ALTURA_JANELA/2)-50;
    SDL_Rect retangulo = {posIncialRectX, posInicialRectY, 70, 70};
    SDL_Event evt;
    Uint32 tempo = 16;
    int continuarExecucao = 1;
    int isevt;
    int mouseX, mouseY;
    int difCliqueX, difCliqueY;
    int mousePressionadoNoRetangulo = 0;
    int retanguloMovendo = 0;
    
    /* LOOP DE EXECUÇÃO */
    while (continuarExecucao) {

        /* CONSTRUÇÃO DO FRAME */
        SDL_SetRenderDrawColor(ren, 255, 255, 255, 0);
        SDL_RenderClear(ren);

        SDL_SetRenderDrawColor(ren, 255, 0, 255, 0);
        SDL_RenderFillRect(ren, &retangulo);
        SDL_RenderPresent(ren);

        /* CAPTURA DE EVENTOS */
        isevt = AUX_WaitEventTimeoutCount(&evt, &tempo);
        if (isevt) {
            if (evt.type == SDL_QUIT) { // Fechamento do programa
                continuarExecucao = 0;
            }

            if (evt.type == SDL_MOUSEBUTTONDOWN) { // Verifica se o botão do mouse foi pressionado em cima do retângulo
                SDL_GetMouseState(&mouseX, &mouseY);
                SDL_Point mousePos = {mouseX, mouseY};
                if (SDL_PointInRect(&mousePos, &retangulo)) {
                    mousePressionadoNoRetangulo = 1;
                    difCliqueX = mouseX - retangulo.x;
                    difCliqueY = mouseY - retangulo.y;
                }
            }

            if (evt.type == SDL_MOUSEMOTION) { // Verifica se o mouse foi movido após o botão do mouse ser pressionado com o cursor em cima do retângulo
                if (mousePressionadoNoRetangulo) {
                    retanguloMovendo = 1;
                    SDL_GetMouseState(&mouseX, &mouseY);
                    retangulo.x = mouseX - difCliqueX;
                    retangulo.y = mouseY - difCliqueY;
                    printf("Movendo o retângulo!\n");
                }
            }

            if (evt.type == SDL_MOUSEBUTTONUP) { // Verifica se o botão do mouse foi liberado após o botão do mouse ser pressionado com o cursor em cima do retângulo
                if (mousePressionadoNoRetangulo) {
                    if (!retanguloMovendo) {
                        printf("O retângulo foi clicado!\n");
                    } else {
                        printf("O retângulo foi movido!\n");
                        retanguloMovendo = 0;
                    }
                    mousePressionadoNoRetangulo = 0;
                }
            }

            if (evt.type == SDL_KEYDOWN && evt.key.keysym.sym == SDLK_ESCAPE) { // Verifica se a tecla "Esc" foi pressionada durante o arrasto do retângulo
                if (retanguloMovendo) {
                    mousePressionadoNoRetangulo = 0;
                    retanguloMovendo = 0;
                    retangulo.x = posIncialRectX;
                    retangulo.y = posInicialRectY;
                    printf("Ações canceladas!\n");
                }
            }
        } else {
            tempo = 16;
        }
    }
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



