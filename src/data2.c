#include <stdlib.h>
#include "maze.h"

/**
 * free2DArray - this function frees a two dimensional array
 *
 * @array: the array
 * @rows: the size of the array
 *
 * Return: void
 */
void free2DArray(int **array, int rows)
{
	int i;

	for (i = 0; i < rows; i++)
	{
		free(array[i]);
	}
	free(array);
}
