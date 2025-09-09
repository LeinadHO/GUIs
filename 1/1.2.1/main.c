#include <SDL2/SDL.h>
#include <stdio.h>

int main(int argc, char* args[])
{
	/* Inicialização */
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("Erro ao inicializar o SDL!");
		exit(0);
	}

	/* Criação da janela */
	SDL_Window* window = SDL_CreateWindow("1.2.1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 400, 200, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		printf("Erro ao criar janela!");
		exit(0);
	}

	/* Criação do renderizador */
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	if (renderer == NULL)
	{
		printf("Erro ao criar renderizador!");
		exit(0);
	}

	/* Definindo a cor do fundo da janela */
	SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0xFF, 0x00);
	SDL_RenderClear(renderer);

	/* Criação do chão */
	SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0x00);
	SDL_Rect ground = {0,170, 400,30};
	SDL_RenderFillRect(renderer, &ground);

	/* Criação da cabeça */
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0x00, 0X00);
	SDL_Rect head = {175,20, 50,50};
	SDL_RenderFillRect(renderer, &head);

	/* Olhos */
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderDrawPoint(renderer, 190, 40);
	SDL_RenderDrawPoint(renderer, 210, 40);

	/* Boca */
	SDL_RenderDrawLine(renderer, 190,60, 210,60);

	/* Criação do corpo */
	/* Tronco */
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderDrawLine(renderer, 200,70, 200,135);

	/* Pernas */
	SDL_RenderDrawLine(renderer, 200,135, 180,170);
	SDL_RenderDrawLine(renderer, 200,135, 220,170);

	/* Braços */
	SDL_RenderDrawLine(renderer, 200,102, 150,80);
	SDL_RenderDrawLine(renderer, 200,102, 250,80);

	SDL_RenderPresent(renderer);
	SDL_Delay(5000);

	/* Finalização */
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}