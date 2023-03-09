#include <SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include "MySDL.h"
#include <SDL_image.h>
#include "DynamicArray.h"
#include <time.h>

const int POSITION_X = 800;
const int POSITION_Y = 300;

void InitDemineurWindow() {
    srand(time(NULL));
    Cell c[25];
    DynamicArray* cell = InitDynamicArray(5, 5, 0, c, sizeof(Cell));
    for (int i = 0; i < 25; i++)
    {
        ((Cell*)cell->elm)[i].num = rand() % 10 -1;
        ((Cell*)cell->elm)[i].reveal = 0;
        ((Cell*)cell->elm)[i].flag = 0;
        ((Cell*)cell->elm)[i].bomb = rand() % 2;
    }
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) { printf("%s\n", SDL_GetError()); exit(-1); }
    SDL_Window* window;

    int WIDTH = 30 * 5;
    int HEIGHT = 30 * 5 +0;

    window = SDL_CreateWindow("Demineur", POSITION_X, POSITION_Y, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);

    if (window == NULL) { printf("%s\n", SDL_GetError()); exit(-1); }
    
    SDL_Event e;
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    int play = 1;
    while (play) {

        SDL_SetRenderDrawColor(renderer, 211, 211, 211, 127);
        SDL_RenderClear(renderer);

        while (SDL_PollEvent(&e) && play) {

            Drawn(cell, renderer);
            switch (e.type) {
            case SDL_MOUSEBUTTONDOWN:
                if (e.motion.state == SDL_RELEASED) 
                {
                    int i = e.motion.x / 30;
                    int j = e.motion.y / 30;
                    if (e.button.button == SDL_BUTTON_LEFT)
                    {
                        ((Cell*)cell->elm)[convertCoordToLen(i, j, cell->sizeX)].reveal = 1;
                    }
                    else if (e.button.button == SDL_BUTTON_RIGHT && !((Cell*)cell->elm)[convertCoordToLen(i, j, cell->sizeX)].reveal)
                    {
                        ((Cell*)cell->elm)[convertCoordToLen(i, j, cell->sizeX)].flag = 1;
                    }
                }
                break;
            case SDL_QUIT:
                play = 0;
                break;

            default:
                break;
            }

        }
    }
    SDL_DestroyRenderer(renderer);

    SDL_DestroyWindow(window);
    SDL_Quit();

    return;
}

void Drawn(DynamicArray* cell, SDL_Renderer* rend)
{
    SDL_Surface* image;
    SDL_Texture* texture;
    for(int i = 0; i < cell->length / cell->sizeX; i++)
    {
        for (int j = 0; j < cell->sizeY; j++)
        {
                
            if(((Cell*)((char*)cell->elm + convertCoordToLen(i, j, cell->sizeX) * cell->elmSize))->flag) image = IMG_Load("src/flag.png");
            else
            {
                switch (((Cell*)((char*)cell->elm + convertCoordToLen(i, j, cell->sizeX) * cell->elmSize))->num)
                {
                case -1:
                    image = IMG_Load("src/bombe(1).png");
                    break;
                case 1:
                    image = IMG_Load("src/1.png");
                    break;
                case 2:
                    image = IMG_Load("src/2.png");
                    break;
                case 3:
                    image = IMG_Load("src/3.png");
                    break;
                case 4:
                    image = IMG_Load("src/4.png");
                    break;
                case 5:
                    image = IMG_Load("src/5.png");
                    break;
                case 6:
                    image = IMG_Load("src/6.png");
                    break;
                case 7:
                    image = IMG_Load("src/7.png");
                    break;
                case 8:
                    image = IMG_Load("src/8.png");
                    break;
                default:
                    image = IMG_Load("src/empty.png");
                    break;
                }
            }
            SDL_Rect imgPos = { i * 30, j * 30, 30, 30 };

            image = IMG_Load("src/reveal.png");
            texture = SDL_CreateTextureFromSurface(rend, image);
            SDL_FreeSurface(image);
            SDL_RenderCopy(rend, texture, NULL, &imgPos);

            texture = SDL_CreateTextureFromSurface(rend, image);
            SDL_FreeSurface(image);
            SDL_RenderCopy(rend, texture, NULL, &imgPos);
        }
    }
    SDL_RenderPresent(rend);
}