#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

/* Struct to represent a drawable game object. */

typedef struct object
{
	int x;
	int y;
    int w;
    int h;
	double dx;
	double dy;
    double ddx;
    double ddy;

	SDL_Texture *texture;

} Object;

/* Struct to wrap all game objects and it's quantity as n. */

typedef struct game_objects {
    int n;
    Object ** objects;

} GameObjects;

void assertTextureNotNull(SDL_Texture * texture);
Object * newObject(SDL_Renderer * renderer, char * texture);
int getWidth();
int getHeight();
double clamp(double x, double min, double max);
int rectangularCollision(Object *a, Object *b);
int circularCollision(Object *a, Object *b);