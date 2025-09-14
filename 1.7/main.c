
/* A animação representa uma pessoa pousando no solo após pular de paraquedas 
   - O personagem se move para a direita ao pressionar a seta para direita do teclado, e para a esquerda ao pressionar a seta para a esquerda 
   - Ao manter pressionado o botão esquerdo do mouse, a velocidade de queda do personagem é aumentada */

#include <assert.h>
#include <stdio.h>
#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h>
#include "../funcoes-externas/AUX_WaitEventTimeoutCount/AUX_WaitEventTimeoutCount.h"
#include "../funcoes-externas/Colisoes/colidiu.h"

#define LARGURA 500
#define ALTURA 1000

int main(int argc, char* args[]) 
{ 
    /* INICIALIZAÇÃO */ 
    // Inicialização dos subsistemas do SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) { 
        printf("Erro ao inicializar biblioteca!");
        exit(-1); 
    }
    
    // Inicialização dos subsistemas da API de imagens do SDL
    IMG_Init(0);

    // Criação da janela, do renderizador e da textura // 
    SDL_Window* window = SDL_CreateWindow("1.7", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, LARGURA, ALTURA, 0); 
    assert(window != NULL);
    
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0); 
    assert(renderer != NULL);

    SDL_Texture* image = IMG_LoadTexture(renderer, "1.7/imagens/paraquedista.png");
    assert(image != NULL);

    /* EXECUÇÃO */
    // Variáveis usadas durante a execução do programa
    int continuar = 1;
    int pousou = 0;
    Uint32 delay = 16;
    SDL_Rect chao = {0, ALTURA-150, LARGURA, ALTURA};
    SDL_Rect personagem = {150, 25, 200, 220};
    SDL_Rect sprite_atual = {0, 0, 200, 220};

    // Loop de execução do programa
    while(continuar) 
    {       
        /* CONSTRUÇÃO DO FRAME */
        // Fundo do cenário
        SDL_SetRenderDrawColor(renderer, 0xAD, 0xD8, 0xE6, 0x00); 
        SDL_RenderClear(renderer); 

        // Chão do cenário
        SDL_SetRenderDrawColor(renderer, 0xBD, 0xEC, 0xB6, 0x00);
        SDL_RenderFillRect(renderer, &chao);
        
        // Paraquedista
        SDL_RenderCopy(renderer, image, &sprite_atual, &personagem);

        // Exibição do frame
        SDL_RenderPresent(renderer); 

        /* CAPTURA DE EVENTOS */
        SDL_Event evt;
        int isevt = AUX_WaitEventTimeoutCount(&evt, &delay);
        if (isevt) 
        {
            // Eventos de finalização do programa
            if (evt.type == SDL_QUIT) {
                continuar = 0;
                break;
            }

            // Eventos de movimentação do personagem
            if (evt.type == SDL_KEYDOWN) {
                switch (evt.key.keysym.sym) {
                    case SDLK_LEFT:
                        if (personagem.x > 0) {
                            personagem.x -= 2;
                            sprite_atual = (SDL_Rect) {400, 0, 200, 220};
                        }
                        break;
                    case SDLK_RIGHT:
                        if (personagem.x < LARGURA - 200) {
                            personagem.x += 2;
                            sprite_atual = (SDL_Rect) {200, 0, 200, 220};
                        }
                        break;
                }
            }
            if (evt.type == SDL_KEYUP) {
                sprite_atual = (SDL_Rect) {0, 0, 200, 220};
            }
        }

        // Tratamento do timeout (Movimenta o paraquedista no eixo Y e recomeça o delay)
        else {
            Uint32 botao_esquerdo_pressionado = SDL_GetMouseState(NULL, NULL);
            // Acelera a queda do personagem se o botão esquerdo do mouse estiver pressionado          
            if (botao_esquerdo_pressionado & SDL_BUTTON_LMASK) {
                personagem.y += 2;
            }
            else {
                personagem.y += 1;
            }
            delay = 16;
        }

        // Verifica se o paraquedista atingiu o solo
        pousou = RetanguloColidiu(&personagem, &chao);
        if (pousou) {
            continuar = 0;
        }
    } 

    /* FINALIZAÇÃO */
    SDL_DestroyTexture(image);
    SDL_DestroyRenderer(renderer); 
    SDL_DestroyWindow(window); 
    SDL_Quit();
    return 0; 
}