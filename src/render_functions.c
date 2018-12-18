#include "mario_bros.h"

void draw_tile(t_game game)
{
	SDL_Rect pos; pos.x = 0, pos.y = 0, pos.w = TILE_SIZE, pos.h = TILE_SIZE;
	int i = 0, j = 0;

	while (i != N_HEIGHT_TILE) {
		while (j != N_WIDTH_TILE) {
			if (game.map[i][j] == 1)
				SDL_RenderCopy(game.renderer, game.sprite.ground, NULL ,&pos);
			pos.x += TILE_SIZE;
			j++;
		}
		pos.x = 0;
		j = 0;
		pos.y += TILE_SIZE;
		i++;
	}
}

void set_fullscreen(SDL_Window* window, SDL_Renderer* renderer)
{
	int flags = SDL_GetWindowFlags(window);
	int IsFullscreen = (flags & SDL_WINDOW_FULLSCREEN) ? 1 : 0;

	if (IsFullscreen == 0) {
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
		SDL_RenderSetLogicalSize(renderer, WIDTH, HEIGHT);
	}
	else {
		SDL_SetWindowFullscreen(window, 0);
	}
}
