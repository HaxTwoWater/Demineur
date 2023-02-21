#include <stdio.h>
#define sizeX 7
#define sizeY 8
#define numBombs 10

int min(int a, int b) { return (a > b) ? b : a; }
int max(int a, int b) { return (a < b) ? b : a; }

typedef struct Case
{
    int content;
    int reveal;
    int flaged;
}Case;

void revealCase(Case array[sizeX][sizeY], int posX, int posY);
void printTable(Case array[sizeX][sizeY]);
void checkEndGame(int* finish, Case array[sizeX][sizeY]);
void endGame(int condition, int* finish, Case array[sizeX][sizeY]);

void app()
{
    /*printf("Choose a size with the format x/y :");
    scanf("%d/%d", &x, &y);*/

    Case array[sizeX][sizeY];
    int a, b;
    int seed = 201;
    Case oEmptyCase;
    oEmptyCase.content = 0;
    oEmptyCase.reveal = 0;
    oEmptyCase.flaged = 0;
    Case oBombCase;
    oBombCase = oEmptyCase;
    oBombCase.content = -1;

    for (a = 0; a < sizeX; a++)
    {
        for (b = 0; b < sizeY; b++)
        {
            array[a][b] = oEmptyCase;
        }
    }

    int value;
    int tryPos;
    int posXBomb;
    int posYBomb;
    for (int i = 0; i < numBombs; i++)
    {
        value = -1;
        tryPos = 1;
        while (value == -1)
        {
            posXBomb = (((seed * 320 + i) * tryPos / 5 * (i * 330 + seed + tryPos) * 2000000 * seed) % sizeX + sizeX) % sizeX;
            posYBomb = (((i * 290 + seed) * tryPos / 3 * (seed * 300 + i + tryPos) * 2000002 * seed) % sizeY + sizeY) % sizeY;
            value = array[posXBomb][posYBomb].content;
            tryPos++;
        }
        array[posXBomb][posYBomb] = oBombCase;

        for (a = max(0, posXBomb - 1); a <= min(sizeX, posXBomb + 1); a++)
        {
            for (b = max(0, posYBomb - 1); b <= min(sizeY, posYBomb + 1); b++)
            {
                if (array[a][b].content != -1)
                {
                    array[a][b].content++;
                }
            }
        }
    }
    int finish = 1;
    while (finish)
    {
        printTable(array);

        char play = ' ';
        int playX = -1;
        int playY = -1;
        printf("\nformat:  \"[type = \'f\' for flag or \'n\' for nothing] x/y\"\nQue voulez vous jouer ? : ");
        while ((playX < 0 || playX > sizeX) || (playY < 0 || playY > sizeY) || (play != 'f' && play != 'n') || (array[playX][playY].reveal == 1 || array[playX][playY].flaged == 1))
        {
            scanf("%s %d/%d", &play, &playY, &playX);
        }
        printf("\n====================\n");

        int content = array[playX][playY].content;

        if (play == 'n')
        {
            if (content == -1) 
            {
                endGame(0, &finish, array);
            }
            else 
            {
                revealCase(array, playX, playY);
            }
        }
        else
        {
            if (content == -1) 
            {
                array[playX][playY].flaged = 1;
            }
            else 
            {
                endGame(0, &finish, array);
            }
        }
        checkEndGame(&finish, array);
    }
}

void checkEndGame(int* finish, Case array[sizeX][sizeY])
{
    int ending = 1;
    for (int i = 0; i < sizeX * sizeY; i++) 
    {
        if (array[0][i].content == -1 && array[0][i].flaged == 0)
        {
            ending = 0;
        }
        else if (array[0][i].content == 0 && array[0][i].reveal == 0) 
        {
            ending = 0;
        }
    }
    if (ending == 1)
    {
        endGame(1, finish, array);
    }
}

void endGame(int condition, int * finish, Case array[sizeX][sizeY])
{
    for (int j = 0; j < sizeX * sizeY; j++)
    {
        array[0][j].reveal = 1;
    }
    printTable(array);

    int ask;
    switch (condition)
    {
    case 0:
        printf("You losed ! Try Again ! \n Type 1 to play again and 0 to exit : ");
        break;
    case 1:
        printf("Well played ! You Won ! \n Type 1 to play again and 0 to exit : ");
        break;
    } 
    scanf("%d", &ask);
    switch (ask)
    {
    case 0:
        *finish = 0;
        break;
    case 1:
        app();
        break;
    }
    printf("\n====================\n");
}

void revealCase(Case array[sizeX][sizeY], int posX, int posY)
{
    int startX = max(0, posX - 1);
    int endX = min(sizeX, posX +2);
    int startY = max(0, posY - 1);
    int endY = min(sizeY, posY +2);

    array[posX][posY].reveal = 1;
    if (array[posX][posY].content == 0) {
        for (int a = startX; a < endX; a++)
        {
            for (int b = startY; b < endY; b++)
            {
                if (array[a][b].reveal == 0)
                {
                    revealCase(array, a, b);
                }
            }
        }
    }
}

void printTable(Case array[sizeX][sizeY])
{
    printf("\n   ");
    for (int i = 0; i < sizeY; i++)
    {
        printf("%d ", i);
    }
    printf("\n\n");
    for (int a = 0; a < sizeX; a++)
    {
        printf("%d  ", a);
        for (int b = 0; b < sizeY; b++)
        {
            if (array[a][b].flaged == 1)
            {
                printf("F ");
            }
            else if (array[a][b].reveal == 0)
            {
                printf("? ");
            }
            else if (array[a][b].content == -1)
            {
                printf("* ");
            }
            else
            {
                printf("%d ", array[a][b].content);
            }
        }
        printf("  %d\n", a);
    }
    printf("\n   ");
    for (int i = 0; i < sizeY; i++)
    {
        printf("%d ", i);
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