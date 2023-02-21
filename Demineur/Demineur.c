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

void revealCase(Case array[][sizeX][sizeY], int posX, int posY, int firstGen);

int main()
{
    /*printf("Choose a size with the format x/y :");
    scanf("%d/%d", &x, &y);*/

    Case array[sizeX][sizeY];
    int a, b;
    int seed = 199;
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
            posXBomb = (((seed * 320 + i) * tryPos / 5 * (i * 330 + seed + tryPos) * 2000000 * seed) % sizeX + sizeX) %sizeX;
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

    while (1)
    {
        printf("\n");
        for (a = 0; a < sizeX; a++)
        {
            for (b = 0; b < sizeY; b++)
            {
                if (array[a][b].flaged == 1)
                {
                    printf("F ");
                }
                else 
                if (array[a][b].reveal == 0)
                {
                    printf("? ");
                }
                else if(array[a][b].content == -1)
                {
                    printf("* ");
                }
                else
                {
                    printf("%d ", array[a][b].content);
                }
            }
            printf("\n");
        }

        char play = ' ';
        int playX = -1;
        int playY = -1;
        printf("\nformat:  \"[type = \'f\' for flag or \'n\' for nothing] x/y\"\nQue voulez vous jouer ? : ");
        while ((playX < 0 || playX > sizeX) || (playY < 0 || playY > sizeY) || (play != 'f' && play != 'n') || (array[playX][playY].reveal == 1))
        {
            scanf("%s %d/%d", &play, &playY, &playX);
        }
        printf("\n====================\n");

        if (play == 'n')
        {
            revealCase(&array, playX, playY, 1);
        }
        else
        {
            array[playX][playY].flaged = 1;
        }
    }


    printf("\n\nProgram ended, press any button to exit the code...");
    getch();
    return(0);
}

void revealCase(Case array[][sizeX][sizeY], int posX, int posY, int firstGen)
{
    (*array)[posX][posY].reveal = 1;
    if ((*array)[posX][posY].content == 0 || firstGen == 1) {
        for (int a = max(0, posX - 1); a <= min(sizeX, posX + 1); a++)
        {
            for (int b = max(0, posY - 1); b <= min(sizeY, posY + 1); b++)
            {
                if ((*array)[a][b].reveal == 0)
                {
                    revealCase(array, a, b, 0);
                }
            }
        }
    }
}