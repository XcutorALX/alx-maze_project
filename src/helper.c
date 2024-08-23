#include "maze.h"
#include <math.h>
#include <stdlib.h>

/**
 * check_collision_vert - this function checks vertical collision of a ray with a grid
 *
 * @ray: the ray to be checked
 * @map: the map
 *
 * Return: 1 for collision 0 for no collision
 */
int check_collision_vert(Grid *grid, Ray *ray)
{
	Point vert;
	Cell **map = grid->cells;
	int xa, ya, collision;

	if (ray->dir > 90 && ray->dir < 270 )
	{
		vert.x = floor(ray->pos.x/64) * (64) - 1;
		xa = -64;
	}
	else
	{
		vert.x = floor(ray->pos.x/64) * (64) + 64;
		xa = 64;
	}

	vert.y = ray->pos.y + (ray->pos.x - vert.x) * tan(ray->dir * (M_PI / 180.0));
	ya = 64 * tan(ray->dir * (M_PI / 180.0));
	ya = abs(ya);
	ya = (ray->dir < 180) ? -1 * ya : ya;

	collision = 0;
	while (vert.x / 64 < grid->width && vert.y / 64 < grid->height && collision == 0)
	{
		printf("%d, %d\n", vert.x, vert.y);
		if ((&(map[vert.y / 64 ][vert.x / 64]))->type == 1)
			collision = 1;
		else
		{
			vert.x += xa;
			vert.y += ya;
		}
	}

	printf("%d, %d\n", vert.x / 64 , vert.y / 64);
	return (1);
}

/**
 * check_collision_hor - this function checks horizontal collision of a ray with a grid
 *
 * @ray: the ray
 * @map: the map
 *
 * Return: pointer to the collision
 */
Point *check_collision_hor(Grid *grid, Ray *ray)
{
	Point hor;
	Cell **map = grid->cells;
	int xa, ya, collision;

	if (ray->dir < 180)
	{
		hor.y = floor(ray->pos.y/64) * (64) - 1;
		ya = -64;
	}
	else
	{
		hor.y = floor(ray->pos.y/64) * (64) + 64;
		ya = 64;
	}

	hor.x = ray->pos.x + (ray->pos.y - hor.y) / tan(ray->dir * (M_PI / 180.0));
	xa = 64 / tan(ray->dir * (M_PI / 180.0));
	xa = abs(xa);
	xa = (ray->dir > 180  && ray->dir < 270) ? -1 * xa : xa;

	collision = 0;
	while (hor.x / 64 < grid->width && hor.y / 64 < grid->height && collision == 0)
	{
		printf("%d, %d\n", hor.x, hor.y);
		if ((&(map[hor.y / 64 ][hor.x / 64]))->type == 1)
			collision = 1;
		else
		{
			hor.x += xa;
			hor.y += ya;
		}
	}

	printf("%d, %d\n", hor.x / 64 , hor.y / 64);
	return (1);
}


/**
 * create_map - creates a map from a 2d array of 1s and 0s using the Grid struct
 *
 * @arr: the array to be converted into a grid map
 *
 * Return: the Grid struct of maps
 */
Grid *create_map(int **arr, int height , int width)
{
	int i, j;
	Grid *map;

	map = malloc(sizeof(Grid));

	if (map == NULL) {
		fprintf(stderr, "Memory allocation failed\n");
		return NULL;
	}

	map->cells = malloc(height * sizeof(Cell *));
	if (map->cells == NULL) 
	{
		fprintf(stderr, "Memory allocation failed for row pointers\n");
		free(map); // Clean up previously allocated memory
		return NULL;
	}

	map->height = height;
	map->width = width;

	for (i = 0; i < height; i++)
	{
		map->cells[i] = malloc(width * sizeof(Cell));
		if (map->cells[i] == NULL) 
		{
			fprintf(stderr, "Memory allocation failed for row %d\n", i);
			for (j = 0; j < i; j++)
			{
				free(map->cells[j]);
			}
            		free(map->cells);
            		free(map);
            		return NULL;
        	}

		for (j = 0; j < width; j++)
		{
			map->cells[i][j].type = arr[i][j];
			map->cells[i][j].height = 64;
			map->cells[i][j].coord.y = i;
			map->cells[i][j].coord.x = j;
		}
	}

	return (map);
}

/**
 * distance - this function calculates the distance between two points
 *
 * @p: the first point
 * @q: the second point
 * @deg: the angle between the points
 *
 * Return: the distance between the points
 */
int distance(Point *p, Point *q, float deg)
{
	int value;

	value = (p->x - q->x) / cos(deg * M_PI / 180);

	return (abs(value));
}
