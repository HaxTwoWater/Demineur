//#include "ia.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include "DynamicArray.h"
#include <stdlib.h>
#include <windows.h>
#include "MySDL.h"
#include <SDL.h>
#include <SDL_image.h>
#include "Demineur.h"



void Clear() {
    for (int n = 0; n < 10; n++)
        printf("\n\n\n\n\n\n\n\n\n\n");
}

#pragma region Game
int largInt(int a)
{
    int larg = 1;
    while (a >= 10 || a <= -10)
    {
        larg++;
        a /= 10;
    }
    return larg;
}
void repeatChar(char Charact, int i)
{
    for (int j = 0; j < i; j++)
    {
        printf("%c", Charact);
    }
}
void Color(int couleurDuTexte, int couleurDeFond)
{
    HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H, couleurDeFond * 16 + couleurDuTexte);
}

//Game
void app()
{
    SDL_Renderer* renderer = NULL;
    SDL_Window* window = NULL;
    SDL_Event e;
    DynamicArray* dynamic = Create(&renderer, &window);

    
    int finish = 1;
    while (finish)
    {
        //printTable(dynamic);

        char play = ' ';
        int exitWhile = 1;
        int content;
        SDL_SetRenderDrawColor(renderer, 211, 211, 211, 127);
        SDL_RenderClear(renderer);

        while (SDL_PollEvent(&e) && play) {
            Drawn(dynamic, renderer);
            switch (e.type) {
            case SDL_MOUSEBUTTONDOWN:
                int i = e.motion.x / 30;
                int j = e.motion.y / 30;
                if (e.button.button == SDL_BUTTON_LEFT)
                {
                    // code for reveal (left click)
                    content = ((Case*)dynamic->elm)[convertCoordToLen(i, j, dynamic->sizeX)].content;
                    Case selectedCase = ((Case*)dynamic->elm)[convertCoordToLen(i, j, dynamic->sizeX)];
                    if (selectedCase.reveal == 0 && selectedCase.flaged == 0 && dynamic->generated == 1)
                    {
                        exitWhile = 0;
                        if (content == -1)
                        {
                            dynamic = endGame(0, &finish, dynamic, renderer, window);
                        }
                        else
                        {
                            revealCase(dynamic, i, j);
                            checkEndGame(&finish, dynamic, renderer, window);
                        }
                    }
                    else if (selectedCase.reveal == 0 && selectedCase.flaged == 0 && dynamic->generated == 0)
                    {
                        exitWhile = 0;
                        Generate(dynamic, convertCoordToLen(i, j, dynamic->sizeX));
                        revealCase(dynamic, i, j);
                        dynamic->generated = 1;
                    }
                }
                else if (e.button.button == SDL_BUTTON_RIGHT)
                {
                    // code for flag (right click)
                    content = ((Case*)dynamic->elm)[convertCoordToLen(i, j, dynamic->sizeX)].content;
                    Case selectedCase = ((Case*)dynamic->elm)[convertCoordToLen(i, j, dynamic->sizeX)];
                    if (selectedCase.reveal == 0 && selectedCase.flaged == 0 && dynamic->generated == 1)
                    {
                        exitWhile = 0;
                        if (content == -1)
                        {
                            dynamic->bombs = max(dynamic->bombs - 1, 0);
                            ((Case*)dynamic->elm)[convertCoordToLen(i, j, dynamic->sizeX)].flaged = 1;
                            checkEndGame(&finish, dynamic, renderer, window);
                        }
                        else
                        {
                            dynamic = endGame(0, &finish, dynamic, renderer, window);
                        }
                    }
                }
                break;
            case SDL_QUIT:
                play = 0;
                finish = 0;
                DestroyDemineurWindow(renderer, window);
                break;

            default:
                break;
            }

        }

        //Clear();
    }
}

DynamicArray* Create(SDL_Renderer** renderer, SDL_Window** window)
{
    int sizeX = -1;
    int sizeY = -1;
    int difficulty = -1;
    int seed = 0;
    Clear();
    printf("Choose a size with the format x/y : ");
    while (sizeX < 5 || sizeY < 5)
    {
        scanf_s("%d/%d", &sizeX, &sizeY);
        while (getchar() != '\n');
    }
    Clear();
    printf("Choose a difficulty between 0 and 5 (0 is the most easy, and 5 the most difficult) : ");
    while (difficulty < 0 || difficulty > 5)
    {
        scanf_s("%d", &difficulty);
        while (getchar() != '\n');
    }
    Clear();
    printf("Choose a seed (0 for random seed) : ");
    scanf_s("%d", &seed);
    while (getchar() != '\n');
    Clear();

    switch (seed)
    {
    case 0:
        printf("random seed");
        seed = time(NULL);
        break;
    default:
        break;
    }
    srand(seed);

    DynamicArray* newDynamic = InitDynamicArray(sizeX, sizeY, seed, sizeof(Case));
    for (int i = 0; i < newDynamic->length; i++)
    {
        ((Case*)newDynamic->elm)[i].content = 0;
        ((Case*)newDynamic->elm)[i].flaged = 0;
        ((Case*)newDynamic->elm)[i].reveal = 0;
        newDynamic->generated = 0;
    }

    int numBombs = newDynamic->sizeX * newDynamic->sizeY;
    switch (difficulty)
    {
    case 1:
        numBombs = numBombs * 15 / 72;
        break;
    case 2:
        numBombs = numBombs * 20 / 72;
        break;
    case 3:
        numBombs = numBombs * 25 / 72;
        break;
    case 4:
        numBombs = numBombs * 30 / 72;
        break;
    case 5:
        numBombs = numBombs * 1 / 2;
        break;
    default:
        numBombs = numBombs * 10 / 72;
        break;
    }
    newDynamic->bombs = numBombs;

    for (int a = 0; a < newDynamic->sizeX; a++)
    {
        for (int b = 0; b < newDynamic->sizeY; b++)
        {
            ((Case*)newDynamic->elm)[convertCoordToLen(a, b, newDynamic->sizeX)].X = a;
            ((Case*)newDynamic->elm)[convertCoordToLen(a, b, newDynamic->sizeX)].Y = b;
        }
    }

    InitDemineurWindow(renderer, window, sizeX, sizeY);

    return newDynamic;
}

void Generate(DynamicArray* newDynamic, int playPos)
{
    int value = 0;
    int tryPos = 0;
    int posXBomb = -1;
    int posYBomb = -1;
    int sizeX = newDynamic->sizeX;
    int sizeY = newDynamic->sizeY;
    int numBombs = newDynamic->bombs;

    DynamicArray* bomb = InitDynamicArray(sizeX * sizeY, 1, 0, sizeof(Case));
    for (int a = 0; a < bomb->sizeX; a++)
    {
        for (int b = 0; b < bomb->sizeY; b++)
        {
            ((Case*)bomb->elm)[convertCoordToLen(a, b, bomb->sizeX)].X = a;
            ((Case*)bomb->elm)[convertCoordToLen(a, b, bomb->sizeX)].Y = b;
        }
    }

    int Pos[2] = { 0, 0 };
    convertLenToCoord(playPos, sizeX, Pos);
    int sX = max(-1, Pos[0] - 2);
    int eX = min(newDynamic->sizeX, Pos[0] + 1);
    int sY = max(-1, Pos[1] - 2);
    int eY = min(newDynamic->sizeY, Pos[1] + 1);

    for (int b = eY; b > sY; b++)
    {
        for (int a = eX; a > sX; a++)
        {
            DeleteAt((Case*)bomb, convertCoordToLen(a, b, newDynamic->sizeX));
            a -= 2;
        }
        b -= 2;
    }
    for (int i = 0; i < numBombs; i++)
    {
        int p = bomb->length;
        int ri = rand() % p;
        int r = convertCoordToLen(((Case*)bomb->elm)[ri].X, ((Case*)bomb->elm)[ri].Y, bomb->sizeX);
        ((Case*)newDynamic->elm)[r].content = -1;
        DeleteAt(bomb, ri);

        int rPos[2];
        convertLenToCoord(r, newDynamic->sizeX, rPos);
        int startX = max(0, rPos[0] - 1);
        int endX = min(newDynamic->sizeX, rPos[0] + 2);
        int startY = max(0, rPos[1] - 1);
        int endY = min(newDynamic->sizeY, rPos[1] + 2);

        for (int a = startX; a < endX; a++)
        {
            for (int b = startY; b < endY; b++)
            {
                int len = convertCoordToLen(a, b, newDynamic->sizeX);
                if (((Case*)newDynamic->elm)[len].content != -1)
                {
                    ((Case*)newDynamic->elm)[len].content += 1;
                }
            }
        }
    }
    Free(bomb);
}

void checkEndGame(int* finish, DynamicArray* dynamic, SDL_Renderer* renderer, SDL_Window* window)
{
    int ending = 1;
    for (int i = 0; i < dynamic->sizeX * dynamic->sizeY; i++)
    {
        int index = convertCoordToLen(i, 0, dynamic->sizeX);
        if (((Case*)dynamic->elm)[index].content == -1 && ((Case*)dynamic->elm)[index].flaged == 0)
        {
            ending = 0;
        }
        else if (((Case*)dynamic->elm)[index].content == 0 && ((Case*)dynamic->elm)[index].reveal == 0)
        {
            ending = 0;
        }
    }
    if (ending == 1)
    {
        dynamic = endGame(1, finish, dynamic, renderer, window);
    }
}

DynamicArray* endGame(int condition, int* finish, DynamicArray* dynamic, SDL_Renderer* renderer, SDL_Window* window)
{
    Clear();
    for (int j = 0; j < dynamic->sizeX * dynamic->sizeY; j++)
    {
        if (((Case*)dynamic->elm)[convertCoordToLen(j, 0, dynamic->sizeX)].flaged == 0 &&
            ((Case*)dynamic->elm)[convertCoordToLen(j, 0, dynamic->sizeX)].content != -1)
        {
            ((Case*)dynamic->elm)[convertCoordToLen(j, 0, dynamic->sizeX)].reveal = 1;
        }
    }
    printTable(dynamic);

    char ask = 122;
    switch (condition)
    {
    case 0:
        printf("You losed ! Try Again ! \nDo you want to start a new game ? (y/n) > ");
        break;
    case 1:
        printf("Well played ! You Won ! \nDo you want to start a new game ? (y/n) > ");
        break;
    }
    while (ask != 110 && ask != 121)
    {
        scanf_s("%c", &ask, 1);
        while (getchar() != '\n');
    }
    Clear();
    switch (ask)
    {
    case 110:
        // Le joueur ne souhaite pas rejouer (110 = 'n')
        *finish = 0;
        Free(dynamic);
        DestroyDemineurWindow(renderer, window);
        return NULL;
        break;
    case 121:
        // Le joueur souhaite rejouer (121 = 'y')
        Free(dynamic);
        DestroyDemineurWindow(renderer, window);
        renderer = NULL;
        window = NULL;
        return Create(&renderer, &window);
        break;
    }
}

void revealCase(DynamicArray* dynamic, int posX, int posY)
{
    int startX = max(0, posX - 1);
    int endX = min(dynamic->sizeX, posX + 2);
    int startY = max(0, posY - 1);
    int endY = min(dynamic->sizeY, posY + 2);

    int index = convertCoordToLen(posX, posY, dynamic->sizeX);
    ((Case*)dynamic->elm)[index].reveal = 1;
    if (((Case*)dynamic->elm)[index].content == 0) {
        for (int a = startX; a < endX; a++)
        {
            for (int b = startY; b < endY; b++)
            {
                if (((Case*)dynamic->elm)[convertCoordToLen(a, b, dynamic->sizeX)].reveal == 0)
                {
                    revealCase(dynamic, a, b);
                }
            }
        }
    }
}

void printTable(DynamicArray* dynamic)
{
    int larg = largInt(dynamic->sizeX + 1);
    printf("Seed: %d\nBombs remaining: %d\n\n  ", dynamic->seed, dynamic->bombs);
    repeatChar(' ', larg);
    for (int i = 0; i < dynamic->sizeY; i++)
    {
        if (i == dynamic->selectY)
        {
            Color(1, 0);
        }
        printf("%d ", i + 1);
        repeatChar(' ', larg - largInt(i));
        Color(15, 0);
    }
    printf("\n\n");
    for (int a = 0; a < dynamic->sizeX; a++)
    {
        if (a == dynamic->selectX)
        {
            Color(1, 0);
        }
        repeatChar(' ', larg - largInt(a + 1));
        printf("%d  ", a + 1);
        Color(15, 0);
        for (int b = 0; b < dynamic->sizeY; b++)
        {
            int background = 0;
            int index = convertCoordToLen(a, b, dynamic->sizeX);
            if (dynamic->selectX == a && dynamic->selectY == b)
            {
                background = 1;
            }
            if (((Case*)dynamic->elm)[index].flaged == 1)
            {
                Color(10, background);
                printf("F");
            }
            else if (((Case*)dynamic->elm)[index].reveal == 0)
            {
                Color(15, background);
                printf("?");
            }
            else if (((Case*)dynamic->elm)[index].content == -1)
            {
                Color(4, background);
                printf("*");
            }
            else
            {
                Color(13, background);
                if (((Case*)dynamic->elm)[index].content == 0)
                {
                    Color(8, background);
                }
                printf("%d", ((Case*)dynamic->elm)[index].content);
            }
            repeatChar(' ', larg - 1);
            Color(15, 0);
            printf(" ");
        }
        if (a == dynamic->selectX)
        {
            Color(1, 0);
        }
        printf(" %d\n", a + 1);
        Color(15, 0);
    }
    printf("\n  ");
    repeatChar(' ', larg);
    for (int i = 0; i < dynamic->sizeY; i++)
    {
        if (i == dynamic->selectY)
        {
            Color(1, 0);
        }
        printf("%d ", i + 1);
        repeatChar(' ', larg - largInt(i));
        Color(15, 0);
    }
    printf("\n\n");
}
#pragma endregion

int main()
{
    app();

    return 0;
}