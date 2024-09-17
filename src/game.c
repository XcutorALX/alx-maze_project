#include "maze.h"
#include <math.h>
#include <stdlib.h>

/**
 * render_map - this function renders the game map on screen
 *
 * @player: the player struct
 * @map: a map of the game
 * @renderer: the SDL_Renderer struct
 * @screen: the Screen struct with data on the screen
 * @local: a local version of the map immediate to the player
 *
 * Return: 1 on success 0 on failure
 */
int render_map(Grid *map, Player player, SDL_Renderer *renderer,
		Screen screen, int **local)
{
	SDL_Rect rect, cell;
	int x, y, cell_size_x, cell_size_y, x_index,
	    y_index, length, view, deg;

	view = player.fov;
	deg = 150 - player.dir;
	deg %= 360;

	rect.x = 0.02 * screen.width;
	rect.y = 0.02 * screen.height;
	rect.w = screen.map_width;
	rect.h = screen.map_height;

	x = rect.x + rect.w / 2;
	y = rect.y + rect.h / 2;

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderFillRect(renderer, &rect);

	localMap(player, map, local);

	render_player_view(player, renderer, screen);
	render_grid(map, renderer, rect, local);

	return (1);
}


/**
 * render_background - this function renders the background of the maze
 *
 * @map: the map of the game
 * @player: a struct with player info
 * @screen: a struct with screen info
 * @renderer: the SDL_Renderer struct
 *
 * Return: 1 on success else 0
 */
int render_background(Grid *map, Player *player, Screen *screen,
		SDL_Renderer *renderer)
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
 * @column: the current column on the screen being rendered
 * @player: a struct containing player info
 * @renderer: the SDL_Renderer struct
 *
 * Return: the height of the wall slice rendered
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
 * @screen: a struct containing game screen info
 *
 * Return: none
 */
void render_floor(int column, int wall_height, SDL_Renderer *renderer,
		Screen *screen)
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
 * @screen: a struct containing game screen info
 *
 */
void render_sky(int column, int wall_height, SDL_Renderer *renderer,
		Screen *screen)
{
	int start, end;

	end = (screen->height - wall_height) / 2;
	start = 0;


	SDL_SetRenderDrawColor(renderer, 70, 164, 255, 255);
	SDL_RenderDrawLine(renderer, column, start,
			column, end);
}
