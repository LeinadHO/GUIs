
/* A animação representa uma pessoa pousando no solo após pular de paraquedas 
   - O personagem se move para a direita ao pressionar a seta para direita do teclado, e para a esquerda ao pressionar a seta para a esquerda 
   - Ao manter pressionado o botão esquerdo do mouse, a velocidade de queda do personagem é aumentada */

#include <stdio.h>
#include <SDL2/SDL.h> 
#include <SDL2/SDL2_gfxPrimitives.h>
#include "../1.5.2/AUX_WaitEventTimeoutCount.h"


int main(int argc, char* args[]) 
{ 
    /* Inicialização */ 
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) { 
        printf("Erro ao inicializar biblioteca!"); 
        exit(0); 
    } 

    /* Criação da janela e do renderizador */ 
    SDL_Window* window = SDL_CreateWindow(
        "1.3.1", 
        SDL_WINDOWPOS_UNDEFINED, 
        SDL_WINDOWPOS_UNDEFINED, 
        700, 700, 0); 
    if (window == NULL) { 
        printf("Erro ao criar janela!"); 
        exit(0); 
    } 
    
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0); 
    if (renderer == NULL) { 
        printf("Erro ao criar renderizador!"); 
        exit(0); 
    } 

    /* Execução */ 
    Uint32 delay = 100;
    int movimento_queda = 0;
    int movimento_horizontal = 0;
    while(movimento_queda < 261) 
    {       
        /* Construção do frame */
        // Fundo do cenário
        SDL_SetRenderDrawColor(renderer, 0xAD, 0xD8, 0xE6, 0x00); 
        SDL_RenderClear(renderer); 

        // Chão do cenário
        boxColor(renderer, 0, 550, 700, 700, 0xFFB6ECBD); 
        
        // Paraquedas
        lineColor(renderer, 290 + movimento_horizontal, 155 + movimento_queda, 260 + movimento_horizontal, 125 + movimento_queda, 0xFF000000); // Corda esquerda 
        lineColor(renderer, 410 + movimento_horizontal, 155 + movimento_queda, 440 + movimento_horizontal, 125 + movimento_queda, 0xFF000000); // Corda direita 
        filledEllipseColor(renderer, 350 + movimento_horizontal, 90 + movimento_queda, 180, 50, 0xFF6169FF); // Velame 
        filledEllipseColor(renderer, 350 + movimento_horizontal, 73 + movimento_queda, 160, 30, 0xFF4C50E2); // Velame (sombra) 

        // Pessoa
        filledCircleColor(renderer, 350 + movimento_horizontal, 150 + movimento_queda, 30, 0xFF4B443B); // Cabeça
        thickLineColor(renderer, 350 + movimento_horizontal, 180 + movimento_queda, 350 + movimento_horizontal, 230 + movimento_queda, 5, 0xFF4B443B); // Tronco 
        thickLineColor(renderer, 350 + movimento_horizontal, 230 + movimento_queda, 340 + movimento_horizontal, 290 + movimento_queda, 5, 0xFF4B443B); // Perna esquerda 
        thickLineColor(renderer, 350 + movimento_horizontal, 230 + movimento_queda, 360 + movimento_horizontal, 290 + movimento_queda, 5, 0xFF4B443B); // Perna direita 
        thickLineColor(renderer, 350 + movimento_horizontal, 205 + movimento_queda, 290 + movimento_horizontal, 155 + movimento_queda, 5, 0xFF4B443B); // Braço esquerdo 
        thickLineColor(renderer, 350 + movimento_horizontal, 205 + movimento_queda, 410 + movimento_horizontal, 155 + movimento_queda, 5, 0xFF4B443B); // Braço direito 
        
        // Exibição da tela
        SDL_RenderPresent(renderer); 

        /* Captura de eventos */
        SDL_Event evt;
        int isevt = AUX_WaitEventTimeoutCount(&evt, &delay);
        if (isevt) 
        {
            // Eventos de finalização do programa
            if (evt.type == SDL_QUIT) {
                SDL_DestroyRenderer(renderer); 
                SDL_DestroyWindow(window); 
                SDL_Quit();
                break;  
            }

            // Eventos de teclas do teclado
            if (evt.type == SDL_KEYDOWN) {
                switch (evt.key.keysym.sym) {
                    case SDLK_RIGHT:
                        movimento_horizontal += 1;
                        break;
                    case SDLK_LEFT:
                        movimento_horizontal -= 1;
                        break;
                }
            }
        }

        // Tratar o timeout
        else {
            // Reseta o delay e a movimentação vertical baseado no estado de pressionamento do botão
            Uint32 pressionado = SDL_GetMouseState(NULL, NULL);
            if (pressionado & SDL_BUTTON_LMASK) {
                movimento_queda += 2;
                delay = 50;
            }
            else {
                movimento_queda += 1;
                delay = 100;
            }
        }
    } 
    return 0; 
}