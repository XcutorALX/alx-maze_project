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
	int dir;
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
	float dir;	
} Ray;

int create_window(SDL_Window **window, Screen *screen);
Grid *create_map(int **arr, int height, int width);
Point check_collision_vert(Grid *grid, Ray *ray);
Point check_collision_hor(Grid *grid, Ray *ray);
int distance(Point *p, Point *q, float deg);
int saveMap(Grid *map);
int **loadMap(int *height, int *width);
int render_background(Grid *map, Player *player, Screen *screen, SDL_Renderer *renderer);
int distance_sqrt(Point *p1, Point *p2);
int custom_round(float value);

#endif
