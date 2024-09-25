#ifndef STRUCT_H
#define STRUCT_H

#include <SDL2/SDL.h>

#define KEY_W 119
#define KEY_A 97
#define KEY_S 115
#define KEY_D 100
#define KEY_LEFT 1073741904
#define KEY_RIGHT 1073741903

/**
 * struct screen_s - a struct to hold screen info
 *
 * @height: Height of the screen
 * @width: width of the screen
 * @map_block_size: the size of map blocks
 * @map_width: the width of the map
 * @map_height: the height of the map
 *
 * Description: Longer description
 */
typedef struct screen_s
{
	int height;
	int width;
	int map_block_size;
	int map_width;
	int map_height;
} Screen;

/**
 * struct point_s - a struct to represent a point
 * in space
 *
 * @x: the x coordinate of the point
 * @y: the y coordinate of the point
 *
 * Description: Longer description
 */
typedef struct point_s
{
	float x;
	float y;
} Point;

/**
 * struct player_s - a struct to hold player info
 *
 * @pos: the player's position
 * @dir: the players direction in degrees
 * @speed: the player's movement speed
 * @fov: the players field of view in degrees
 * @rot_speed: the player's rotation speed
 * @height: Height of the player
 *
 * Description: Longer description
 */
typedef struct player_s
{
	Point pos;
	float dir;
	int fov;
	int height;
	int speed;
	int rot_speed;
} Player;

/**
 * struct cell_s - a struct to represent a cell
 *
 * @coord: the localized x,y coordinate relative
 * to the grid struct
 * @height: the height of the cell
 * @type: 1 if occupied, 0 if empty
 *
 * Description: Longer description
 */
typedef struct cell_s
{
	Point coord;
	int height;
	int type;
} Cell;

/**
 * struct grid_s - a struct to represent a grid
 *
 * @width: the width of the grid
 * @height: the height of the grid
 * @cells: a 2D array of cells to represent a grid
 *
 * Description: Longer description
 */
typedef struct grid_s
{
	int width;
	int height;
	Cell **cells;
} Grid;

/**
 * struct ray_s - a struct to represent a ray
 *
 * @pos: the starting pos of the ray
 * @dir: the direction of the ray in degrees
 *
 * Description: Longer description
 */
typedef struct ray_s
{
	Point pos;
	float dir;
} Ray;

/**
 * struct pad_s - a struct containing the
 * state of all game keys
 *
 * @forward: the state of the forward movement key
 * @backward: the state of the backward movement key
 * @left: the state of the left movement key
 * @right: the state of the right movement key
 * @rot_left: the state of the rotate left key
 * @rot_right: the state of the rotate right key
 *
 * Description: Longer description
 */
typedef struct pad_s
{
	int forward;
	int backward;
	int left;
	int right;
	int rot_left;
	int rot_right;
} Gamepad;

/**
 * struct resource_s - a struct to keep track of
 * resources to be free at the end
 *
 * Description: longer description
 */
typedef struct resource_s
{
	SDL_Window *window;
	SDL_Renderer *renderer;
	Grid *map;
	int **arr;
	int **local_map;
} Resources;

#endif
