#include <stdio.h>
#include <string.h>
#include "../Untils/List.c"

int min(int a, int b) { return (a > b) ? b : a; }
int max(int a, int b) { return (a < b) ? b : a; }

#include <stdlib.h>
#include <windows.h>

int largInt(int a)
{
    int larg = 1;
    while (a >= 10 || a<= -10)
    {
        larg++;
        a /= 10;
    }
    return larg;
}
char * repeatChar(char * string, int i)
{
    char * returnString = "";
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
void revealCase(ListCase *list, int posX, int posY);
void printTable(ListCase *list);
void checkEndGame(int* finish, ListCase* list);
void endGame(int condition, int* finish, ListCase* list);

void app()
{
    ListCase list = Create();

    int finish = 1;
    while (finish)
    {
        printTable(&list);

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
                list.selectX = max(list.selectX - 1, 0);
                break;
            case 115:
                exitWhile = 0;
                // code for arrow down
                list.selectX = min(list.selectX + 1, list.X - 1);
                break;
            case 100:
                exitWhile = 0;
                // code for arrow right
                list.selectY = min(list.selectY + 1, list.Y - 1);
                break;
            case 113:
                exitWhile = 0;
                // code for arrow left
                list.selectY = max(list.selectY - 1, 0);
                break;

            case 102:
                exitWhile = 0;
                // code for flag (key F)
                selectedCase = *GetAtIndex(&list, list.selectX, list.selectY);
                if (selectedCase.reveal == 0 && selectedCase.flaged == 0)
                {
                    exitWhile = 0;
                    play = 'f';
                }
                break;
            case 32:
                // code for reveal (key spacebar)
                selectedCase = *GetAtIndex(&list, list.selectX, list.selectY);
                if (selectedCase.reveal == 0 && selectedCase.flaged == 0)
                {
                    exitWhile = 0;
                    play = 'r';
                }
                break;
            }
        }
        system("cls");

        int content = GetAtIndex(&list, list.selectX, list.selectY)->content;

        if (play == 'r')
        {
            if (content == -1)
            {
                endGame(0, &finish, &list);
            }
            else
            {
                revealCase(&list, list.selectX, list.selectY);
                checkEndGame(&finish, &list);
            }
        }
        else if (play == 'f')
        {
            if (content == -1)
            {
                GetAtIndex(&list, list.selectX, list.selectY)->flaged = 1;
                checkEndGame(&finish, &list);
            }
            else
            {
                endGame(0, &finish, &list);
            }
        }
    }
}

void checkEndGame(int* finish, ListCase* list)
{
    int ending = 1;
    for (int i = 0; i < list->X * list->Y; i++)
    {
        if (GetAtIndex(list, i, 0)->content == -1 && GetAtIndex(list, i, 0)->flaged == 0)
        {
            ending = 0;
        }
        else if (GetAtIndex(list, i, 0)->content == 0 && GetAtIndex(list, i, 0)->reveal == 0)
        {
            ending = 0;
        }
    }
    if (ending == 1)
    {
        endGame(1, finish, list);
    }
}

void endGame(int condition, int* finish, ListCase* list)
{
    for (int j = 0; j < list->X * list->Y; j++)
    {
        GetAtIndex(list, j, 0)->reveal = 1;
    }
    printTable(list);
    //ClearList(list);

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
        *list = Create();
        break;
    }
    system("cls");
}

void revealCase(ListCase *list, int posX, int posY)
{
    int startX = max(0, posX - 1);
    int endX = min(list->X, posX +2);
    int startY = max(0, posY - 1);
    int endY = min(list->Y, posY +2);

    GetAtIndex(list, posX, posY)->reveal = 1;
    if (GetAtIndex(list, posX, posY)->content == 0) {
        for (int a = startX; a < endX; a++)
        {
            for (int b = startY; b < endY; b++)
            {
                if (GetAtIndex(list, a, b)->reveal == 0)
                {
                    revealCase(list, a, b);
                }
            }
        }
    }
}

void printTable(ListCase *list)
{
    int larg = largInt(list->X+1);
    printf("  %s", repeatChar(" ", larg));
    for (int i = 0; i < list->Y; i++)
    {
        if (i == list->selectY)
        {
            Color(1, 0);
        }
        printf("%d %s", i+1, repeatChar(" ", larg - largInt(i)));
        Color(15, 0);
    }
    printf("\n\n");
    for (int a = 0; a < list->X; a++)
    {
        if (a == list->selectX)
        {
            Color(1, 0);
        }
        printf("%s%d  ", repeatChar(" ", larg - largInt(a+1)), a+1);
        Color(15, 0);
        for (int b = 0; b < list->Y; b++)
        {
            int background = 0;
            if (list->selectX == a && list->selectY == b)
            {
                background = 1;
            }
            if (GetAtIndex(list, a, b)->flaged == 1)
            {
                Color(10, background);
                printf("F");
            }
            else if (GetAtIndex(list, a, b)->reveal == 0)
            {
                Color(15, background);
                printf("?");
            }
            else if (GetAtIndex(list, a, b)->content == -1)
            {
                Color(4, background);
                printf("*");
            }
            else
            {
                Color(13, background);
                if (GetAtIndex(list, a, b)->content == 0)
                {
                    Color(8, background);
                }
                printf("%d", GetAtIndex(list, a, b)->content);
            }
            printf("%s", repeatChar(" ", larg - 1));
            Color(15, 0);
            printf(" ");
        }
        if (a == list->selectX)
        {
            Color(1, 0);
        }
        printf(" %d\n", a+1);
        Color(15, 0);
    }
    printf("\n  %s", repeatChar(" ", larg));
    for (int i = 0; i < list->Y; i++)
    {
        if (i == list->selectY)
        {
            Color(1, 0);
        }
        printf("%d %s", i+1, repeatChar(" ", larg - largInt(i)));
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
