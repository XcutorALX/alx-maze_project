#include <stdio.h>
#include "maze.h"
#include "struct.h"

/**
 * print2DArray - this function prints a 2d array of integers
 *
 * @rows: the number of rows in the arrray
 * @cols: the number of columns in the array
 * @array: the array to be printed
 *
 * Return: void
 */
void print2DArray(int **array, int rows, int cols)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
			printf("%d ", array[i][j]);
		printf("\n");
	}
}

/**
 * draw_radial_cone - draws a cone in the direction
 * of the angle specified
 *
 * @renderer: SDL_Renderer struct
 * @center_x: x value of the center/point of origin of the cone
 * @center_y: y value of the center/point of origin of the cone
 * @cone_angle_deg: the internal angle of the cone
 * @length: the length of the radius
 * @num_lines: the number of lines the cone should be divided into
 * @dir_deg: the direction the cone faces relative to the x axis
 *
 * Return: void
 */
void draw_radial_cone(SDL_Renderer *renderer, int center_x, int center_y,
		float cone_angle_deg, float length, int num_lines,
		float dir_deg)
{
	float angle_step, angle, angle_rad;
	int end_x, end_y;

	angle_step = cone_angle_deg / (num_lines - 1);

	for (int i = 0; i < num_lines; ++i)
	{
		angle = dir_deg + i * angle_step;
		angle_rad = angle * M_PI / 180.0;
		end_x = center_x + (int)(length * cos(angle_rad));
		end_y = center_y - (int)(length * sin(angle_rad));
		SDL_RenderDrawLine(renderer, center_x, center_y, end_x, end_y);
	}
}
