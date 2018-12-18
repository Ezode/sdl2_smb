#ifndef SMB
#define SMB

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define N_WIDTH_TILE 16
#define N_HEIGHT_TILE 16
#define TILE_SIZE 32
#define WIDTH N_WIDTH_TILE * TILE_SIZE
#define HEIGHT N_HEIGHT_TILE * TILE_SIZE
#define FRAME_RATE 60
#define FPS 1000 / FRAME_RATE

typedef struct s_sprite
{
	SDL_Texture* ground;
} t_sprite;

struct s_key
{
	int x;
	int y;
	int mouse[5];
	int keycode[285];
} t_key;

typedef struct s_game
{
	int** map;

	SDL_Window* window;
	SDL_Renderer* renderer;

	struct s_sprite sprite;
	struct s_key key;

	int playing;
	int editing;

	SDL_Event event;

} t_game;

int** malloc_map(void);
int load_map(t_game* game);
int save_map(int** map);
int edit_map(t_game* game);
void draw_tile(t_game game);
void set_fullscreen(SDL_Window* window, SDL_Renderer* renderer);

#endif
