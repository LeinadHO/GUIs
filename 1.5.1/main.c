#include <SDL2/SDL.h>
#include <stdio.h>
#include "../1.5.2/AUX_WaitEventTimeoutCount.h"

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
    int movimentoX = 2;
    int movimentoY = 2;
    Uint32 espera = 16;

    // Loop de captura de eventos
    while (1) 
    {   
        // Redesenho
        SDL_SetRenderDrawColor(ren, 0xFF, 0xFF, 0xFF, 0x00);
        SDL_RenderClear(ren);
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

            // Atualiza a posição do retângulo do teclado
            if (evt.type == SDL_KEYDOWN) {
                switch (evt.key.keysym.sym) {
                    case SDLK_UP:
                        if (retangulo_teclado.y > 0) {
                            retangulo_teclado.y -= 2;
                        }
                        break;
                    case SDLK_DOWN:
                        if (retangulo_teclado.y < ALTURA-10) {
                            retangulo_teclado.y += 2;
                        }
                        break;
                    case SDLK_LEFT:
                        if (retangulo_teclado.x > 0) {
                            retangulo_teclado.x -= 2;
                        }
                        break;
                    case SDLK_RIGHT:
                        if (retangulo_teclado.x < LARGURA-10) {
                            retangulo_teclado.x += 2;  
                        }
                        break;         
                }
            }
        }

        else // Timeout - Atualiza a posição do retângulo do tempo
        {   
            espera = 16;
            // Troca a direção de movimento do retângulo do tempo se tiver atingido um limite da janela
            switch (retangulo_tempo.x) {
                case LARGURA-10:
                    movimentoX = -2;
                    break;
                case 0:
                    movimentoX = 2;
                    break;
            }
            switch (retangulo_tempo.y) {
                case ALTURA-10:
                    movimentoY = -2;
                    break;
                case 0:
                    movimentoY = 2;
                    break;
            }
            retangulo_tempo.x += movimentoX;
            retangulo_tempo.y += movimentoY;
        }

        // Atualiza a posição do retângulo do mouse
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
        retangulo_mouse.x = mouseX - retangulo_mouse.w / 2;
        retangulo_mouse.y = mouseY - retangulo_mouse.h / 2;
        if (retangulo_mouse.x < 0) {
            retangulo_mouse.x = 0;
        }
        if (retangulo_mouse.x > LARGURA - 10) {
            retangulo_mouse.x = LARGURA - 10;
        }
        if (retangulo_mouse.y < 0) {
            retangulo_mouse.y = 0;
        }
        if (retangulo_mouse.y > ALTURA - 10) {
            retangulo_mouse.y = ALTURA - 10;
        }
    }
    return 0;
}