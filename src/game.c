#include "maze.h"
#include <math.h>
#include <stdlib.h>

/**
 * render_background - this function renders the background of the maze
 *
 * @map: the map of the game
 *
 * Return: 1 on success else 0
 */
int render_background(Grid *map, Player *player, Screen *screen)
{
	float inc;
	Point temp;
	Ray ray;
	int i;

	inc = player->fov / screen->width;
	ray.dir = 280;
	temp.x = 32;
	temp.y = 32;
	ray.pos = temp;

	for (i = 0; i < screen->width; i++)
	{
		
	}

	return (1);
}
