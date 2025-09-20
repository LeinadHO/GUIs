/* BIBLIOTECAS */
#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include "AUX_WaitEventTimeoutCount.h"
#include "MultiplosCliques.h"

/* CONSTANTES */
#define LARGURA 1280
#define ALTURA 720

/* DECLARAÇÃO DAS FUNÇÕES */
int Inicializador(SDL_Window** win, SDL_Renderer** ren);
int Executador(SDL_Window* win, SDL_Renderer* ren);
int Finalizador(SDL_Window** win, SDL_Renderer** ren);

/* PONTO DE ENTRADA DO PROGRAMA*/
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

/* FUNÇÃO DE INICIALIZAÇÃO DO PROGRAMA E SEUS SUBSISTEMAS */
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

/* FUNÇÃO DE EXECUÇÃO DO PROGRAMA (CONSTRUÇÃO DO FRAME, CAPTURA DE EVENTOS, ETC) */
int Executador(SDL_Window* win, SDL_Renderer* ren) {

    // Declaração das variáveis que serão utilizadas durante a execução
    SDL_Event evt;
    int isevt, mouseX_atual, mouseY_atual;
    int continuar_execucao = 1;
    int n = 0;
    MultiplosCliques mc = {0};
    MultiplosCliques_Iniciar(&mc, 250);

    // Loop de execução do programa
    while (continuar_execucao) {
        // Construção e exibição do frame
        SDL_SetRenderDrawColor(ren, 0xFF, 0xFF, 0xFF, 0x00);
        SDL_RenderClear(ren);
        SDL_RenderPresent(ren);
        
        // Loop de captura de eventos
        Uint32 espera = mc.espera;
        isevt = AUX_WaitEventTimeoutCount(&evt, &espera);
        if (isevt) { // Trata os eventos esperados pelo programa
            // Eventos de finalização do loop de captura de eventos
            if (evt.type == SDL_QUIT) {
                continuar_execucao = 0;
            }

            // Eventos de clique do mouse
            else if (evt.type == SDL_MOUSEBUTTONDOWN && evt.button.button == SDL_BUTTON_LEFT) {
                SDL_GetMouseState(&mouseX_atual, &mouseY_atual);
                MultiplosCliques_ContarClique(&mc, mouseX_atual, mouseY_atual, 250);
            }

            // Eventos de movimento do mouse
            else if (evt.type == SDL_MOUSEMOTION) {
                SDL_GetMouseState(&mouseX_atual, &mouseY_atual);
                int houve_movimento = MultiplosCliques_VerificarMovimento(&mc, mouseX_atual, mouseY_atual);
                if (houve_movimento) {
                    n = MultiplosCliques_QtdCliques(&mc);
                    if (n > 0) {
                        MultiplosCliques_ReiniciarContagem(&mc);
                        MultiplosCliques_EmitirEventos(n);
                        printf("Saiu porque mexeu\n");
                    }
                }
            }

            // Eventos de usuário (Múltiplos Cliques)
            else if (evt.type == SDL_USEREVENT) {
                printf("Você clicou %d vez(es) seguidas!\n", n);
                continuar_execucao = 0;
            }
        }
        else { // Emite o evento quando o tempo de timeout foi atingido
            n = MultiplosCliques_QtdCliques(&mc);
            if (n > 0) {
                MultiplosCliques_ReiniciarContagem(&mc);
                MultiplosCliques_EmitirEventos(n);
                printf("Saiu porque acabou o tempo\n");
            }  
        }
    }
}

/* FUNÇÃO DE ENCERRAMENTO DO PROGRAMA E DESALOCAÇÃO DOS COMPONENTES USADOS DURANTE A EXECUÇÃO */
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
