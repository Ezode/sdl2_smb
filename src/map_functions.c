#include <stdlib.h>
#include <stdio.h>
#include "mario_bros.h"

int** malloc_map(char* str, long size)
{
	int i = 0, j = 0, k = 0;
	int **map = NULL;

	map = malloc(sizeof(int*) * N_HEIGHT_TILE);
	if (map == NULL)
		return (NULL);
	while (i != N_HEIGHT_TILE) {
		map[i] = malloc(sizeof(int) * N_WIDTH_TILE);
		if (map[i] == NULL)
			return (NULL);
		while (j != N_WIDTH_TILE) {
			if (k == size) {
				map[i][j] = 0;
				j++;
			}
			else if (str[k] != '\n') {
				map[i][j] = str[k] - 48;
				k++;
				j++;
			}
			else
				k++;
		}
		j = 0;
		i++;
	}
	return (map);
}

int** load_map()
{
	FILE* file = NULL;
	long size = 0;
	char* str = NULL;
	int** map = NULL;

	file = fopen("./map.txt", "r");
	if (file == NULL)
		return (NULL);
	fseek(file, 0, SEEK_END);
	size = ftell(file);
	fseek(file, 0, SEEK_SET);
	str = malloc(sizeof(char) * (size + 1));
	fread(str, size, 1, file);
	str[size] = '\0';
	map = malloc_map(str, size);
	return (map);
}

int edit_map(int** map, struct key key)
{
	if (key.mouse[SDL_BUTTON_RIGHT] == 1) {
		if (key.x >= 0 && key.x <= WIDTH && key.y >= 0 && key.y <= HEIGHT) {
			map[key.y / TILE_SIZE][key.x / TILE_SIZE] = 0;
		}
	}
	else if (key.mouse[SDL_BUTTON_LEFT] == 1) {
		if (key.x >= 0 && key.x <= WIDTH && key.y >= 0 && key.y <= HEIGHT) {
			map[key.y / TILE_SIZE][key.x / TILE_SIZE] = 1;
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
	return (0);
}
