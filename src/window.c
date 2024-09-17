#include <SDL2/SDL.h>
#include "maze.h"

/**
 * create_window - creates an sdl window
 *
 * @screen: a pointer to the Screen struct
 * @window: a pointer to the window variable to store the result
 *
 * Return: 0 on success and 1 on failure
 */

int create_window(SDL_Window **window, Screen *screen)
{
	*window = SDL_CreateWindow("MazeRunner", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, screen->width, screen->height,
			SDL_WINDOW_SHOWN);

	if  ((*window) == NULL)
	{
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		return (1);
	}
	return (0);
}
