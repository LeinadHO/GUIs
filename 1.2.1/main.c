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
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0x00);
	SDL_RenderClear(renderer);

	/* Criação do cabeça */
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0x00, 0X00);
	SDL_Rect rectangle = {175,20, 50,50};
	SDL_RenderFillRect(renderer, &rectangle);

	/* Criação do corpo */
	SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0x00);
	SDL_RenderDrawLine(renderer, 200,70, 200,135);

	/* Criação do ponto */
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderDrawPoint(renderer, 200, 45);
	
	SDL_RenderPresent(renderer);
	SDL_Delay(5000);
}