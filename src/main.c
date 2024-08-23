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
	Screen screen;
	Player player;
	Grid map;

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

	player.
	screenSurface = SDL_GetWindowSurface( window );
	SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ) );
	SDL_UpdateWindowSurface( window );

	SDL_Event e; int quit = 0; while( !quit ){ while( SDL_PollEvent( &e ) ){ if( e.type == SDL_QUIT ) quit = 1; } }

	SDL_DestroyWindow( window );
	SDL_Quit();
	return (0);
}
