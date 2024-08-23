#ifndef MAZE_H
#define MAZE_H

#include <SDL2/SDL.h>

typedef struct
{
	int height;
	int width;
} Screen;

typedef struct
{
	int x;
	int y;
} Point;

typedef struct
{
	Point pos;
	int fov;
	int height;
} Player;

typedef struct
{
	Point coord;
	int height;
	int type;
} Cell;

typedef struct
{
	int width;
	int height;
	Cell **cells;
} Grid;

typedef struct
{
	Point pos;
	int dir;	
} Ray;

int create_window(SDL_Window **window, Screen *screen);
Grid *create_map(int **arr, int height, int width);
int check_collision_vert(Grid *grid, Ray *ray);
int check_collision_hor(Grid *grid, Ray *ray);
int distance(Point *p, Point *q, float deg);
int saveMap(Grid *map);
int **loadMap(int *height, int *width);

#endif
