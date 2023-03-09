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
        ((Cell*)cell->elm)[i].reveal = rand() % 2;
    }
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) { printf("%s\n", SDL_GetError()); exit(-1); }
    SDL_Window* window;

    int WIDTH = 30 * 5;
    int HEIGHT = 30 * 5 +0;

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

    const char* image_path = "src/1.png";

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

        /*
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
        */

        Drawn(cell, renderer);

    }
    //SDL_Delay(5000);
    SDL_DestroyRenderer(renderer);

    SDL_DestroyWindow(window);
    SDL_Quit();

    return;
}

void Drawn(DynamicArray* cell, SDL_Renderer* rend)
{
    for(int i = 0; i < cell->length / cell->sizeX; i++)
    {
        for (int j = 0; j < cell->sizeY; j++)
        {
            SDL_Surface* image;
            /*
            printf("%d\n", ((Cell*)cell->elm)[convertCoordToLen(i, j, cell->sizeX) * cell->elmSize]);
            printf("%d\n", ((Cell*)cell->elm)[convertCoordToLen(i, j, cell->sizeX) * cell->elmSize].num);
            printf("%d\n", ((Cell*)((char*)cell->elm + convertCoordToLen(i, j, cell->sizeX) * cell->elmSize)));
            printf("%d\n", ((char*)cell->elm + convertCoordToLen(i, j, cell->sizeX) * cell->elmSize));
            printf("%d\n", ((Cell*)((char*)cell->elm + convertCoordToLen(i, j, cell->sizeX) * cell->elmSize))->num);
            printf("%d\n", ((Cell*)((char*)cell->elm + convertCoordToLen(i, j, cell->sizeX) * cell->elmSize))->reveal);
            printf("%d\n", *((char*)cell->elm + convertCoordToLen(i, j, cell->sizeX) * cell->elmSize));
            printf("\n");
            */

            //(((Cell*)(GetAt(cell, convertCoordToLen(i, j, cell->sizeX))))->num)
            SDL_Texture* myImage = SDL_CreateTextureFromSurface(rend, IMG_Load("src/revealed.png"));
            SDL_FreeSurface(IMG_Load("src/revealed.png"));
            SDL_Rect myImgPos = { i * 30, j * 30, 30, 30 };
            SDL_RenderCopy(rend, myImage, NULL, &myImgPos);

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
                switch (((Cell*)((char*)cell->elm + convertCoordToLen(i, j, cell->sizeX) * cell->elmSize))->reveal)
                {
                    case 0:
						image = IMG_Load("src/empty.png");
						break;
                    default:
                        image = NULL;
                        break;
                }
                break;
            }
            
            if (image != NULL)
            {
                SDL_Texture* monImage = SDL_CreateTextureFromSurface(rend, image);
                SDL_FreeSurface(image);
                SDL_Rect imgPos = { i * 30, j * 30, 30, 30 };
                SDL_RenderCopy(rend, monImage, NULL, &imgPos);
            }
        }
    }
    SDL_RenderPresent(rend);
}