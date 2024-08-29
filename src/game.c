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
int render_background(Grid *map, Player *player, Screen *screen, SDL_Renderer *renderer)
{
	float inc, angle, value;
	Point temp, vert, hor;
	Ray ray;
	int i, x, y, actual_height, height_const, actual_distance;

	vert.x = -1;
	hor.x = -1;
	height_const = 64 * 554;
	inc = (float)player->fov / (float)screen->width;
	ray.dir = (float) (player->dir) - (player->fov / 2);
	temp.x = 96;
	temp.y = 96;
	ray.pos = temp;

	for (i = 0; i < screen->width; i++)
	{
		if (ray.dir != 0 && ray.dir != 180)
			vert = check_collision_vert(map, &ray);

		if (ray.dir != 90 && ray.dir != 270)
			hor = check_collision_hor(map, &ray);

		x = hor.x != -1 ? distance_sqrt(&(ray.pos), &hor) : -1;
		y = vert.x  != -1 ? distance_sqrt(&(ray.pos), &vert) : -1;

		value = cos(((float)(player->dir) - ray.dir) * M_PI / 180);

		if (x == -1)
			actual_distance = y * value;
		else if (y == -1)
			actual_distance = x * value;
		else			
			actual_distance = x < y ? x * value : y * value;


		actual_height = height_const / actual_distance;
		SDL_RenderDrawLine(renderer, i, 240 - (actual_height / 2), 
				i, 240 + (actual_height / 2));
		printf("%d, %d\n", i, actual_height);
		ray.dir += inc;
	}

	return (1);
}
