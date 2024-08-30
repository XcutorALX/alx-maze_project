#include <SDL2/SDL.h>
#include "maze.h"
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

/**
 * main - entry point for the game
 *
 * Return: 0
 **/
int main(void)
{
	SDL_Window *window = NULL;
	SDL_Surface *screenSurface = NULL;
	SDL_Renderer *renderer;
	SDL_Event event;
	Screen screen;
	Player player;
	Grid *map;
	Point pos;
	int height, width, **arr, running, rot_speed;

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        	return (1);
	}

	screen.width = 640;
	screen.height = 480;
	if  (create_window(&window, &screen) == 1)
	{
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		return (1);
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	
	if (renderer == NULL) 
	{

		SDL_DestroyWindow(window);
		printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
		SDL_Quit();
		return 1;
	}

	height = 0;
	width = 0;
	arr = loadMap(&height, &width);
	map = create_map(arr, height, width);

	player.fov = 60;
	player.height = 32;
	player.dir = 270;
	pos.x = 96;
	pos.y = 96;
	player.pos = pos;
	player.speed = 4;
	rot_speed = 5;

	screenSurface = SDL_GetWindowSurface( window );
//	render_background(map, &player, &screen, renderer);
//	SDL_RenderPresent(renderer);
	
	running = 1;
	while (running)
	{
	while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0; // Exit the loop if the window is closed
            }

            if (event.type == SDL_KEYDOWN) {
		    switch (event.key.keysym.sym) {
			    case SDLK_w:
				    move_vert(&player, player.speed, map);
				    break;
			    case SDLK_a:
				    move_hor(&player, -1 * player.speed, map);
				    break;
			    case SDLK_s:
				    move_vert(&player, -1 * player.speed, map);
				    break;
			    case SDLK_d:
				    move_hor(&player, player.speed, map);
				    break;
			    case SDLK_LEFT:
				    player.dir -= rot_speed;
				    break;
			    case SDLK_RIGHT:
				    player.dir += rot_speed;
				    break;
			    default:
				    printf("None\n");
				    break;
            		}
	    }

	    if (player.dir >= 360)
		    player.dir = fmod(player.dir, 360);
	    else if(player.dir < 0)
		    player.dir += 360;

	    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	    SDL_RenderClear(renderer);
	    render_background(map, &player, &screen, renderer);
	    SDL_RenderPresent(renderer);		    
	}
	}

//	SDL_Event e; int quit = 0; while( !quit ){ while( SDL_PollEvent( &e ) ){ if( e.type == SDL_QUIT ) quit = 1; } }

	SDL_DestroyWindow( window );
	SDL_Quit();
	return (0);
}
