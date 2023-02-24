﻿#include <stdio.h>
#include <string.h>
#include <time.h>
#include <conio.h>

int min(int a, int b) { return (a > b) ? b : a; }
int max(int a, int b) { return (a < b) ? b : a; }

#include "DynamicArray.h"
#include <stdlib.h>
#include <windows.h>

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
void revealCase(DynamicArray* dynamic, int posX, int posY);
void printTable(DynamicArray* dynamic);
void checkEndGame(int* finish, DynamicArray* dynamic);
void endGame(int condition, int* finish, DynamicArray* dynamic);
DynamicArray* Create();

void app()
{
    DynamicArray* dynamic = Create();

    int finish = 1;
    while (finish)
    {
        printTable(dynamic);

        char play = ' ';
        int exitWhile = 1;
        while (exitWhile)
        {
            Case selectedCase;
            switch (getch())
            {
            case 122:
                exitWhile = 0;
                // code for arrow up
                dynamic->selectX = max(dynamic->selectX - 1, 0);
                break;
            case 115:
                exitWhile = 0;
                // code for arrow down
                dynamic->selectX = min(dynamic->selectX + 1, dynamic->sizeX - 1);
                break;
            case 100:
                exitWhile = 0;
                // code for arrow right
                dynamic->selectY = min(dynamic->selectY + 1, dynamic->sizeY - 1);
                break;
            case 113:
                exitWhile = 0;
                // code for arrow left
                dynamic->selectY = max(dynamic->selectY - 1, 0);
                break;

            case 102:
                exitWhile = 0;
                // code for flag (key F)
                selectedCase = *dynamic[convertCoordToLen(dynamic->selectX, dynamic->selectY, dynamic->sizeX)].elm->val;
                if (selectedCase.reveal == 0 && selectedCase.flaged == 0)
                {
                    exitWhile = 0;
                    play = 'f';
                }
                break;
            case 32:
                // code for reveal (key spacebar)
                selectedCase = *dynamic[convertCoordToLen(dynamic->selectX, dynamic->selectY, dynamic->sizeX)].elm->val;
                if (selectedCase.reveal == 0 && selectedCase.flaged == 0)
                {
                    exitWhile = 0;
                    play = 'r';
                }
                break;
            }
        }
        system("cls");

        int content = dynamic[convertCoordToLen(dynamic->selectX, dynamic->selectY, dynamic->sizeX)].elm->val->content;

        if (play == 'r')
        {
            if (content == -1)
            {
                endGame(0, &finish, dynamic);
            }
            else
            {
                revealCase(dynamic, dynamic->selectX, dynamic->selectY);
                checkEndGame(&finish, dynamic);
            }
        }
        else if (play == 'f')
        {
            if (content == -1)
            {
                dynamic[convertCoordToLen(dynamic->selectX, dynamic->selectY, dynamic->sizeX)].elm->val->flaged = 1;
                checkEndGame(&finish, dynamic);
            }
            else
            {
                endGame(0, &finish, dynamic);
            }
        }
    }
    Free(dynamic);
}

DynamicArray* Create()
{
    int sizeX = -1;
    int sizeY = -1;
    int difficulty = -1;
    system("cls");
    printf("Choose a size with the format x/y : ");
    while (sizeX < 0 || sizeY < 0)
    {
        scanf_s("%d/%d", &sizeX, &sizeY);
    }
    system("cls");
    printf("Choose a difficulty between 0 and 5 (0 is the most easy, and 5 the most difficult) : ");
    while (difficulty < 0 || difficulty > 5)
    {
        scanf_s("%d", &difficulty);
    }
    system("cls");

    int seed = 201;
    DynamicArray* newDynamic = InitDynamicArray(sizeX, sizeY);

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

    Case oEmptyCase;
    oEmptyCase.content = 0;
    oEmptyCase.reveal = 0;
    oEmptyCase.flaged = 0;

    for (int a = 0; a < newDynamic->sizeX; a++)
    {
        for (int b = 0; b < newDynamic->sizeY; b++)
        {
            Case* newCase = (Case*)malloc(sizeof(Case));
            newCase->content = oEmptyCase.content;
            newCase->reveal = oEmptyCase.reveal;
            newCase->flaged = oEmptyCase.flaged;

            ArrayElm* newElm = (ArrayElm*)malloc(sizeof(ArrayElm));
            newElm->X = a;
            newElm->Y = b;
            newElm->val = newCase;


            newDynamic[convertCoordToLen(a, b, newDynamic->sizeX)].elm = newElm;
        }
    }
    int value = 0;
    int tryPos = 0;
    int posXBomb = -1;
    int posYBomb = -1;
    DynamicArray* bomb = InitDynamicArray(sizeX, sizeY);
    for (int a = 0; a < bomb->sizeX * bomb->sizeY; a++)
    {
        bomb[a].selectX = a;
    }
    srand(time(NULL));
    for (int i = 0; i < numBombs; i++)
    {
        int p = bomb->length;
        int ri = rand() % p;
        int r = bomb[ri].selectX;
        newDynamic[r].elm->val->content = -1;
        DeleteAt(bomb, ri);
        printf("%d, %d / %d\n", p, ri, r);

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
                if (newDynamic[len].elm->val->content != -1)
                {
                    newDynamic[len].elm->val->content += 1;
                }
            }
        }
    }

    //Free(bomb);

    return newDynamic;
}

void checkEndGame(int* finish, DynamicArray* dynamic)
{
    int ending = 1;
    for (int i = 0; i < dynamic->sizeX * dynamic->sizeY; i++)
    {
        if (dynamic[convertCoordToLen(i, 0, dynamic->sizeX)].elm->val->content == -1 && dynamic[convertCoordToLen(i, 0, dynamic->sizeX)].elm->val->flaged == 0)
        {
            ending = 0;
        }
        else if (dynamic[convertCoordToLen(i, 0, dynamic->sizeX)].elm->val->content == 0 && dynamic[convertCoordToLen(i, 0, dynamic->sizeX)].elm->val->reveal == 0)
        {
            ending = 0;
        }
    }
    if (ending == 1)
    {
        endGame(1, finish, dynamic);
    }
}

void endGame(int condition, int* finish, DynamicArray* dynamic)
{
    for (int j = 0; j < dynamic->sizeX * dynamic->sizeY; j++)
    {
        dynamic[convertCoordToLen(j, 0, dynamic->sizeX)].elm->val->reveal = 1;
    }
    printTable(dynamic);

    char ask = -1;
    switch (condition)
    {
    case 0:
        printf("You losed ! Try Again ! \nDo you want to start a new game ? (y/n) > ");
        break;
    case 1:
        printf("Well played ! You Won ! \nDo you want to start a new game ? (y/n) > ");
        break;
    }
    while (ask != 'y' && ask != 'n')
    {
        scanf_s("%s", &ask);
    }
    switch (ask)
    {
    case 'n':
        *finish = 0;
        break;
    case 'y':
        dynamic = Create();
        break;
    }
    system("cls");
}

void revealCase(DynamicArray* dynamic, int posX, int posY)
{
    int startX = max(0, posX - 1);
    int endX = min(dynamic->sizeX, posX + 2);
    int startY = max(0, posY - 1);
    int endY = min(dynamic->sizeY, posY + 2);

    dynamic[convertCoordToLen(posX, posY, dynamic->sizeX)].elm->val->reveal = 1;
    if (dynamic[convertCoordToLen(posX, posY, dynamic->sizeX)].elm->val->content == 0) {
        for (int a = startX; a < endX; a++)
        {
            for (int b = startY; b < endY; b++)
            {
                if (dynamic[convertCoordToLen(a, b, dynamic->sizeX)].elm->val->reveal == 0)
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
    printf("  ");
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
            if (dynamic->selectX == a && dynamic->selectY == b)
            {
                background = 1;
            }
            if (dynamic[convertCoordToLen(a, b, dynamic->sizeX)].elm->val->flaged == 1)
            {
                Color(10, background);
                printf("F");
            }
            else if (dynamic[convertCoordToLen(a, b, dynamic->sizeX)].elm->val->reveal == 0)
            {
                Color(15, background);
                printf("?");
            }
            else if (dynamic[convertCoordToLen(a, b, dynamic->sizeX)].elm->val->content == -1)
            {
                Color(4, background);
                printf("*");
            }
            else
            {
                Color(13, background);
                if (dynamic[convertCoordToLen(a, b, dynamic->sizeX)].elm->val->content == 0)
                {
                    Color(8, background);
                }
                printf("%d", dynamic[convertCoordToLen(a, b, dynamic->sizeX)].elm->val->content);
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

int main()
{
    app();

    printf("\n\nProgram ended, press any button to exit the code...");
    _getch();
    return 0;
}