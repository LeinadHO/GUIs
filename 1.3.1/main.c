/* A animação representa uma pessoa pousando no solo após pular de paraquedas */

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

int main(int argc, char* args[])
{
    /* Inicialização */
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        printf("Erro ao inicializar biblioteca!");
        exit(0);
    }

    /* Criação da janela e do renderizador */
    SDL_Window* window = SDL_CreateWindow("1.3.1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 700, 700, 0);
    if (window == NULL)
    {
        printf("Erro ao criar janela!");
        exit(0);
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer == NULL)
    {
        printf("Erro ao criar renderizador!");
        exit(0);
    }

    /* Execução */
    int contador = 0;
    while(contador < 261)
    {
        /* Configuração do fundo */
        SDL_SetRenderDrawColor(renderer, 0xAD, 0xD8, 0xE6, 0x00);
        SDL_RenderClear(renderer);

        /* Criação do chão */
        boxColor(renderer, 0, 550, 700, 700, 0xFFB6ECBD);

        /* Criação do paraquedas */
        lineColor(renderer, 290, 155+contador, 260, 125+contador, 0xFF000000); // Corda esquerda
        lineColor(renderer, 410, 155+contador, 440, 125+contador, 0xFF000000); // Corda direita
        filledEllipseColor(renderer, 350, 90+contador, 180, 50, 0xFF6169FF); // Velame
        filledEllipseColor(renderer, 350, 73+contador, 160, 30, 0xFF4C50E2); // Velame (sombra)


        /* Criação da pessoa */
        filledCircleColor(renderer, 350, 150+contador, 30, 0xFF4B443B); // Cabeça
        thickLineColor(renderer, 350, 180+contador, 350, 230+contador, 5, 0xFF4B443B); // Tronco
        thickLineColor(renderer, 350, 230+contador, 340, 290+contador, 5, 0xFF4B443B); // Perna esquerda
        thickLineColor(renderer, 350, 230+contador, 360, 290+contador, 5, 0xFF4B443B); // Perna direita
        thickLineColor(renderer, 350, 205+contador, 290, 155+contador, 5, 0xFF4B443B); // Braço esquerdo
        thickLineColor(renderer, 350, 205+contador, 410, 155+contador, 5, 0xFF4B443B); // Braço direito

        /* Atualização da tela */
        SDL_RenderPresent(renderer);
        SDL_Delay(25);
        contador += 1;
    }

    /* Finalização */
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
