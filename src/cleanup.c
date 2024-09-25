#include <SDL2/SDL.h>
#include "maze.h"
#include "struct.h"

/**
 * cleanup - this function frees all the allocated memory
 *
 * @resources: a struct that holds the addresses to be freed
 *
 * Return: none
 */
void cleanup(Resources resources)
{
	if (resources.window != NULL)
		SDL_DestroyWindow(resources.window);
	if (resources.renderer != NULL)
		SDL_DestroyRenderer(resources.renderer);
	if (resources.map != NULL)
		cleanup_grid(resources.map);
	if (resources.local_map != NULL)
		free2DArray(resources.local_map, 7);

	SDL_Quit();
}

/**
 * cleanup_grid - this function cleans up the grid
 * struct
 *
 * @grid: a struct that holds the game map
 *
 * Return: void
 */
void cleanup_grid(Grid *grid)
{
	int i;

	for (int i = 0; i < grid->height; i++)
	{
		free(grid->cells[i]);
	}
    
	free(grid->cells);
    
	grid->cells = NULL;
	
	free(grid);
}
