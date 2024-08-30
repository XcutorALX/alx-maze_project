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
	Point vert, hor;
	Ray ray;
	int i, x, y, actual_height, height_const, actual_distance, align;

	vert.x = -1;
	hor.x = -1;
	height_const = 64 * 554;
	inc = (float)player->fov / (float)screen->width;
	ray.dir = (float) (player->dir) - (player->fov / 2);
	ray.pos = player->pos;
	for (i = 0; i < screen->width; i++)
	{
		if (ray.dir >= 360)
			ray.dir = fmod(ray.dir, 360);
        	else if (ray.dir < 0)
			ray.dir += 360;
	
		if (ray.dir != 0 && ray.dir != 180)
			hor = check_collision_hor(map, &ray);
		if (ray.dir != 90 && ray.dir != 270)
			vert = check_collision_vert(map, &ray);
		x = hor.x != -1 ? distance_sqrt(&(ray.pos), &hor) : -1;
		y = vert.x  != -1 ? distance_sqrt(&(ray.pos), &vert) : -1;
		value = cos(((float)(player->dir) - ray.dir) * M_PI / 180);
		if (x == -1 || (y != -1 && y < x))
		{
			align = 0;
			actual_distance = y * value;
		}
		else
		{
			align = 1;
			actual_distance = x * value;
		}
		align == 1 ? SDL_SetRenderDrawColor(renderer, 112, 112, 112, 255) : 
			SDL_SetRenderDrawColor(renderer, 96, 96, 96, 255);
		actual_height = height_const / actual_distance; 
		SDL_RenderDrawLine(renderer, i, 240 - (actual_height / 2), 
				i, 240 + (actual_height / 2));
		ray.dir += inc;
	}
	return (1);
}
