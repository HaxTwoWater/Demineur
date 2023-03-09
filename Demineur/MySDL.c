#include "MySDL.h"
#include <SDL.h>
#include <SDL_image.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "DynamicArray.h"
#include "Demineur.h"

const int POSITION_X = 800;
const int POSITION_Y = 300;

void InitDemineurWindow(SDL_Renderer** renderer, SDL_Window** window, int sizeX, int sizeY) {

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) { printf("%s\n", SDL_GetError()); exit(-1); }

    int WIDTH = 30 * sizeX;
    int HEIGHT = 30 * sizeY + 0;

    *window = SDL_CreateWindow("Demineur", POSITION_X, POSITION_Y, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);

    if (window == NULL) { printf("%s\n", SDL_GetError()); exit(-1); }

    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
}

void DestroyDemineurWindow(SDL_Renderer* renderer, SDL_Window* window) {
    SDL_DestroyRenderer(renderer);

    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Drawn(DynamicArray* cell, SDL_Renderer* rend)
{
    srand(0);
    SDL_Surface* image;
    SDL_Surface* image1;
    for (int i = 0; i < cell->length / cell->sizeX; i++)
    {
        for (int j = 0; j < cell->sizeY; j++)
        {
            
            switch (((Case*)cell->elm)[convertCoordToLen(i, j, cell->sizeX)].reveal)
            {
            case 0:
                image1 = IMG_Load("src/empty.png");
                SDL_Texture* myImage11 = SDL_CreateTextureFromSurface(rend, image1);
                SDL_FreeSurface(image1);
                SDL_Rect myImgPos11 = { i * 30, j * 30, 30, 30 };
                SDL_RenderCopy(rend, myImage11, NULL, &myImgPos11);

                switch (((Case*)cell->elm)[convertCoordToLen(i, j, cell->sizeX)].flaged)
                {
                case 1:
                    image = IMG_Load("src/flag.png");
                    break;
                default:
                    image = NULL;
                    break;
                }

                if (image != NULL)
                {
                    SDL_Texture* monImage02 = SDL_CreateTextureFromSurface(rend, image);
                    SDL_FreeSurface(image);
                    SDL_Rect imgPos02 = { i * 30, j * 30, 30, 30 };
                    SDL_RenderCopy(rend, monImage02, NULL, &imgPos02);
                }

                break;
            default:
                image1 = IMG_Load("src/revealed.png");
                SDL_Texture* myImage12 = SDL_CreateTextureFromSurface(rend, image1);
                SDL_FreeSurface(image1);
                SDL_Rect myImgPos12 = { i * 30, j * 30, 30, 30 };
                SDL_Point center = { 15, 15 };
                SDL_RenderCopyEx(rend, myImage12, NULL, &myImgPos12, rand() %4 *90, &center, SDL_FLIP_NONE);

                switch (((Case*)cell->elm)[convertCoordToLen(i, j, cell->sizeX)].content)
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
                    image = NULL;
                    break;
                }

                if (image != NULL)
                {
                    SDL_Texture* monImage01 = SDL_CreateTextureFromSurface(rend, image);
                    SDL_FreeSurface(image);
                    SDL_Rect imgPos01 = { i * 30, j * 30, 30, 30 };
                    SDL_RenderCopy(rend, monImage01, NULL, &imgPos01);
                }

                break;
            }
        }
    }
    SDL_RenderPresent(rend);
}