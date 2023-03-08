#include <SDL.h>
#include <stdlib.h>
#include <stdio.h>


const int WIDTH = 320;
const int HEIGHT = 480;
const int POSITION_X = 800;
const int POSITION_Y = 300;



int main(int c, char* T[]) {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) { printf("%s\n", SDL_GetError()); exit(-1); }
    SDL_Window* window;
    window = SDL_CreateWindow("Hello SDL", POSITION_X, POSITION_Y, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);

    SDL_Rect carreFlag, rectFlag;
    int x = 100;
    int y = 100;
    carreFlag.x = x;
    carreFlag.y = y;
    carreFlag.w = 6;
    carreFlag.h = 6;
    rectFlag.x = x;
    rectFlag.y = y;
    rectFlag.w = 3;
    rectFlag.h = 15;
    SDL_Rect caseSurr, caseFill;
    int spawnCaseX = 10;
    int spawnCaseY = 10;
    int spawnCaseS = 10;
    caseSurr.x = spawnCaseX;
    caseSurr.x = spawnCaseY;
    caseSurr.w = spawnCaseS;
    caseSurr.h = spawnCaseS;
    caseFill.x = spawnCaseX + 1;
    caseFill.x = spawnCaseY + 1;
    caseFill.w = spawnCaseS - 2;
    caseFill.h = spawnCaseS - 2;


    if (window == NULL) { printf("%s\n", SDL_GetError()); exit(-1); }
    //dessiner un composant 
    SDL_Event windowEvent;
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);


    while (1) {
        //
        if (SDL_PollEvent(&windowEvent)) {
            if (windowEvent.type == SDL_QUIT) { break; }
        }
        //SDL_Renderer
        SDL_SetRenderDrawColor(renderer, 211, 211, 211, 127);
        SDL_RenderClear(renderer);

        //Case placement
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderFillRect(renderer, &caseSurr);
        SDL_SetRenderDrawColor(renderer, 220, 240, 49, 255);
        SDL_RenderFillRect(renderer, &caseFill);

        //Flag
        SDL_SetRenderDrawColor(renderer, 169, 169, 169, 255);
        SDL_RenderFillRect(renderer, &rectFlag);
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &carreFlag);


        const char* image_path = "test.bmp";
        SDL_Surface* image = SDL_LoadBMP(image_path);

        if (!image) {
            printf("Failed to load image at %s: %s\n", image_path, SDL_GetError());
            return;
        }
        SDL_FreeSurface(image);


        SDL_RenderPresent(renderer);

    }
    //SDL_Delay(5000);
    SDL_DestroyRenderer(renderer);

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}