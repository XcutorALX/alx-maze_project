#include "maze.h"
#include <math.h>
#include <stdlib.h>

/**
 * render_map - this function renders the game map on screen
 *
 * @player: the player struct
 * @map: a map of the game
 *
 * Return: 1 on success 0 on failure
 */
int render_map(Grid *map, Player player, SDL_Renderer *renderer, Screen screen, int **local)
{
	SDL_Rect rect, cell;
	int x, y, cell_size_x, cell_size_y, x_index,
	    y_index, length;

	rect.x = 0.02 * screen.width;
	rect.y = 0.02 * screen.height;
	rect.w = screen.map_width;
	rect.h = screen.map_height;
	cell_size_y = rect.h / 7;
	cell_size_x = rect.w / 13;
	x = (rect.x + rect.w) / 2;
	y = (rect.y + rect.h) / 2;
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderFillRect(renderer, &rect);
	SDL_SetRenderDrawColor(renderer, 0, 255, 68, 255); 
	drawCircle(renderer, x, y, 0.02 * rect.w);
	localMap(player, map, local);
	x = rect.x;
/**	y = rect.y + cell_size_y + 1;

	for (; y <= rect.y + rect.h - cell_size_y; y += cell_size_y)
	{
		length = rect.x + rect.w;
		SDL_RenderDrawLine(renderer, x, y, length, y);
	}

	y = rect.y;
	x += cell_size_x + 1;
	
	for (; x <= rect.x + rect.w - cell_size_x; x += cell_size_x)
	{
		length = rect.y + rect.h;
		SDL_RenderDrawLine(renderer, x, y, x, length);
	}
**/
	y = rect.y;
	cell.w = cell_size_x;
	cell.h = cell_size_y;

	for (y_index = 0; y_index < 7; y_index++)
	{
		for(x_index = 0; x_index < 13; x_index++)
		{
			if (local[y_index][x_index] == 1)
			{
				SDL_SetRenderDrawColor(renderer, 112, 112, 112, 255);
				cell.x = x + (x_index * cell_size_x);
				cell.y = y + (y_index * cell_size_y);
				SDL_RenderFillRect(renderer, &cell);
			}
		}
	}
	return (1);
}



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
	int i, wall_height;

	vert.x = -1;
	hor.x = -1;
	inc = (float)player->fov / (float)screen->width;
	ray.dir = player->dir - (player->fov / 2);
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
		wall_height = render_wall(i, vert, hor, ray, player, renderer);
		render_floor(i, wall_height, renderer, screen);
		render_sky(i, wall_height, renderer, screen);
		ray.dir += inc;
	}
	return (1);
}

/**
 * render_wall - this function renders the walls from the map
 *
 * @vert: the vertical wall collision with the ray
 * @hor: the horizontal wall collision with the ray
 * @ray: the current ray being projected
 *
 */
int render_wall(int column, Point vert, Point hor, Ray ray, 
		Player *player, SDL_Renderer *renderer)
{
	float value;
	int x, y, align, actual_height, height_const, actual_distance;

	height_const = 64 * 554;
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
	if (actual_distance == 0)
		actual_distance = 1;
	actual_height = height_const / actual_distance; 
	SDL_RenderDrawLine(renderer, column, 240 - (actual_height / 2), 
			column, 240 + (actual_height / 2));

	return (actual_height);
}

/**
 * render_floor - this function renders the floor of the background
 *
 * @column: the current column
 * @wall_height: the height of the wall
 * @renderer: the sdl renderer
 *
 */
void render_floor(int column, int wall_height, SDL_Renderer *renderer, Screen *screen)
{
	int start, end;

	start = (screen->height + wall_height) / 2;
	end = screen->height;


	SDL_SetRenderDrawColor(renderer, 0, 129, 0, 255);
	SDL_RenderDrawLine(renderer, column, start,
                        column, end);
}

/**
 * render_sky - this function renders the sky of the background
 *
 * @column: the current column
 * @wall_height: the height of the wall
 * @renderer: the sdl renderer
 *
 */
void render_sky(int column, int wall_height, SDL_Renderer *renderer, Screen *screen)
{
	int start, end;

	end = (screen->height - wall_height) / 2;
	start = 0;


	SDL_SetRenderDrawColor(renderer, 70, 164, 255, 255);
	SDL_RenderDrawLine(renderer, column, start,
                        column, end);
}
