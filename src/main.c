#include <stdio.h>
#include <stdlib.h>
#include "mario_bros.h"

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

int handle_event(SDL_Event event, struct key* key)
{
	if (SDL_WaitEvent(&event)) {
		switch (event.type)
		{
		case SDL_MOUSEBUTTONDOWN:
			key->mouse[event.button.button] = 1;
			break;
		case SDL_MOUSEBUTTONUP:
			key->mouse[event.button.button] = 0;
			break;
		case SDL_MOUSEMOTION:
			key->x = event.motion.x;
			key->y = event.motion.y;
			break;
		case SDL_KEYDOWN:
			if (key->keycode[event.key.keysym.scancode] == 0)
				key->keycode[event.key.keysym.scancode] = 1;
			break;
		case SDL_KEYUP:
			key->keycode[event.key.keysym.scancode] = 0;
			break;
		case SDL_QUIT:
			return(1);
			break;
		default:
			break;
		}
	}
	return (0);
}

void draw_tile(SDL_Renderer* renderer, struct sprite text, int** map)
{
	SDL_Rect pos; pos.x = 0, pos.y = 0, pos.w = TILE_SIZE, pos.h = TILE_SIZE;
	int i = 0, j = 0;

	while (i != N_HEIGHT_TILE) {
		while (j != N_WIDTH_TILE) {
			if (map[i][j] == 1)
				SDL_RenderCopy(renderer, text.ground, NULL ,&pos);
			pos.x += TILE_SIZE;
			j++;
		}
		pos.x = 0;
		j = 0;
		pos.y += TILE_SIZE;
		i++;
	}
}

int check_cmd(SDL_Window* window, SDL_Renderer* renderer, struct key* key, int** map)
{
	int ret = 0;

	if (key->keycode[SDL_SCANCODE_LALT] == 1 && key->keycode[SDL_SCANCODE_RETURN] == 1) {
		set_fullscreen(window, renderer);
		key->keycode[SDL_SCANCODE_RETURN] = 2;
	}
	else if (key->keycode[SDL_SCANCODE_LCTRL] == 1 && key->keycode[SDL_SCANCODE_S] == 1) {
		ret = save_map(map);
		key->keycode[SDL_SCANCODE_S] = 2;
	}
	else if (key->keycode[SDL_SCANCODE_ESCAPE] == 1) {
		ret = -1;
	}
	
	return (ret);
}

int load_texture(SDL_Renderer* renderer, struct sprite* text)
{
	SDL_Surface* surface = NULL;

	surface = IMG_Load("img/ground.png");
	text->ground = SDL_CreateTextureFromSurface(renderer, surface);
	return (0);
}

int init_sdl(SDL_Window** window)
{
	if (SDL_InitSubSystem(SDL_INIT_VIDEO) != 0) {
		fprintf(stderr, "%s\n", SDL_GetError());
		return (-1);
	}
	*window = SDL_CreateWindow("Mario Bros", 50, 50, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	if(!window) {
		fprintf(stderr, "%s\n", SDL_GetError());
		return (-1);
	}
	return (0);
}

int check_env(char** env)
{
	if (env[0] == NULL)
		return (-1);
	return (0);
}

int main(int argc, char** argv)
{
	int ret = 0;
	int** map = NULL;
	int actualTime = 0, prevTime = 0;
	struct sprite text = {NULL};
	struct key key = {0, 0, {0}, {0}};

	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_Event event;

	if (argc != 1 || argv[1] != NULL)
		return (-1);

	map = load_map();
	if (map == NULL) {
		fprintf(stderr, "Error loading map file\n");
		return (-1);
	}

	if (init_sdl(&window) != 0)
		return (-1);
	renderer = SDL_CreateRenderer(window, -1, 0);
	load_texture(renderer, &text);

	SDL_Surface *s;
	s = SDL_CreateRGBSurface(0, WIDTH, HEIGHT, 32, 0, 0, 0, 0);
	SDL_FillRect(s, NULL, SDL_MapRGB(s->format, 0, 255, 0));
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, s);

	while ((ret = handle_event(event, &key)) != 1) {
		actualTime = SDL_GetTicks();
		if (actualTime - prevTime >= FPS) {
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			SDL_RenderClear(renderer);

			edit_map(map, key);

			if (check_cmd(window, renderer, &key, map) < 0)
				return (-1);

			SDL_RenderCopy(renderer, texture, NULL, NULL);

			draw_tile(renderer, text, map);

			SDL_RenderPresent(renderer);
			prevTime = actualTime;
		}
		else {
			SDL_Delay(FPS - (actualTime - prevTime));
		}
	}

	SDL_DestroyWindow(window);
	SDL_Quit();
	return (0);
}
