#include <stdio.h>
#include <string.h>
#include <time.h>

int min(int a, int b) { return (a > b) ? b : a; }
int max(int a, int b) { return (a < b) ? b : a; }

#include "../Untils/DynamicArray.c"
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
char* repeatChar(char* string, int i)
{
    char* returnString = "";
    for (int k = 0; k < strlen(returnString); k++)
    {
        returnString[k] = 0;
    }
    returnString[0] = 0;
    for (int j = 0; j < i; j++)
    {
        returnString = strcat(returnString, string);
    }
    return returnString;
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
DynamicArray Create();

void app()
{
    DynamicArray dynamic = Create();

    int finish = 1;
    while (finish)
    {
        printTable(&dynamic);

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
                dynamic.selectX = max(dynamic.selectX - 1, 0);
                break;
            case 115:
                exitWhile = 0;
                // code for arrow down
                dynamic.selectX = min(dynamic.selectX + 1, dynamic.sizeX - 1);
                break;
            case 100:
                exitWhile = 0;
                // code for arrow right
                dynamic.selectY = min(dynamic.selectY + 1, dynamic.sizeY - 1);
                break;
            case 113:
                exitWhile = 0;
                // code for arrow left
                dynamic.selectY = max(dynamic.selectY - 1, 0);
                break;

            case 102:
                exitWhile = 0;
                // code for flag (key F)
                selectedCase = *dynamic.elm[convertCoordToLen(dynamic.selectX, dynamic.selectY, dynamic.sizeX)].val;
                if (selectedCase.reveal == 0 && selectedCase.flaged == 0)
                {
                    exitWhile = 0;
                    play = 'f';
                }
                break;
            case 32:
                // code for reveal (key spacebar)
                selectedCase = *dynamic.elm[convertCoordToLen(dynamic.selectX, dynamic.selectY, dynamic.sizeX)].val;
                if (selectedCase.reveal == 0 && selectedCase.flaged == 0)
                {
                    exitWhile = 0;
                    play = 'r';
                }
                break;
            }
        }
        system("cls");

        int content = dynamic.elm[convertCoordToLen(dynamic.selectX, dynamic.selectY, dynamic.sizeX)].val->content;

        if (play == 'r')
        {
            if (content == -1)
            {
                endGame(0, &finish, &dynamic);
            }
            else
            {
                revealCase(&dynamic, dynamic.selectX, dynamic.selectY);
                checkEndGame(&finish, &dynamic);
            }
        }
        else if (play == 'f')
        {
            if (content == -1)
            {
                dynamic.elm[convertCoordToLen(dynamic.selectX, dynamic.selectY, dynamic.sizeX)].val->flaged = 1;
                checkEndGame(&finish, &dynamic);
            }
            else
            {
                endGame(0, &finish, &dynamic);
            }
        }
    }
}

DynamicArray Create()
{
    int sizeX = -1;
    int sizeY = -1;
    int difficulty = -1;
    system("cls");
    printf("Choose a size with the format x/y : ");
    while (sizeX < 0 || sizeY < 0)
    {
        scanf("%d/%d", &sizeX, &sizeY);
    }
    system("cls");
    printf("Choose a difficulty between 0 and 5 (0 is the most easy, and 5 the most difficult) : ");
    while (difficulty < 0 || difficulty > 5)
    {
        scanf("%d", &difficulty);
    }
    system("cls");

    int seed = 201;
    DynamicArray newDynamic;
    newDynamic.sizeX = sizeX;
    newDynamic.sizeY = sizeY;
    newDynamic.selectX = sizeX / 2;
    newDynamic.selectY = sizeY / 2;
    Init(newDynamic);
    int numBombs = newDynamic.sizeX * newDynamic.sizeY;
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
    oEmptyCase.reveal = 1;
    oEmptyCase.flaged = 0;

    for (int a = 0; a < newDynamic.sizeX; a++)
    {
        for (int b = 0; b < newDynamic.sizeY; b++)
        {
            Add(newDynamic, a, b, oEmptyCase);
        }
    }
    int value;
    int tryPos;
    int posXBomb;
    int posYBomb;
    DynamicArray bomb = newDynamic;
    srand(time(NULL));
    for (int i = 0; i < numBombs; i++)
    {
        int ri = rand() % sizeof(bomb);
        int r = convertCoordToLen(bomb.elm[ri].X, bomb.elm[ri].Y, newDynamic.sizeX);
        newDynamic.elm[r].val->content = -1;
        DeleteAt(bomb, ri);

        int rPos[2];
        convertLenToCoord(r, newDynamic.sizeX, rPos);
        int startX = max(0, rPos[0] - 1);
        int endX = min(newDynamic.sizeX, rPos[0] + 2);
        int startY = max(0, rPos[1] - 1);
        int endY = min(newDynamic.sizeY, rPos[1] + 2);

        for (int a = startX; a < endX; a++)
        {
            for (int b = startY; b < endY; b++)
            {
                if (newDynamic.elm[convertCoordToLen(a, b, newDynamic.sizeX)].val->content != -1)
                {
                    newDynamic.elm[convertCoordToLen(a, b, newDynamic.sizeX)].val->content += 1;
                }
            }
        }
    }

    return newDynamic;
}

void checkEndGame(int* finish, DynamicArray* dynamic)
{
    int ending = 1;
    for (int i = 0; i < dynamic->sizeX * dynamic->sizeY; i++)
    {
        if (dynamic->elm[convertCoordToLen(i, 0, dynamic->sizeX)].val->content == -1 && dynamic->elm[convertCoordToLen(i, 0, dynamic->sizeX)].val->flaged == 0)
        {
            ending = 0;
        }
        else if (dynamic->elm[convertCoordToLen(i, 0, dynamic->sizeX)].val->content == 0 && dynamic->elm[convertCoordToLen(i, 0, dynamic->sizeX)].val->reveal == 0)
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
        dynamic->elm[convertCoordToLen(j, 0, dynamic->sizeX)].val->reveal = 1;
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
        scanf("%s", &ask);
    }
    switch (ask)
    {
    case 'n':
        *finish = 0;
        break;
    case 'y':
        *dynamic = Create();
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

    dynamic->elm[convertCoordToLen(posX, posY, dynamic->sizeX)].val->reveal = 1;
    if (dynamic->elm[convertCoordToLen(posX, posY, dynamic->sizeX)].val->content == 0) {
        for (int a = startX; a < endX; a++)
        {
            for (int b = startY; b < endY; b++)
            {
                if (dynamic->elm[convertCoordToLen(a, b, dynamic->sizeX)].val->reveal == 0)
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
    printf("  %s", repeatChar(" ", larg));
    for (int i = 0; i < dynamic->sizeY; i++)
    {
        if (i == dynamic->selectY)
        {
            Color(1, 0);
        }
        printf("%d %s", i + 1, repeatChar(" ", larg - largInt(i)));
        Color(15, 0);
    }
    printf("\n\n");
    for (int a = 0; a < dynamic->sizeX; a++)
    {
        if (a == dynamic->selectX)
        {
            Color(1, 0);
        }
        printf("%s%d  ", repeatChar(" ", larg - largInt(a + 1)), a + 1);
        Color(15, 0);
        for (int b = 0; b < dynamic->sizeY; b++)
        {
            int background = 0;
            if (dynamic->selectX == a && dynamic->selectY == b)
            {
                background = 1;
            }
            if (dynamic->elm[convertCoordToLen(a, b, dynamic->sizeX)].val->flaged == 1)
            {
                Color(10, background);
                printf("F");
            }
            else if (dynamic->elm[convertCoordToLen(a, b, dynamic->sizeX)].val->reveal == 0)
            {
                Color(15, background);
                printf("?");
            }
            else if (dynamic->elm[convertCoordToLen(a, b, dynamic->sizeX)].val->content == -1)
            {
                Color(4, background);
                printf("*");
            }
            else
            {
                Color(13, background);
                if (dynamic->elm[convertCoordToLen(a, b, dynamic->sizeX)].val->content == 0)
                {
                    Color(8, background);
                }
                printf("%d", dynamic->elm[convertCoordToLen(a, b, dynamic->sizeX)].val->content);
            }
            printf("%s", repeatChar(" ", larg - 1));
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
    printf("\n  %s", repeatChar(" ", larg));
    for (int i = 0; i < dynamic->sizeY; i++)
    {
        if (i == dynamic->selectY)
        {
            Color(1, 0);
        }
        printf("%d %s", i + 1, repeatChar(" ", larg - largInt(i)));
        Color(15, 0);
    }
    printf("\n\n");
}

int main()
{
    app();

    printf("\n\nProgram ended, press any button to exit the code...");
    getch();
    return(0);
}
