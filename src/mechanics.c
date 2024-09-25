#include "maze.h"
#include <math.h>
#include "struct.h"

/**
 * normalize - normalizes the distance moved
 *
 * @player: the player struct
 * @prev: the prev position in the game
 * @speed: the movement speed
 *
 * Return: none
 */
void normalize(Player *player, Player *prev, float speed)
{
	float mag;
	float x, y, newx, newy;

	if (distance_flt(&(player->pos), &(prev->pos)) <= speed)
		return;

	x = player->pos.x - prev->pos.x;
	y = player->pos.y - prev->pos.y;
	mag = sqrt((x) * (x) + (y) * (y));

	if (mag > 0)
	{
		x /= mag;
		y /= mag;
	}
	else
		return;

	newx = x * speed;
	newy = y * speed;
	player->pos.x = newx;
	player->pos.y = newy;
}

/**
 * movement_logic - this function contains the logic for
 * movement and rotation
 *
 * @dt: the change in time since the last render
 * @player: a struct containing player info
 * @keys: a struct containing the state of all essential keys
 * @map: the map of the game
 *
 * Return: none
 */
void movement_logic(float dt, Gamepad keys, Player *player, Grid *map)
{
	float adj_speed, adj_rot;

	adj_speed = dt * player->speed;
	adj_rot = dt * player->rot_speed;

	if (keys.rot_left)
		player->dir -= adj_rot;
	if (keys.rot_right)
		player->dir += adj_rot;

	if (player->dir >= 360)
		player->dir -= 360;
	else if (player->dir < 0)
		player->dir += 360;

	if (keys.forward)
		move_vert(player, adj_speed, map);

	if (keys.backward)
		move_vert(player, -1 * adj_speed, map);

	if (keys.left)
		move_hor(player, -1 * adj_speed, map);

	if (keys.right)
		move_hor(player, adj_speed, map);
}

/**
 * move_vert - moves a character parallel to the viewing angle
 *
 * @player: the player struct
 * @speed: the movement speed
 * @map: the map of the game
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
	cor = 8;
	temp_x = player->pos.x;
	temp_y = player->pos.y;

	x_change = speed * cos(dir * (M_PI / 180));
	y_change = -speed * sin(dir * (M_PI / 180));

	temp_x += x_change;
	temp_y += y_change;


	x_cor = cor * (x_change / speed);
	y_cor = -cor * (y_change / -speed);

	x_cor = speed < 0 ? -x_cor : x_cor;
	y_cor = speed < 0 ? -y_cor : y_cor;

	x_index = floor((temp_x + x_cor) / 64);
	y_index = floor((temp_y + y_cor) / 64);

	if ((&(cells[y_index][x_index]))->type != 1)
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
 * @map: the map of the game
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

	x_cor = -cor * (x_change / -speed);
	y_cor = cor * (y_change / speed);

	temp_x += x_change;
	temp_y += y_change;

	x_cor = speed < 0 ? -x_cor : x_cor;
	y_cor = speed < 0 ? -y_cor : y_cor;

	x_index = floor((temp_x + x_cor) / 64);
	y_index = floor((temp_y + y_cor) / 64);

	if ((&(cells[y_index][x_index]))->type != 1)
	{
		player->pos.x += x_change;
		player->pos.y += y_change;
	}
}
