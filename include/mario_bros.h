#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define N_WIDTH_TILE 16
#define N_HEIGHT_TILE 16
#define TILE_SIZE 32
#define WIDTH N_WIDTH_TILE * TILE_SIZE
#define HEIGHT N_HEIGHT_TILE * TILE_SIZE
#define FRAME_RATE 60
#define FPS 1000 / FRAME_RATE

struct sprite {
	SDL_Texture* ground;
};

struct key {
	int x;
	int y;
	int mouse[5];
	int keycode[285];
};

int save_map(int** map);
int edit_map(int** map, struct key key);
int** load_map();
