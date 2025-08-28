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
    SDL_Window* window = SDL_CreateWindow("1.2.2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 700, 700, 0);
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
    //while(true)
    //{
        /* Configuração do fundo */
        SDL_SetRenderDrawColor(renderer, 0xAD, 0xD8, 0xE6, 0x00);
        SDL_RenderClear(renderer);

        /* Criação do chão */
        boxColor(renderer, 0, 550, 700, 700, 0xFFB6ECBD);

        /* Criação do paraquedas */
        lineColor(renderer, 290, 155, 260, 125, 0xFF000000); // Corda esquerda
        lineColor(renderer, 410, 155, 440, 125, 0xFF000000); // Corda direita


        /* Criação da pessoa */
        filledCircleColor(renderer, 350, 150, 30, 0xFF4B443B); // Cabeça
        thickLineColor(renderer, 350, 180, 350, 230, 5, 0xFF4B443B); // Tronco
        thickLineColor(renderer, 350, 230, 340, 290, 5, 0xFF4B443B); // Perna esquerda
        thickLineColor(renderer, 350, 230, 360, 290, 5, 0xFF4B443B); // Perna direita
        thickLineColor(renderer, 350, 205, 290, 155, 5, 0xFF4B443B); // Braço esquerdo
        thickLineColor(renderer, 350, 205, 410, 155, 5, 0xFF4B443B); // Braço direito



        SDL_RenderPresent(renderer);
        SDL_Delay(5000);
        // Delay para 10 pixels/s = 25

        /* Verificação da posição da pessoa */
    //}

    /* Finalização */
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
