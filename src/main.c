#include <SDL2/SDL.h>
#include "maze.h"
#include "struct.h"
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define DEFAULT_RESOURCE (Resources) {NULL, NULL, NULL, NULL, NULL}

/**
 * main - entry point for the game
 *
 * Return: 0
 **/
int main(void)
{
	Resources resources;
	Screen screen;
	Player player;
	int height, width, **arr, running, rot_speed;

        resources = DEFAULT_RESOURCE;
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return (1);
	}
	screen.width = 640;
	screen.height = 480;
	screen.map_height = floor(0.33 * screen.height);
	screen.map_width = floor(0.33 * screen.width);
	screen.map_block_size = floor(screen.map_height / 7);
	if  (create_window(&(resources.window), &screen) == 1)
	{
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		return (1);
	}
	resources.renderer = SDL_CreateRenderer(resources.window, -1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (resources.renderer == NULL)
	{
		cleanup(resources);
		printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
		return (1);
	}
	if (init_game(&player, &(resources.map), &(resources.local_map)) == 1)
	{
		cleanup(resources);
		printf("Game could not be initiated! initiation error");
		return (1);
	}
	game_loop(resources.map, resources.renderer, player, screen, resources.local_map);
	cleanup(resources);
	return (0);
}


/**
 * init_game - this function sets up the game
 *
 * @player: the player instance
 * @map: the map of the game
 * @local_map: the local map of the players
 * immediate surrounding
 *
 * Return: 1 on success and 0 on failure
 */
int init_game(Player *player, Grid **map, int ***local_map)
{
	int height, width, **arr;

	height = 0;
	width = 0;

	arr = loadMap(&height, &width);
	if (arr == NULL)
		return (1);
	(*map) = create_map(arr, height, width);
	if (*map == NULL)
		return (1);
	player->fov = 60;
	player->height = 32;
	player->dir = 270;
	player->pos.x = 96;
	player->pos.y = 96;
	player->speed = 200;
	player->rot_speed = 200;

	free2DArray(arr, height);

	*local_map = create2DArray(7, 13);
	if (*local_map == NULL)
		return (1);
	return (0);
}

/**
 * game_loop - this function handles the game loop
 *
 * @map: the map of the game
 * @renderer: an SLD_Renderer instance
 * @player: the player instance
 * @screen: the screen instance
 * @local: the local map of the players
 * immediate surrounding
 *
 * Return: 0 on success and 1 on failure
 */
int game_loop(Grid *map, SDL_Renderer *renderer,
		Player player, Screen screen, int **local)
{
	int running;
	SDL_Event event;
	Gamepad keys;
	Uint32 last_time, current_time;
	float dt, adj_speed, adj_rot, temp;
	Player prev;

	keys.left = 0;
	keys.right = 0;
	keys.forward = 0;
	keys.backward = 0;
	keys.rot_left = 0;
	keys.rot_right = 0;
	running = 1;
	last_time = SDL_GetTicks();
	while (running)
	{
		current_time = SDL_GetTicks();
		dt = (current_time - last_time) / 1000.0f;
		last_time = current_time;
		adj_speed = dt * player.speed;
		adj_rot = dt * player.rot_speed;
		prev.pos.x = player.pos.x;
		prev.pos.y = player.pos.y;
		while (SDL_PollEvent(&event) && running == 1)
		{
			if (event_handler(event, &player, map, &keys) == 0)
				running = 0;
		}

		if (running == 1)
		{
			movement_logic(dt, keys, &player, map);
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
			SDL_RenderClear(renderer);
			render_background(map, &player, &screen, renderer);
			render_map(map, player, renderer, screen, local);
			SDL_RenderPresent(renderer);
		}
	}
	return (0);
}

/**
 * event_handler - this function takes care of event handling process
 *
 * @event: an SDL_Event instance
 * @player: the player instance
 * @map: the map of the game
 * @keys: the current status of all game keys
 *
 * Return: 1 to continue and 0 to quit
 */
int event_handler(SDL_Event event, Player *player, Grid *map, Gamepad *keys)
{
	int status, result;

	switch (event.type)
	{
		case SDL_QUIT:
			return (0);
			break;
		case SDL_KEYDOWN:
			status = 1;
			break;
		case SDL_KEYUP:
			status = 0;
			break;
		case SDL_WINDOWEVENT:
			result = event.window.event != SDL_WINDOWEVENT_CLOSE;
			break;
	}

	handle_key_event(event.key.keysym.sym, keys, status);

	return (result);
}
