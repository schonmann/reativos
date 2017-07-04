#include <constants.h>
#include <main.h>
#include <util.h>
#include <events.h>
#include <math.h>
#include <time.h>
#include <sdl_engine.h>
#include <SDL2/SDL_ttf.h>

int gameOver;

int collidesWith(SDL_Rect rect, double x, double y)
{
	double rx = rect.x;
	double ry = rect.y;
	double rw = rect.w;
	double rh = rect.h;
	int collidesXAxis = rx <= x && x <= rx + rw;
	int collidesYAxis = ry <= y && y <= ry + rh;

	return collidesXAxis && collidesYAxis;
}

Object *newEnemy(SDL_Renderer * renderer, double y) {
    Object * obj = newObject(renderer, ASSET_ENEMY);
    obj->x = rand() % getWidth() - obj->w/2;
    obj->y = y;
    obj->dx = 0;
    obj->dy = .5;
    obj->ddy = 0.1;
    return obj;
}

Object *newPlayer(SDL_Renderer * renderer) {
    Object * obj = newObject(renderer, ASSET_PLAYER);
    obj->x = getWidth()/2 - obj->w/2;
    obj->y = getHeight() - obj->h*2;
    obj->dx = 4;
    obj->ddy = 1;
    return obj;
}

Object *newBackgroundL0(SDL_Renderer * renderer) {
    Object * obj = newObject(renderer, ASSET_BACKGROUND_L0);
    return obj;
}

Object *newBackgroundL1(SDL_Renderer * renderer) {
    Object * obj = newObject(renderer, ASSET_BACKGROUND_L1);
    return obj;
}

Object *newBackgroundL2(SDL_Renderer * renderer) {
    Object * obj = newObject(renderer, ASSET_BACKGROUND_L2);
    return obj;
}

GameObjects * setup(SDL_Renderer * renderer) {
    int numberOfObjects = 8;

    GameObjects * objs = (GameObjects * ) calloc(sizeof(GameObjects), 1);
    
    objs->n = numberOfObjects;
    objs->objects = (Object **) calloc(sizeof(Object*), objs->n);

    for(int i = 0; i < objs->n; i++) {
        objs->objects[i] = (Object *) calloc(sizeof(Object), 1);
    }

    //Instancia camadas do background.

    objs->objects[0] = newBackgroundL0(renderer);
    objs->objects[1] = newBackgroundL1(renderer);
    objs->objects[2] = newBackgroundL2(renderer);

    //Instancia players.

    objs->objects[3] = newPlayer(renderer);

    //Instancia inimigos.

    objs->objects[4] = newEnemy(renderer, -1*getHeight()/11);
    objs->objects[5] = newEnemy(renderer, -3*getHeight()/11);
    objs->objects[6] = newEnemy(renderer, -5*getHeight()/11);
    objs->objects[7] = newEnemy(renderer, -7*getHeight()/11);
    objs->objects[8] = newEnemy(renderer, -9*getHeight()/11);

    gameOver = false;

    //Retorna objetos.

    return objs;
}

void handleKeyboard(GameObjects * objs) {
    Object * player = objs->objects[3];
    const Uint8* keystates = SDL_GetKeyboardState(NULL);

    int bounds_d = getHeight() - player->h*2;

    if(keystates[SDL_SCANCODE_RIGHT]) {
        player->ddx = PLAYER_DDX; 
    } else if (keystates[SDL_SCANCODE_LEFT]) {
        player->ddx = -PLAYER_DDX;
    }

    if (keystates[SDL_SCANCODE_SPACE] && player->y == bounds_d) {
        player->dy = - 12;
    }
}

void updateEnemies(GameObjects * objs) {
    for(int i = 4; i < objs->n; i++) {
        Object * enemy = objs->objects[i];
        enemy->dy += enemy->ddy;
        enemy->y += enemy->dy;
        if(enemy->y >= getHeight() + enemy->h) {
            //Desaloca inimigo ao atingir o chao.
            free(enemy);
            //Aloca outro inimigo.
            objs->objects[i] = newEnemy(renderer, -50);
        }
    }
}

void updatePlayer(GameObjects * objs) {
    Object * player = objs->objects[3];
    player->dx += player->ddx;
    player->x += player->dx;
    player->dy += player->ddy;
    player->y += player->dy;

    double bounds_r = getWidth() - player->w;
    double bounds_l = 0;
    double bounds_d = getHeight() - player->h*2;

    player->x = clamp(player->x, bounds_l, bounds_r);
    player->dx = clamp(player->dx, -PLAYER_MAX_DX, PLAYER_MAX_DX);
    player->y = clamp(player->y, 0, bounds_d);
}

void checkForCollision(GameObjects * objs) {
    Object * player = objs->objects[3];
    for(int i = 4; i < objs->n; i++) {
        Object * enemy = objs->objects[i];
        if(circularCollision(player,enemy)) {
            printf("Collision!");
            gameOver = true;
        }
    }
}

void update(GameObjects * objs) {
    if(gameOver) return;

    handleKeyboard(objs);
    updateEnemies(objs);
    updatePlayer(objs);
    checkForCollision(objs);
}

void draw(SDL_Renderer * renderer, GameObjects * objs) {

    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0x00);
    SDL_RenderClear(renderer);

    for(int i = 0; i < objs->n; i++) {
        Object *object = objs->objects[i];
        SDL_Rect destination;
        destination.x = object->x;
        destination.y = object->y;
        destination.w = object->w;
        destination.h = object->h;
        SDL_RenderCopy(renderer, object->texture, NULL, &destination);  
    }

    if(gameOver) {
        TTF_Init();
        TTF_Font *f = TTF_OpenFont("./assets/arcade.TTF", 30);
        SDL_Color c;
        c.r = 255; c.g = 80; c.b = 80;
        SDL_Surface * message = TTF_RenderText_Solid(f, "GAME OVER!", c);
        SDL_Texture * t = SDL_CreateTextureFromSurface(renderer, message);
        SDL_Rect r;
        r.x = getWidth()/2 - message->w/2; r.y = getHeight()/2 - message->h/2;
        r.w = message->w;
        r.h = message->h;
        SDL_RenderCopy(renderer, t, NULL, &r);
    }

    SDL_RenderPresent(renderer);
}