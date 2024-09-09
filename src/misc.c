#include <stdio.h>
#include "maze.h"

void print2DArray(int** array, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", array[i][j]);
        }
        printf("\n");
    }
}

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
		angle_rad = angle * M_PI /180.0;
		end_x = center_x + (int)(length * cos(angle_rad));
		end_y = center_y - (int)(length * sin(angle_rad));
		SDL_RenderDrawLine(renderer, center_x, center_y, end_x, end_y);
	}
}
