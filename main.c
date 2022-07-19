#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define WIDTH 1200
#define HEIGHT 800

#define IMG_PATH "dvd_logo.png"

#define SPEED 1

typedef struct {
    int xdir;
    int ydir;
    SDL_Texture *texture;
    SDL_Rect rect;
} Dvd_logo;

Dvd_logo create_dvd_logo(SDL_Renderer *renderer)
{
    Dvd_logo dvd_logo = (Dvd_logo) {
        .xdir = 1,
        .ydir = 1,
        .texture = IMG_LoadTexture(renderer, IMG_PATH),
        .rect = (SDL_Rect) {
            .x = WIDTH / 2,
            .y = HEIGHT / 2,
        }
    };

    SDL_QueryTexture(dvd_logo.texture, NULL, NULL, &dvd_logo.rect.w, &dvd_logo.rect.h);
    return dvd_logo;
}

void update_dvd_logo(Dvd_logo *dvd_logo)
{
    if (dvd_logo->rect.x + dvd_logo->rect.w >= WIDTH) dvd_logo->xdir = -1;
    if (dvd_logo->rect.x <= 0) dvd_logo->xdir = 1;
    if (dvd_logo->rect.y + dvd_logo->rect.h >= HEIGHT) dvd_logo->ydir = -1;
    if (dvd_logo->rect.y < 0) dvd_logo->ydir = 1;
    dvd_logo->rect.x += dvd_logo->xdir * SPEED;
    dvd_logo->rect.y += dvd_logo->ydir * SPEED;
}

int main()
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *win = SDL_CreateWindow("Screensaver", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    Dvd_logo dvd_logo = create_dvd_logo(renderer);
    while (1) {
        SDL_Event e;
        if (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT)
            break;
            else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_q)
            break;
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 0, 0, 100, 255);
        SDL_RenderCopy(renderer, dvd_logo.texture, NULL, &dvd_logo.rect);

        SDL_RenderPresent(renderer);
        update_dvd_logo(&dvd_logo);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
