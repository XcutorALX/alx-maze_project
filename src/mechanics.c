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
void move_vert(Player *player, int speed)
{
	int x_change, y_change;

	x_change = speed * cos(player->dir * (M_PI / 180));
	y_change = -speed * sin(player->dir * (M_PI / 180));
	printf("%f, %f\n", player->pos.x, player->pos.y);

	player->pos.x += x_change;
	player->pos.y += y_change;
	printf("%d, %d\n", x_change, y_change);
	printf("%f, %f\n", player->pos.x, player->pos.y);
}

/**
 * move_hor - moves a character perpendicular to the viewing angle
 *
 * @player: the player struct
 * @speed: the movement speed
 *
 * Return: none
 */
void move_hor(Player *player, int speed)
{
	int x_change, y_change, deg;

	deg = player->dir - 90;
	x_change = -speed * cos(deg * (M_PI / 180));
	y_change = speed * sin(deg * (M_PI / 180));
	printf("%f, %f\n", player->pos.x, player->pos.y);


	printf("%d, %d\n", x_change, y_change);
	player->pos.x += x_change;
	player->pos.y += y_change;
	printf("%f, %f\n", player->pos.x, player->pos.y);

}
