#include "maze.h"
#include "struct.h"
#include <math.h>
#include <stdlib.h>

/**
 * render_grid - this function renders the grid and walls on the game map
 *
 * @map: a map of the game
 * @renderer: the SDL renderer
 * @local: a local map of the player's immediate surrounding
 * @rect: an SDL_Rect struct
 *
 * Return: 1 on success 0 on failure
 */
int render_grid(Grid *map, SDL_Renderer *renderer, SDL_Rect rect, int **local)
{
	SDL_Rect cell;
	int x, y, cell_size_x, cell_size_y, x_index, y_index, length;

	cell_size_y = rect.h / 7;
	cell_size_x = rect.w / 13;
	x = rect.x;
	y = rect.y + cell_size_y + 1;
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
	x = rect.x;
	cell.w = cell_size_x;
	cell.h = cell_size_y;
	for (y_index = 0; y_index < 7; y_index++)
	{
		for (x_index = 0; x_index < 13; x_index++)
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
 * render_player_view - this function renders the
 * player's view (player, circle, and FOV)
 *
 * @player: the player struct
 * @renderer: the SDL renderer
 * @screen: the screen struct
 *
 * Return: 1 on success 0 on failure
 */
int render_player_view(Player player, SDL_Renderer *renderer, Screen screen)
{
	SDL_Rect rect;
	int x, y, view, deg;

	view = player.fov;
	deg = 150 - player.dir;
	deg %= 360;

	rect.x = 0.02 * screen.width;
	rect.y = 0.02 * screen.height;
	rect.w = screen.map_width;
	rect.h = screen.map_height;

	x = rect.x + rect.w / 2;
	y = rect.y + rect.h / 2;

	SDL_SetRenderDrawColor(renderer, 0, 255, 68, 255);
	drawCircle(renderer, x, y, 0.02 * rect.w);
	draw_radial_cone(renderer, x, y, view, 60, 30, deg);

	return (1);
}
