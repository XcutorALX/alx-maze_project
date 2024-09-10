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
 * localMap - edits a two dimensional array to reflect player vicinity
 *
 * @player: the player struct
 * @map: the map of the game
 * @local_map: the local map
 *
 * Return: 1 for success and 0 for failure
 */

int localMap(Player player, Grid *map, int **local)
{
	int x_start, x_index, y_index,
	    player_x, player_y, i;
	Cell **cells = map->cells;

	player_x = floor(player.pos.x / 64);
	player_y = floor(player.pos.y / 64);
	y_index = player_y - 3;
	x_index = player_x - 6;
	x_start = x_index;
	i = 0;

	while (y_index < 0)
	{
		for (x_index = x_start; x_index <= player_x + 6; x_index++)
			local[i][x_index - x_start] = 0;
		y_index++;
		i++;
	}

	for (; y_index <= player_y + 3; y_index++)
	{
		if (y_index >= map->height)
		{
			for (x_index = x_start; x_index <= player_x + 6; x_index++)
				local[y_index - player_y + 3][x_index - x_start] = 0;
		}
		else
		{
			for (x_index = x_start; x_index <= player_x + 6; x_index++)
			{
				if (x_index < 0 || x_index >= map->width)
					local[y_index - player_y + 3][x_index - x_start] = 0;
				else
					local[y_index - player_y + 3][x_index - x_start] = cells[y_index][x_index].type;
			}
		}
	}
	mirrorArray(local, 7, 13);

	return (1);
}

void mirrorArray(int **arr, int rows, int cols)
{
	int start, end, temp, i;

	for (i = 0; i < rows; i++)
	{
		start = 0;
		end = cols - 1;

		while (start < end)
		{
			temp = arr[i][start];
			arr[i][start] = arr[i][end];
			arr[i][end] = temp;
		
			start++;
			end--;
		}
	}
}

/**
 * create2DArray - this function helps create a 2d array
 *
 * @rows: the size of the rows
 * @cols: the size of the columns
 *
 * Return: a pointer to the allocated array
 */
int **create2DArray(int rows, int cols)
{
	int **array;
	array = malloc(rows * sizeof(int*));
	if (array == NULL)
	{
        	printf("Memory allocation failed for rows.\n");
        	return NULL;
	}

	for (int i = 0; i < rows; i++)
	{
		array[i] = (int*)malloc(cols * sizeof(int));
		if (array[i] == NULL)
		{
			printf("Memory allocation failed for row %d.\n", i);
			for (int j = 0; j < i; j++)
				free(array[j]);
			free(array);
			return (NULL);
		}
	}

	return (array);
}

/**
 * free2DArray - this function frees a two dimensional array
 *
 * @array: the array
 * @rows: the size of the array
 *
 * Return: void
 */
void free2DArray(int** array, int rows)
{
	int i;

	for (int i = 0; i < rows; i++)
	{
		free(array[i]);
	}
	free(array);
}
