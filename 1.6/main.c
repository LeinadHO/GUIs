#include <SDL2/SDL.h>
#include <stdio.h>
#include "AUX_WaitEventTimeoutCount.h"
#include "colidiu.h"

#define ALTURA 100
#define LARGURA 200

int main (int argc, char* args[])
{
    /* INICIALIZAÇÃO */

    // Inicialização dos subsistemas
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        printf("Erro ao iniciar os subsistemas!");
        return 1;
    }

    // Criação da janela
    SDL_Window* win = SDL_CreateWindow("Movendo um Retângulo", 
                        SDL_WINDOWPOS_UNDEFINED, 
                        SDL_WINDOWPOS_UNDEFINED,
                        LARGURA, ALTURA, SDL_WINDOW_SHOWN
                      );
    if (win == NULL) {
        printf("Erro ao iniciar janela!");
        return 1;
    }

    // Criação do renderizador
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);
    if (ren == NULL) {
        printf("Erro ao iniciar renderizador!");
        return 1;
    }

    /* EXECUÇÃO */

    // Declaração das variáveis
    SDL_Rect retangulo_tempo = {40,20, 10,10};
    SDL_Rect retangulo_teclado = {60,30, 10,10};
    SDL_Rect retangulo_mouse = {80,40, 10,10};
    SDL_Rect linha_chegada = {LARGURA-30,0, 30,ALTURA};
    int movimentoX = 2;
    Uint32 espera = 16;
    int retangulo_tempo_chegou = 0;
    int retangulo_teclado_chegou = 0;
    int retangulo_mouse_chegou = 0;

    // Loop de captura de eventos
    while (1) 
    {   
        // Redesenho do cenário
        SDL_SetRenderDrawColor(ren, 0x00, 0xBF, 0xFF, 0x00);
        SDL_RenderClear(ren);
        SDL_SetRenderDrawColor(ren, 0x72, 0x2F, 0x37, 0x00);
        SDL_RenderFillRect(ren, &linha_chegada);
        SDL_SetRenderDrawColor(ren, 0xFF, 0x00, 0x00, 0x00);
        SDL_RenderFillRect(ren, &retangulo_tempo);
        SDL_SetRenderDrawColor(ren, 0x00, 0xFF, 0x00, 0x00);
        SDL_RenderFillRect(ren, &retangulo_teclado);
        SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0xFF, 0x00);
        SDL_RenderFillRect(ren, &retangulo_mouse);
        SDL_RenderPresent(ren);

        // Captura de eventos
        SDL_Event evt;
        int isevt = AUX_WaitEventTimeoutCount(&evt, &espera);
        if (isevt) // Evento
        {
            // Captura eventos de finalização do programa
            if (evt.type == SDL_QUIT) { 
                SDL_DestroyRenderer(ren);
                SDL_DestroyWindow(win);
                SDL_Quit();
                break;
            }

            // Atualiza a posição do retângulo do teclado se ele ainda não tiver atingido a linha de chegada
            if (evt.type == SDL_KEYDOWN) {
                if (retangulo_teclado_chegou == 0) {
                    switch (evt.key.keysym.sym) {
                        case SDLK_LEFT:
                            if (retangulo_teclado.x < 0) {
                                retangulo_teclado.x -= 2;  
                            }
                        case SDLK_RIGHT:
                            retangulo_teclado.x += 2;  
                            break;         
                    }
                }
            }
            
        }

        else // Timeout - Reseta o tempo de delay
        {   
            espera = 16;
            if (retangulo_tempo_chegou == 0) { // Só permite a movimentação se ainda não tiver chegado na linha de chegada
                movimentoX = 2;
                retangulo_tempo.x += movimentoX;
            }
        }

        // Atualiza a posição do retângulo do mouse, se ele ainda não tiver atingido a linha de chegada
        if (retangulo_mouse_chegou == 0) {
            int mouseX, mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);
            retangulo_mouse.x = mouseX - retangulo_mouse.w / 2;
            if (retangulo_mouse.x < 0) {
                retangulo_mouse.x = 0;
            }
            if (retangulo_mouse.x > LARGURA - 10) {
                retangulo_mouse.x = LARGURA - 10;
            }
        }

        // Verifica se os retângulos atingiram a linha de chegada
        retangulo_teclado_chegou = RetanguloColidiu(&retangulo_teclado, &linha_chegada);
        retangulo_tempo_chegou = RetanguloColidiu(&retangulo_tempo, &linha_chegada);
        retangulo_mouse_chegou = RetanguloColidiu(&retangulo_mouse, &linha_chegada);
    }
    return 0;
}