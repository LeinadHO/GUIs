#include <SDL2/SDL.h>
#include <stdio.h>

int main (int argc, char* args[])
{
    /* INICIALIZAÇÃO */

    // Inicialização dos subsistemas
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        printf("Erro ao iniciar os subsistemas!");
    }

    // Criação da janela
    SDL_Window* win = SDL_CreateWindow("Movendo um Retângulo", 
                        SDL_WINDOWPOS_UNDEFINED, 
                        SDL_WINDOWPOS_UNDEFINED,
                        400, 200, SDL_WINDOW_SHOWN
                      );
    if (win == NULL) {
        printf("Erro ao iniciar janela!");
    }

    // Criação do renderizador
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);
    if (ren == NULL) {
        printf("Erro ao iniciar renderizador!");
    }

    /* EXECUÇÃO */

    // Declaração das variáveis
    SDL_Rect retangulo_tempo = {40,20, 10,10};
    SDL_Rect retangulo_teclado = {60,30, 10,10};
    SDL_Rect retangulo_mouse = {80,40, 10,10};

    // Loop de captura de eventos
    while (1) 
    {   
        SDL_Event evt;
        int isevt = SDL_WaitEventTimeout(&evt, 500);
        if (isevt)
        {
            // Captura eventos de finalização do programa
            if (evt.type == SDL_QUIT) { 
                SDL_DestroyRenderer(ren);
                SDL_DestroyWindow(win);
                SDL_Quit();
                break;
            }
        }
        SDL_SetRenderDrawColor(ren, 0xFF, 0xFF, 0xFF, 0x00);
        SDL_RenderClear(ren);
        SDL_SetRenderDrawColor(ren, 0xFF, 0x00, 0x00, 0x00);
        SDL_RenderFillRect(ren, &retangulo_tempo);
        SDL_SetRenderDrawColor(ren, 0x00, 0xFF, 0x00, 0x00);
        SDL_RenderFillRect(ren, &retangulo_teclado);
        SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0xFF, 0x00);
        SDL_RenderFillRect(ren, &retangulo_mouse);
        SDL_RenderPresent(ren);
    }
}