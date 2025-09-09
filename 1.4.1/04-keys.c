#include <SDL2/SDL.h>
#include <stdlib.h>
#include <time.h>

int main (int argc, char* args[])
{
    /* INICIALIZACAO */
    srand(time(NULL));
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("Movendo um Retângulo",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         400, 200, SDL_WINDOW_SHOWN
                      );
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);

    /* EXECUÇÃO */
    int red[10], green[10], blue[10], retangulos_criados = 0;
    SDL_Rect r = { 40,20, 10,10 };
    SDL_Event evt;
    SDL_Rect retangulos[10];

    /* Criação do primeiro frame */
    SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);
    SDL_RenderClear(ren);
    SDL_SetRenderDrawColor(ren, 0x00,0x00,0xFF,0x00);
    SDL_RenderFillRect(ren, &r);
    SDL_RenderPresent(ren);

    while (1) {
        
        SDL_WaitEvent(&evt);

        /* Captura teclas pressionadas do teclado */
        if (evt.type == SDL_KEYDOWN) { 
            switch (evt.key.keysym.sym) {
                case SDLK_UP:
                    if (r.y > 0) {
                        r.y -= 5;
                    }
                    break;
                case SDLK_DOWN:
                    if (r.y < 190) {
                        r.y += 5;
                    }
                    break;
                case SDLK_LEFT:
                    if (r.x > 0) {
                        r.x -= 5;
                    }
                    break;
                case SDLK_RIGHT:
                    if (r.x < 390) {
                        r.x += 5;
                    }
                    break;
            }
        }

        /* Captura botões pressionados do mouse */
        if (evt.type == SDL_MOUSEBUTTONDOWN) { 
            if (retangulos_criados < 10) {
                retangulos[retangulos_criados].x = evt.button.x;
                retangulos[retangulos_criados].y = evt.button.y;
                retangulos[retangulos_criados].w = 15;
                retangulos[retangulos_criados].h = 15;
                red[retangulos_criados] = rand() % 256;
                green[retangulos_criados] = rand() % 256;
                blue[retangulos_criados] = rand() % 256;
                retangulos_criados += 1;
            }
        }

        /* Captura se o usuário finalizou o programa (Botão X da janela ou ALT+F4) */
        if (evt.type == SDL_QUIT) { 
            SDL_DestroyRenderer(ren);
            SDL_DestroyWindow(win);
            SDL_Quit();
            break;
        }

        /* Limpa o fundo da janela */
        SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);
        SDL_RenderClear(ren);
        
        /* Desenha os retângulos gerados após o clique do mouse */
        for (int i=0; i<retangulos_criados; i++) {
            SDL_SetRenderDrawColor(ren, red[i], green[i], blue[i], 0);
            SDL_RenderFillRect(ren, &retangulos[i]);
        }
        
        /* Desenha o retângulo móvel */
        SDL_SetRenderDrawColor(ren, 0x00,0x00,0xFF,0x00);
        SDL_RenderFillRect(ren, &r);

        /* Exibe tudo que foi construído durante o loop */
        SDL_RenderPresent(ren);

    }

    return 0;
}
