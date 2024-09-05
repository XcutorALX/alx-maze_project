#include "maze.h"

/**
 * saveMap - saves the map to a file
 *
 * @map: a pointer to the map
 *
 * Return: 0 om success and 1 on failure
 */
int saveMap(Grid *map)
{
	char *filename = "maze.map";
	FILE *file = fopen(filename, "w");

	if (file == NULL)
	{
		printf("Error opening file!\n");
		return (1);
	}

	fprintf(file, "%d\n", map->height);
	fprintf(file, "%d\n", map->width);
    
	for (int i = 0; i < map->height; i++)
	{	
		for (int j = 0; j < map->width; j++)
		{
			fprintf(file, "%d", (map->cells)[i][j].type);
		}
		fprintf(file, "\n");
	}

	fclose(file);
	return (0);
}

/**
 * readMap - reads a map from a file
 *
 */

int **loadMap(int *height, int *width)
{
	char *filename = "maze.map";
	FILE *file = fopen(filename, "r");
	
	if (file == NULL)
	{
		printf("Error opening file!\n");
		return NULL;
	}
	
	fscanf(file, "%d", height);
	fscanf(file, "%d", width);

	int **map = (int **)malloc(*height * sizeof(int *));
	for (int i = 0; i < *height; i++)
		map[i] = (int *)malloc(*width * sizeof(int));

	for (int i = 0; i < *height; i++)
	{
		for (int j = 0; j < *width; j++)
			fscanf(file, "%1d", &map[i][j]);
        }

    fclose(file);
    return (map);
}

/**
 * localMap - creates a two dimensional array to simulate the
 * 	local map around the player
 *
 * @player: the player struct
 * @map: the map of the game
 *
 * Return: a two dimensional array
 */
int **localMap(Player player, Grid *map)
{
	int x_index, y_index;
	
	x_index = floor(player.pos.x / 64);
	y_index = floor(player.pos.y / 64);


	return (NULL);
}
