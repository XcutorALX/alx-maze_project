#include <SDL2/SDL.h>
#include "maze.h"
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

/**
 * main - entry point for the game
 *
 * Return: 0
 **/
int main(void)
{
	SDL_Window *window = NULL;
	SDL_Surface *screenSurface = NULL;
	SDL_Renderer *renderer;
	Screen screen;
	Player player;
	Grid *map;
	int height, width, **arr;

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        	return (1);
	}

	screen.width = 640;
	screen.height = 480;
	if  (create_window(&window, &screen) == 1)
	{
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		return (1);
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	
	if (renderer == NULL) 
	{
		SDL_DestroyWindow(window);
		printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
		SDL_Quit();
		return 1;
	}

	height = 0;
	width = 0;
	arr = loadMap(&height, &width);
	map = create_map(arr, height, width);

	player.fov = 60;
	player.height = 32;
	player.dir = 280;
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);	
	screenSurface = SDL_GetWindowSurface( window );
	render_background(map, &player, &screen, renderer);
	SDL_RenderPresent(renderer);

	SDL_Event e; int quit = 0; while( !quit ){ while( SDL_PollEvent( &e ) ){ if( e.type == SDL_QUIT ) quit = 1; } }

	SDL_DestroyWindow( window );
	SDL_Quit();
	return (0);
}
