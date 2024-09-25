#ifndef MAZE_H
#define MAZE_H

#include <SDL2/SDL.h>
#include "struct.h"

/* main functions */
int init_game(Player *player, Grid **map, int ***local_map);
int game_loop(Grid *map, SDL_Renderer *renderer,
		Player player, Screen screen, int **local);
int event_handler(SDL_Event event, Player *player, Grid *map, Gamepad *keys);
void handle_key_event(int code, Gamepad *keys, int status);
int create_window(SDL_Window **window, Screen *screen);

/* Map functions */
Grid *create_map(int **arr, int height, int width);
int saveMap(Grid *map);
int **loadMap(int *height, int *width);
int localMap(Player player, Grid *map, int **local);

/* collision checkers */
Point check_collision_vert(Grid *grid, Ray *ray);
Point check_collision_hor(Grid *grid, Ray *ray);

/* distance functions */
float distance_flt(Point *p1, Point *p2);
int distance(Point *p, Point *q, float deg);
int distance_sqrt(Point *p1, Point *p2);

/* render functions */
int render_background(Grid *map, Player *player,
		Screen *screen, SDL_Renderer *renderer);
int render_wall(int column, Point vert, Point hor, Ray ray,
		Player *player, SDL_Renderer *renderer);
void render_floor(int i, int wall_height,
		SDL_Renderer *renderer, Screen *screen);
void render_sky(int i, int wall_height,
		SDL_Renderer *renderer, Screen *screen);
int render_map(Grid *map, Player player,
		SDL_Renderer *renderer, Screen screen, int **local);
int render_player_view(Player player, SDL_Renderer *renderer,
		Screen screen);
int render_grid(Grid *map, SDL_Renderer *renderer,
		SDL_Rect rect, int **local);

/* movement functions */
void movement_logic(float dt, Gamepad keys, Player *player, Grid *map);
void move_vert(Player *player, float speed, Grid *map);
void move_hor(Player *player, float speed, Grid *map);


/* drawing functions */
void drawCircle(SDL_Renderer *renderer, int centerX, int centerY, int radius);
void draw_radial_cone(SDL_Renderer *renderer, int center_x, int center_y,
		float cone_angle_deg, float length, int num_lines, float dir_deg);

/* misc functions */
void free2DArray(int **array, int rows);
int **create2DArray(int rows, int cols);
void print2DArray(int **array, int rows, int cols);
void normalize(Player *player, Player *prev, float speed);
void mirrorArray(int **arr, int rows, int cols);

/* cleanup functions */
void cleanup(Resources resources);
void cleanup_grid(Grid *grid);

#endif
