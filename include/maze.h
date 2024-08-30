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
	float x;
	float y;
} Point;

typedef struct
{
	Point pos;
	int dir;
	int fov;
	int height;
	int speed;
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
void move_vert(Player *player, int speed);
void move_hor(Player *player, int speed);
int render_wall(int column, Point vert, Point hor, Ray ray, Player *player, SDL_Renderer *renderer);
void render_floor(int i, int wall_height, SDL_Renderer *renderer, Screen *screen);
void render_sky(int i, int wall_height, SDL_Renderer *renderer, Screen *screen);

#endif
