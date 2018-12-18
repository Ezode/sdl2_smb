#include <stdio.h>
#include <stdlib.h>
#include "mario_bros.h"

int check_cmd(t_game *game)
{
	int ret = 0;

	if (game->key.keycode[SDL_SCANCODE_LALT] == 1 && game->key.keycode[SDL_SCANCODE_RETURN] == 1) {
		set_fullscreen(game->window, game->renderer);
		game->key.keycode[SDL_SCANCODE_RETURN] = 2;
	}
	else if (game->editing == 1 && game->key.keycode[SDL_SCANCODE_LCTRL] == 1 && game->key.keycode[SDL_SCANCODE_S] == 1) {
		ret = save_map(game->map);
		game->key.keycode[SDL_SCANCODE_S] = 2;
	}
	else if (game->key.keycode[SDL_SCANCODE_ESCAPE] == 1) {
		ret = -1;
	}
	return (ret);
}

int handle_event(SDL_Event event, struct s_key* key)
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
			if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
				return (1);
			else if (key->keycode[event.key.keysym.scancode] == 0)
				key->keycode[event.key.keysym.scancode] = 1;
			break;
		case SDL_KEYUP:
			key->keycode[event.key.keysym.scancode] = 0;
			break;
		case SDL_QUIT:
			return (2);
			break;
		default:
			break;
		}
	}
	return (0);
}

int init_sdl(t_game *game)
{
	if (SDL_InitSubSystem(SDL_INIT_VIDEO) != 0) {
		fprintf(stderr, "%s\n", SDL_GetError());
		return (-1);
	}
	game->window = SDL_CreateWindow("Mario Bros", 50, 50, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	if(!game->window) {
		fprintf(stderr, "%s\n", SDL_GetError());
		return (-1);
	}
	return (0);
}

int editor(t_game *game)
{
	int ret = 0;
	SDL_Surface *surface = NULL;
	SDL_Texture* background = NULL;

	if (load_map(game->map) != 0)
		return (-1);

	surface = SDL_CreateRGBSurface(0, WIDTH, HEIGHT, 32, 0, 0, 0, 0);
	SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0, 255, 0));
	background = SDL_CreateTextureFromSurface(game->renderer, surface);

	while ((ret = handle_event(game->event, &game->key)) == 0) {
		SDL_SetRenderDrawColor(game->renderer, 0, 0, 255, 255);
		SDL_RenderClear(game->renderer);

		edit_map(game);

		if (check_cmd(game) < 0)
			return (-1);

		SDL_RenderCopy(game->renderer, background, NULL, NULL);

		draw_tile(*game);

		SDL_RenderPresent(game->renderer);
	}
	game->editing = 0;
	return (ret);
}

int game_loop(t_game *game)
{
	while (1) {

	}
	return (0);
}

int main_menu(t_game* game)
{
	int ret = 0;

	while (handle_event(game->event, &game->key) == 0) {
		if (game->key.keycode[SDL_SCANCODE_1] == 1) {
			game->editing = 1;
			ret = editor(game);
		}
		else if (game->key.keycode[SDL_SCANCODE_2] == 1) {
			game->playing = 1;
			ret = game_loop(game);
		}
		if (ret == 2)
			break;
		check_cmd(game);
		SDL_SetRenderDrawColor(game->renderer, 255, 0, 0, 255);
		SDL_RenderClear(game->renderer);
		SDL_RenderPresent(game->renderer);
	}
	return (ret);
}

int load_texture(t_game *game)
{
	SDL_Surface* surface = NULL;

	surface = IMG_Load("img/ground.png");
	game->sprite.ground = SDL_CreateTextureFromSurface(game->renderer, surface);
	return (0);
}

int main(int argc, char** argv)
{
	int ret = 0;
	struct s_game game = {NULL, NULL, NULL, {NULL}, {0, 0, {0}, {0}}, 0, 0};

	if (init_sdl(&game) != 0)
		return (-1);
	game.renderer = SDL_CreateRenderer(game.window, -1, 0);

	game.map = malloc_map();
	if (game.map == NULL)
		return (-1);
	if (load_texture(&game) != 0)
		return (-1);

	ret = main_menu(&game);

	SDL_DestroyWindow(game.window);
	SDL_Quit();
	return (ret);
}
