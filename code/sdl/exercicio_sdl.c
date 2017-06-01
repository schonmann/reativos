#include <SDL2/SDL.h>
#include <stdlib.h>

#define W_WIDTH 640      //Window width.
#define W_HEIGHT 480     //Window height.
#define MAX_DISTANCE 100 //The max distance a rectangle will walk before changing it's direction.
#define NR 2             //Numer of rectangles.

#define UP 0    //Facing up.
#define RIGHT 1 //Facing right.
#define DOWN 2  //Facing down.
#define LEFT 3  //Facing left.

/* Function signatures. */

SDL_Window *createWindow();
SDL_Renderer *createRenderer(SDL_Window *window);
SDL_Rect buildRect(int x1, int x2, int y1, int y2);
void move(SDL_Rect *rect, int x, int y);
void drawRect(SDL_Renderer *renderer, SDL_Rect rect);
void batchDraw(SDL_Renderer *renderer, SDL_Rect *rects);
void onError(int code);

/* Struct to wrap the rectangle and it's facing direction. */

typedef struct rect
{
    SDL_Rect *r;
    int speed;
    int facing;
    int distance;
} Rect;

SDL_Window *createWindow()
{
    return SDL_CreateWindow("Hello World!",
                            SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED,
                            W_WIDTH, W_HEIGHT, SDL_WINDOW_SHOWN);
}

SDL_Renderer *createRenderer(SDL_Window *window)
{
    return SDL_CreateRenderer(window, -1.0);
}

SDL_Rect buildRect(int x1, int x2, int y1, int y2)
{
    SDL_Rect = {x1, x2, y1, y2};
    return r;
}

void move(Rect *r, int dx, int dy)
{
    rect->r->x += dx;
    rect->r->y += dy;
    rect->distance += dx + dy;
}

void drawRect(SDL_Renderer *renderer, SDL_Rect rect)
{
    SDL_SetRendererDrawColor(renderer, 0x00, 0x00, 0xFF, 0x00);
    SDL_RenderFillRect(renderer, &rect);
}

void batchDraw(SDL_Renderer *renderer, SDL_Rect *rects)
{
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0x00);
    SDL_RenderFillRect(renderer, NULL);
    //Render all rectangles.
    for (int r = 0; r < NR; r++)
        drawRect(renderer, rects[i]);
    //Batch render all the previous rendering calls.
    SDL_RenderPresent(renderer);
}

/* Error routine. */

void onError(int code)
{
    printf("Unexpected error ocurred. Aborting execution... Code: %d", code);
    exit(0);
}

SDL_Rect *getInitialRectangles()
{
    SDL_Rect r1 = {50, 50, 50, 50};
    SDL_Rect r2 = {50, 50, 50, 100};
    Rect *rects = (Rect *)malloc(sizeof(Rect) * NR);
    //...
    rects[0].r = r1;
    rects[0].speed = 1;
    rects[0].facing = UP;
    rects[0].distance = 0;
    //...
    rects[1].r = r2;
    rects[1].speed = 1;
    rects[1].facing = DOWN;
    rects[1].distance = 0;

    return rects;
}

int main()
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
    Rect *rects = getInitialRectangles();
    while (1)
    {
        for (int i = 0; i < NR; i++)
        {
            switch (rects[i].facing)
            {
            case UP:
                break;
            case RIGHT:
                break;
            case DOWN:
                break;
            case LEFT:
                break;
            }
        }
    }

    //Finalization.
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
