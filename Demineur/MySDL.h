#ifndef MY_SDL
#define MY_SDL
#include <SDL.h>
#include "DynamicArray.h"

void InitDemineurWindow(SDL_Renderer* renderer, SDL_Window* window, int sizeX, int sizeY);
void DestroyDemineurWindow(SDL_Renderer* renderer, SDL_Window* window);
void Drawn(DynamicArray* cell, SDL_Renderer* rend);

#endif // !MY_SDL
