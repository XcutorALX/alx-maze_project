#include "maze.h"
#include <math.h>

/**
 * move_vert - moves a character parallel to the viewing angle
 *
 * @player: the player struct
 * @speed: the movement speed
 *
 * Return: none
 */
void move_vert(Player *player, int speed, Grid *map)
{
	int x_change, y_change, temp_x, temp_y, 
	    x_index, y_index, x_cor, y_cor, cor;
	Cell **cells;

	cells = map->cells;
	cor = 32;
	temp_x = player->pos.x;
	temp_y = player->pos.y;

	x_change = speed * cos(player->dir * (M_PI / 180));
	y_change = -speed * sin(player->dir * (M_PI / 180));

	temp_x += x_change;
	temp_y += y_change;

	x_cor = player->dir > 90 && player->dir < 270? -cor : cor;
	y_cor = player->dir < 180 ? -cor : cor;

	x_index = floor((temp_x + x_cor) / 64);
	y_index = floor((temp_y + y_cor) / 64);

	if ((&(cells[ y_index ][ x_index ]))->type != 1)
	{
		player->pos.x = temp_x;
		player->pos.y = temp_y;
	}
}

/**
 * move_hor - moves a character perpendicular to the viewing angle
 *
 * @player: the player struct
 * @speed: the movement speed
 *
 * Return: none
 */
void move_hor(Player *player, int speed, Grid *map)
{
	int x_change, y_change, temp_x, temp_y,
	    x_index, y_index, deg, cor, x_cor, y_cor;
	Cell **cells;

	cells = map->cells;
	temp_x = player->pos.x;
	temp_y = player->pos.y;
	cor = 8;

	deg = player->dir - 90;
	x_change = -speed * cos(deg * (M_PI / 180));
	y_change = speed * sin(deg * (M_PI / 180));

	x_cor = deg > 90 && deg < 270? -cor : cor;
	y_cor = deg < 180 ? -cor : cor;

	temp_x += x_change;
	temp_y += y_change;

	x_index = floor((temp_x + x_cor) / 64);
	y_index = floor((temp_y + y_cor) / 64);

	if ((&(cells[ y_index ][ x_index ]))->type != 1)
	{
		player->pos.x += x_change;
		player->pos.y += y_change;
	}
}
