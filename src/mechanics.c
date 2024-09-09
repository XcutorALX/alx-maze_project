#include "maze.h"
#include <math.h>

/**
 * normalize - normalizes the distance moved
 *
 * @player: the player struct
 * @map: the game map
 *
 * Return: none
 */
void normalize(Player *player, Player *prev, float speed)
{
	float mag;
	float x, y, newx, newy;

	if (distance_flt(&(player->pos), &(prev->pos)) <= speed)
		return ;
	
	x = player->pos.x - prev->pos.x;
	y = player->pos.y - prev->pos.y;
	mag = sqrt((x) * (x) + (y) * (y));

	if (mag > 0) 
	{
        	x /= mag;
        	y /= mag;
    	}
	else
		return ;

	newx = x * speed;
	newy = y * speed;
	player->pos.x = newx;
	player->pos.y = newy;
}


/**
 * move_vert - moves a character parallel to the viewing angle
 *
 * @player: the player struct
 * @speed: the movement speed
 *
 * Return: none
 */
void move_vert(Player *player, float speed, Grid *map)
{
	float x_change, y_change, temp_x, temp_y, 
	    x_cor, y_cor, cor;
	int x_index, y_index, dir;
	Cell **cells;

	dir = floor(player->dir);
	cells = map->cells;
	cor = 16;
	temp_x = player->pos.x;
	temp_y = player->pos.y;

	x_change = speed * cos(dir * (M_PI / 180));
	y_change = -speed * sin(dir * (M_PI / 180));

	temp_x += x_change;
	temp_y += y_change;

	x_cor = dir > 90 && dir < 270? -cor : cor;
	y_cor = dir < 180 ? -cor : cor;

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
void move_hor(Player *player, float speed, Grid *map)
{
	float x_change, y_change, temp_x, temp_y,
	    deg, cor, x_cor, y_cor;
	int x_index, y_index, dir;
	Cell **cells;

	dir = floor(player->dir);
	cells = map->cells;
	temp_x = player->pos.x;
	temp_y = player->pos.y;
	cor = 8;

	deg = dir - 90;
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
