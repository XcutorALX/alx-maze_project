#include <SDL2/SDL.h>
#include <math.h>

void drawCircle(SDL_Renderer *renderer, int centerX, int centerY, int radius)
{
	int w, h, dx, dy;

	for (w = 0; w < radius * 2; w++)
	{
		for (h = 0; h < radius * 2; h++)
		{
			dx = radius - w;
			dy = radius - h;
			if ((dx*dx + dy*dy) <= (radius * radius))
				SDL_RenderDrawPoint(renderer, centerX + dx, centerY + dy);
		}
	}
}  
