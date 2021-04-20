#include <Windows.h>
#include <SDL.h>

int HEIGHT = 900;
int WIDTH = 1440;
long double min = -2.84;
long double max = 1.0;
long double zoom = 1.5;
int MAX_ITERATIONS = 200;

long double map(long double x, long double in_min, long double in_max, long double out_min, long double out_max) {
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int main(int argc, char* argv[]) {
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* wind;
	SDL_Renderer* rend;
	SDL_Event event;

	int wigth = 1440;
	int height = 900;
	int count = 0;

	SDL_CreateWindowAndRenderer(wigth, height, 0, &wind, &rend);
	SDL_RenderSetLogicalSize(rend, WIDTH, HEIGHT);
	
	while (true) {
		if (GetKeyState('W') & 0x8000) {
			max -= 0.1 * zoom;
			min += 0.15 * zoom;
			zoom *= 0.9349;
			MAX_ITERATIONS += 5;
			if (count > 30) {
				MAX_ITERATIONS *= 1.02;
			}
		}
		if (GetKeyState('S') & 0x8000) {
			max += 0.1 * zoom;
			min -= 0.15 * zoom;
			zoom /= 0.9349;
			MAX_ITERATIONS -= 5;
			if (count > 30) {
				MAX_ITERATIONS /= 1.02;
			}
		}
		
		SDL_RenderPresent(rend);

		for (int i = 0; i < WIDTH; i++) {
			if (SDL_PollEvent(&event) && event.type == SDL_QUIT) {
				return 0;
			}
			if (GetKeyState('X') & 0x8000) {
				return 0;
			}

			for (int j = 0; j < HEIGHT; j++) {
				long double x = map(i, 0, WIDTH, min, max);
				long double y = map(j, 0, HEIGHT, min, max);
				long double xi = x;
				long double yi = y;
				int n = 0;

				for (int k = 0; k < MAX_ITERATIONS; k++) {
					long double x1 = x * x - y * y;
					long double y1 = 2 * x * y;
					x = x1 + xi;
					y = y1 + yi;
					if (x + y > 2) {
						break;
					}
					n++;
				}

				int color = map(n, 0, MAX_ITERATIONS, 0, 255);
				if ((n == MAX_ITERATIONS) || color < 20) {
					color = 0;
				}

				int r = map(color * color, 0, 255 * 255, 0, 255);
				int g = color;
				int b = map(sqrt(color), 0, sqrt(255), 0, 255);
				SDL_SetRenderDrawColor(rend, r, g, b, 255);
				SDL_RenderDrawPoint(rend, i, j);
			}
		}
		count++;
	}
	return 0;
}