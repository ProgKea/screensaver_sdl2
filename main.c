#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_image.h>

#define WIDTH 800
#define HEIGHT 600

#define IMG_PATH "dvd_logo.png"

#define SPEED 1

#define TOP_RIGHT 1
#define TOP_LEFT 2
#define BOTTOM_LEFT 3
#define BOTTOM_RIGHT 4
#define TOP 5
#define BOTTOM 6

SDL_Window *win;
SDL_Renderer *renderer;
SDL_Rect rect;
SDL_Texture *dvd_logo;

int dir;

void init()
{
  dir = BOTTOM_RIGHT;

  SDL_Init(SDL_INIT_EVERYTHING);
  win = SDL_CreateWindow("Screensaver", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
  renderer = SDL_CreateRenderer(win, -1, 0);

  dvd_logo = IMG_LoadTexture(renderer, IMG_PATH);
}

void draw_rect()
{
  SDL_RenderClear(renderer);

  rect.h = 75;
  rect.w = 90;

  SDL_SetRenderDrawColor(renderer, 0, 0, 100, 255);
  /* SDL_RenderFillRect(renderer, &rect); */
  SDL_RenderCopy(renderer, dvd_logo, NULL, &rect);

  SDL_RenderPresent(renderer);
}

void move_rect(int direction)
{
  switch (direction) {
  case TOP_RIGHT:
    rect.x+=SPEED;
    rect.y-=SPEED;
    break;
  case TOP_LEFT:
    rect.x-=SPEED;
    rect.y-=SPEED;
    break;
  case BOTTOM_LEFT:
    rect.x-=SPEED;
    rect.y+=SPEED;
    break;
  case BOTTOM_RIGHT:
    rect.x+=SPEED;
    rect.y+=SPEED;
    break;
  }
}

void check_collision()
{
    if (rect.y >= HEIGHT-rect.h && dir == BOTTOM_RIGHT) {
	dir = TOP_RIGHT; 
    }
    if (rect.y >= HEIGHT-rect.h && dir == BOTTOM_LEFT) {
	dir = TOP_LEFT; 
    }
    if (rect.y <= 0 && dir == TOP_RIGHT) {
	dir = BOTTOM_RIGHT; 
    }
    if (rect.y <= 0 && dir == TOP_LEFT) {
	dir = BOTTOM_LEFT; 
    }
    if (rect.x >= WIDTH-rect.w && dir == TOP_RIGHT) {
	dir = TOP_LEFT; 
    }
    if (rect.x >= WIDTH-rect.w && dir == BOTTOM_RIGHT) {
	dir = BOTTOM_LEFT; 
    }
    if (rect.x <= 0 && dir == TOP_LEFT) {
	dir = TOP_RIGHT; 
    }
    if (rect.x <= 0 && dir == BOTTOM_LEFT) {
	dir = BOTTOM_RIGHT; 
    }
}

int main()
{
  init();
  
  while (1) {
    SDL_Event e;
    if (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT)
	break;
      else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_q)
	break;
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    draw_rect();
    move_rect(dir);
    check_collision();
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(win);
  return 0;
}
