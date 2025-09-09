#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <stdio.h>

int main(int argc, char* args[])
{
    /* Inicialização */
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        printf("Erro ao inicializar biblioteca!");
        exit(0);
    }

    /* Criação da janela e do renderizador */
    SDL_Window* window = SDL_CreateWindow("1.2.2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 700, 900, 0);
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
    /* Cor de fundo da janela */
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x70, 0xFF);
    SDL_RenderClear(renderer);

    /* Chão */
    boxColor(renderer, 0, 800, 700, 900, 0xFF2B4006);

    /* Lua */
    filledCircleColor(renderer, 100, 100, 50, 0xFF2DA4E2);

    /* Foguete */
    filledTrigonColor(renderer, 250, 250, 450, 250, 350, 100, 0xFF0000FF);
    boxColor(renderer, 250, 250, 450, 600, 0xFFA6A6A6);
    filledTrigonColor(renderer, 250, 550, 135, 550, 250, 350, 0xFF0000FF);
    filledTrigonColor(renderer, 450, 550, 565, 550, 450, 350, 0xFF0000FF);
    filledCircleColor(renderer, 350, 350, 50, 0xFF808080);
    filledCircleColor(renderer, 350, 350, 35, 0xFFE6D8AD);
    Sint16 vx[4] = {250, 300, 400, 450};
    Sint16 vy[4] = {600, 700, 700, 600};
    filledPolygonColor(renderer, vx, vy, 4, 0xFF4E4C49);
    
    SDL_RenderPresent(renderer);
    SDL_Delay(5000);

    /* Finalização */
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
