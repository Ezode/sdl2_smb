#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "mario_bros.h"

int** malloc_map(void)
{
	int i = 0, j = 0;
	int **map = NULL;

	map = malloc(sizeof(int*) * N_HEIGHT_TILE);
	if (map == NULL)
		return (NULL);
	while (i != N_HEIGHT_TILE) {
		map[i] = malloc(sizeof(int) * N_WIDTH_TILE);
		if (map[i] == NULL)
			return (NULL);
		while (j != N_WIDTH_TILE) {
			map[i][j] = 0;
			j++;
		}
		i++;
		j = 0;
	}
	return (map);
}

char* get_str(void)
{
	long size = 0;
	char* str = NULL;
	FILE* file = NULL;

	file = fopen("./map.txt", "r");
	if (file == NULL)
		return (NULL);
	fseek(file, 0, SEEK_END);
	size = ftell(file);
	fseek(file, 0, SEEK_SET);
	str = malloc(sizeof(char) * (size + 1));
	if (str == NULL)
		return (NULL);
	fread(str, size, 1, file);
	str[size] = '\0';
	fclose(file);
	return (str);
}

int load_map(t_game* game)
{
	int size = 0;
	char* str = NULL;
	
	if ((str = get_str()) == NULL)
		return (-1);
	size = strlen(str);

	for (int i = 0, j = 0, k = 0; i != N_HEIGHT_TILE; i++) {
		for (j = 0; j != N_WIDTH_TILE; j++) {
			if (k == size)
				game->map[i][j] = 0;
			else {
				game->map[i][j] = str[k] - 48;
				k++;
			}
		}
	}
	free(str);
	return (0);
}

int edit_map(t_game *game)
{
	if (game->key.mouse[SDL_BUTTON_RIGHT] == 1) {
		if (game->key.x >= 0 && game->key.x <= WIDTH && game->key.y >= 0 && game->key.y <= HEIGHT) {
			game->map[game->key.y / TILE_SIZE][game->key.x / TILE_SIZE] = 0;
		}
	}
	else if (game->key.mouse[SDL_BUTTON_LEFT] == 1) {
		if (game->key.x >= 0 && game->key.x <= WIDTH && game->key.y >= 0 && game->key.y <= HEIGHT) {
			game->map[game->key.y / TILE_SIZE][game->key.x / TILE_SIZE] = 1;
		}
	}
	return (0);
}

int save_map(int** map)
{
	int i = 0, j = 0;
	char str[1] = "0";
	FILE* file = NULL;

	file = fopen("./map.txt", "w");
	if (file == NULL)
		return (-1);
	while (i != N_HEIGHT_TILE) {
		while (j != N_WIDTH_TILE) {
			str[0] = map[i][j] + 48;
			fwrite(str, 1, 1, file);
			j++;
		}
		j = 0;
		i++;
	}
	fclose(file);
	return (0);
}
