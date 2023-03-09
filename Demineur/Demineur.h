#ifndef DEMINEUR
#define DEMINEUR

typedef struct Case
{
    int content;
    int reveal;
    int flaged;
    int X;
    int Y;
}Case;


void revealCase(DynamicArray* dynamic, int posX, int posY);
void printTable(DynamicArray* dynamic);
void checkEndGame(int* finish, DynamicArray* dynamic);
DynamicArray* endGame(int condition, int* finish, DynamicArray* dynamic);
DynamicArray* Create(SDL_Renderer* renderer, SDL_Window* window);
void Generate(DynamicArray* newDynamic, int playPos);

#endif // !Demineur
