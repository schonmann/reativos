#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include <math.h>

#define true 1
#define false 0

#define W_WIDTH 640		//Window width.
#define W_HEIGHT 480	//Window height.
#define W_NAME "Joguinho"

#define ASSET_PLAYER "path/pra/imagem/do/player.png"

/* Type signatures */

typedef struct color Color;
typedef struct game_object GameObject;

/* Function signatures. */

SDL_Window *createWindow();
SDL_Renderer *createRenderer(SDL_Window *window);
void batchDraw(SDL_Renderer *renderer);
void onError(int code);
void endProgram(SDL_Renderer *renderer, SDL_Window *window);
void mainLoop(SDL_Renderer *renderer, SDL_Window *window);
int heardQuitGameEvent();
int collidesWith(SDL_Rect rect, int x, int y);
SDL_Texture * loadTexture(SDL_Renderer * renderer, char *name);

/* Struct to represent a color. */

typedef struct color
{
	int r;
	int g;
	int b;
	int a;
} Color;

/* Struct to represent a drawable game object. */

/* Struct to represent a player. */

typedef struct player
{
	int x;
	int y;
	int dx;
	int dy;
	SDL_Texture *texture;
} Player;

Player * newPlayer() {
	Player * p = (Player *) malloc(sizeof(Player));

	p->x = 0;
	p->y = 0;
	p->dx = 0;
	p->dy = 0;

	p->texture = loadTexture(ASSET_PLAYER);
}

/**
 * @function 		createWindow
 * @description 	Create a SDL_Window.
 * @return 			{SDL_Window} 		Returns a SDL_Window struct.
 */

SDL_Window *createWindow()
{
	return SDL_CreateWindow(W_NAME, SDL_WINDOWPOS_UNDEFINED,
					SDL_WINDOWPOS_UNDEFINED,
					W_WIDTH, W_HEIGHT, 
					SDL_WINDOW_SHOWN);
}

/**
 * @function 		createRenderer
 * @description 	Create a SDL_Renderer with additional customization (V-Sync).
 * @param			{SDL_Window *}		window
 * @return 			{SDL_Renderer} 		Returns a SDL_Renderer struct.
 */


SDL_Renderer *createRenderer(SDL_Window *window)
{
	return SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

/**
 * @function 			batchDraw
 * @description 		Batch draws all rectangles to avoid performance problems.
 * @param	{SDL_Renderer *}	renderer	Current renderer.
 * @param	{SDL_Window *}		window		Current window.
 */

void batchDraw(SDL_Renderer *renderer)
{
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0x00);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
}

/**
 * @function 			batchUpdate
 * @description 		Batch update all rectangles.
 * @param	{Rect *}	rects		The rectangles to update.
 */

void batchUpdate()
{

}

SDL_Texture * loadTexture(SDL_Renderer * renderer, char *name)
{
	SDL_Surface * surface = IMG_Load(name);
	return SDL_CreateTextureFromSurface(renderer, surface);
}

/**
 * @function 			onError
 * @description 		Handle errors by code.
 * @param	{int}		code		Error code.
 */

void onError(int code)
{
	switch (code)
	{
	default:
		printf("Unexpected error ocurred. Aborting execution... Code: %d", code);
		exit(code);
	}
}

/**
 * @function 	 endProgram
 * @description  Finalization method to properly end the program.
 * @param 		 {SDL_Renderer *}	renderer	Current renderer.
 * @param 		 {SDL_Window *}		window		Current window.            
 */

void endProgram(SDL_Renderer *renderer, SDL_Window *window)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

int heardQuitGameEvent()
{
	static SDL_Event event;
	SDL_PollEvent(&event);
	return event.type == SDL_QUIT;
}

/**
 * @function collidesWith
 * @param 	rect	Target rectangle.
 * @param 	x		X-Axis coordinate.
 * @param 	y		Y-Axis coordinate.               
 * @return 	Returns wether or not the rectangle contains that coordinate.
 */

int collidesWith(SDL_Rect rect, int x, int y)
{
	int rx = rect.x;
	int ry = rect.y;
	int rw = rect.w;
	int rh = rect.h;
	int collidesXAxis = rx <= x && x <= rx + rw;
	int collidesYAxis = ry <= y && y <= ry + rh;
	return collidesXAxis && collidesYAxis;
}

/**
 * @function mainLoop
 * @param 	{SDL_Renderer *} 	renderer	Instantiated renderer.
 * @param 	{SDL_Window *} 		window		Instantiated window.
 * @description Runs the game loop.
 */

void mainLoop(SDL_Renderer *renderer, SDL_Window *window)
{
	//...
	Player * player = newPlayer();
	//...
	int running = true;
	while (running)
	{
		batchUpdate();
		batchDraw(renderer);
		
		if (heardQuitGameEvent())
		{
			endProgram(renderer, window);
			running = !running;
		}
	}
}

int main(int argc, char *argv[])
{
	//Initialize stuff and abort in case of any error.
	if (SDL_Init(SDL_INIT_EVERYTHING))
	{
		onError(0);
	}
	//Try to initialize the window.
	SDL_Window *window = createWindow();
	if (window == NULL)
	{
		onError(1);
	}
	//Try to initialize renderer.
	SDL_Renderer *renderer = createRenderer(window);
	if (renderer == NULL)
	{
		onError(2);
	}
	//Main routine.
	mainLoop(renderer, window);
	return 0;
}
