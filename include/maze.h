#ifndef MAZE_H
#define MAZE_H

#include <SDL2/SDL.h>

#define KEY_W 119
#define KEY_A 97
#define KEY_S 115
#define KEY_D 100
#define KEY_LEFT 1073741904 
#define KEY_RIGHT 1073741903

typedef struct
{
	int height;
	int width;
	int map_block_size;
	int map_width;
	int map_height;
} Screen;

typedef struct
{
	float x;
	float y;
} Point;

typedef struct
{
	Point pos;
	float dir;
	int fov;
	int height;
	int speed;
	int rot_speed;
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

typedef struct
{
	int forward;
	int backward;
	int left;
	int right;
	int rot_left;
	int rot_right;
} Gamepad;

int create_window(SDL_Window **window, Screen *screen);
Grid *create_map(int **arr, int height, int width);
Point check_collision_vert(Grid *grid, Ray *ray);
Point check_collision_hor(Grid *grid, Ray *ray);
int distance(Point *p, Point *q, float deg);
int saveMap(Grid *map);
int **loadMap(int *height, int *width);
int render_background(Grid *map, Player *player, Screen *screen, SDL_Renderer *renderer);
int distance_sqrt(Point *p1, Point *p2);
void move_vert(Player *player, float speed, Grid *map);
void move_hor(Player *player, float speed, Grid *map);
int render_wall(int column, Point vert, Point hor, Ray ray, Player *player, SDL_Renderer *renderer);
void render_floor(int i, int wall_height, SDL_Renderer *renderer, Screen *screen);
void render_sky(int i, int wall_height, SDL_Renderer *renderer, Screen *screen);
int render_map(Grid *map, Player player, SDL_Renderer *renderer, Screen screen, int **local);
int init_game(Player *player, Grid **map, int ***local_map);
int game_loop(Grid *map, SDL_Renderer *renderer, Player player, Screen screen, int **local);
int event_handler(SDL_Event event, Player *player, Grid *map, Gamepad *keys);
void handle_key_event(int code, Gamepad *keys, int status);
void normalize(Player *player, Player *prev, float speed);
float distance_flt(Point *p1, Point *p2);
void drawCircle(SDL_Renderer *renderer, int centerX, int centerY, int radius);
int localMap(Player player, Grid *map, int **local);
void free2DArray(int** array, int rows);
int **create2DArray(int rows, int cols);
void print2DArray(int** array, int rows, int cols);
void draw_radial_cone(SDL_Renderer *renderer, int center_x, int center_y,                                                               float cone_angle_deg, float length, int num_lines, float dir_deg);
void mirrorArray(int **arr, int rows, int cols);
int render_player_view(Player player, SDL_Renderer *renderer, Screen screen);
int render_grid(Grid *map, SDL_Renderer *renderer, SDL_Rect rect, int **local);

#endif
