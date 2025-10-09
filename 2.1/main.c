/* BIBLIOTECAS */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include "AUX_WaitEventTimeoutCount.h"

/* CONSTANTES */
#define LARGURA 1280
#define ALTURA 720

/* DECLARAÇÃO DAS FUNÇÕES */
void InicializaPrograma(SDL_Window** win, SDL_Renderer** ren);
void ExecutaPrograma(SDL_Window* win, SDL_Renderer* ren);
void FinalizaPrograma(SDL_Window** win, SDL_Renderer** ren);

int main(int argc, char* argv[]) {

    // Inicialização do programa
    srand(time(NULL));
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    InicializaPrograma(&window, &renderer);

    // Execução do programa
    ExecutaPrograma(window, renderer);

    // Finalização do programa
    FinalizaPrograma(&window, &renderer);
    return 0;
}

/* FUNÇÃO DE INICIALIZAÇÃO DO SDL E SEUS SUBSISTEMAS */
void InicializaPrograma(SDL_Window** win, SDL_Renderer** ren) {

    // Inicialização dos subsistemas do SDL
    SDL_Init(SDL_INIT_EVERYTHING);

    // Criação da janela
    *win = SDL_CreateWindow("2.1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, LARGURA, ALTURA, 0);

    // Criação do renderizador
    *ren = SDL_CreateRenderer(*win, -1, 0);
}

/* FUNÇÃO DE EXECUÇÃO DO PROGRAMA (CONSTRUÇÃO DO FRAME, CAPTURA DE EVENTOS, ETC) */
void ExecutaPrograma(SDL_Window* win, SDL_Renderer* ren) {

    // Declaração das variáveis que serão utilizadas durante a execução
    SDL_Event evt;
    Uint32 delay = 250;
    int qtd_cliques = 0;
    int contando = 0;
    int isevt;
    int continuar_execucao = 1;
    int r = 255, g = 255, b = 255;
    int proximo_tom = 0;

    // Loop de execução do programa
    while (continuar_execucao) {

        // Construção e exibição do frame
        SDL_SetRenderDrawColor(ren, r, g, b, 0x00);
        SDL_RenderClear(ren);
        SDL_RenderPresent(ren);
        
        // Loop de captura de eventos
        isevt = AUX_WaitEventTimeoutCount(&evt, &delay);
        if (isevt) { 

            // Eventos de finalização do loop de captura de eventos
            if (evt.type == SDL_QUIT) {
                continuar_execucao = 0;
            }

            // Começa a contagem de cliques
            if (evt.type == SDL_MOUSEBUTTONDOWN) {
                if (!contando) {
                    contando = 1;
                }
                qtd_cliques++;
                delay = 250;      
            }

            // Emite evento se a contagem já tiver começado
            if (evt.type == SDL_MOUSEMOTION && contando) {
                SDL_Event evt_usuario;
                evt_usuario.type = SDL_USEREVENT;
                evt_usuario.user.code = qtd_cliques;
                SDL_PushEvent(&evt_usuario);
                contando = 0;
                qtd_cliques = 0;
            }

            // Muda a cor da janela baseado no número de cliques registrados
            if (evt.type == SDL_USEREVENT) {
                int numero_cliques = evt.user.code;
                switch (proximo_tom) {
                    case 0:
                        r = abs((rand() * numero_cliques) % 256);
                        break;
                    case 1:
                        g = abs((rand() * numero_cliques) % 256);
                        break;
                    case 2:
                        b = abs((rand() * numero_cliques) % 256);
                        break;
                }
                printf("RGB: %d %d %d\n", r, g, b);
                proximo_tom = (proximo_tom + 1) % 3;
            }
        } else { // Timeout - Emite evento se a contagem já tiver começado
            if (contando) {
                SDL_Event evt_usuario;
                evt_usuario.type = SDL_USEREVENT;
                evt_usuario.user.code = qtd_cliques;
                SDL_PushEvent(&evt_usuario);
                contando = 0;
                qtd_cliques = 0;
            }
            delay = 250;
        }
    }
}

/* FUNÇÃO DE ENCERRAMENTO DO SDL E DESALOCAÇÃO DOS COMPONENTES USADOS DURANTE A EXECUÇÃO */
void FinalizaPrograma(SDL_Window** win, SDL_Renderer** ren) {

    // Desaloca os espaços de memória usados pelos componentes e finaliza os subsistemas utilizados
    SDL_DestroyRenderer(*ren);
    SDL_DestroyWindow(*win);
    SDL_Quit();
}
