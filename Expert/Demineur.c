#include <stdio.h>
#include <string.h>

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

typedef struct Case Case;
struct Case
{
    int content;
    int reveal;
    int flaged;

    Case *next;
};

typedef struct ListCase 
{
    Case* first;
    int X;
    int Y;
    int selectX;
    int selectY;
} ListCase;

//Util
ListCase Create(int sizeX, int sizeY, int difficulty);
void AddCase(ListCase *list, Case val);
void ClearList(ListCase *list);
Case* GetAtIndex(ListCase* list, int indexX, int indexY);
void SetAtIndex(ListCase* list, Case *val, int indexX, int indexY);

ListCase Create(int sizeX, int sizeY, int difficulty) 
{
    int seed = 201;
    ListCase list;
    list.X = sizeX;
    list.Y = sizeY;
    list.selectX = sizeX / 2;
    list.selectY = sizeY / 2;
    int numBombs = list.X * list.Y;
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

    for (int a = 0; a < list.X; a++)
    {
        for (int b = 0; b < list.Y; b++)
        {
            AddCase(&list, oEmptyCase);
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
            posXBomb = (((seed * 320 + i) * tryPos / 5 * (i * 330 + seed + tryPos) * 2000000 * seed) % list.X + list.X) % list.X;
            posYBomb = (((i * 290 + seed) * tryPos / 3 * (seed * 300 + i + tryPos) * 2000002 * seed) % list.Y + list.Y) % list.Y;
            value = GetAtIndex(&list, posXBomb, posYBomb)->content;
            tryPos++;
        }
        GetAtIndex(&list, posXBomb, posYBomb)->content = -1;

        int startX = max(0, posXBomb - 1);
        int endX = min(list.X, posXBomb + 2);
        int startY = max(0, posYBomb - 1);
        int endY = min(list.Y, posYBomb + 2);

        for (int a = startX; a < endX; a++)
        {
            for (int b = startY; b < endY; b++)
            {
                if (GetAtIndex(&list, a, b)->content != -1)
                {
                    GetAtIndex(&list, a, b)->content += 1;
                }
            }
        }
    }

    return list;
}

void ClearList(ListCase* list)
{
    while (list->first != NULL) 
    {
        Case* actual = list->first;
        list->first = list->first->next;
        free(actual);
    }
}

void SetAtIndex(ListCase* list, Case* val, int indexX, int indexY)
{
    Case *c = GetAtIndex(list, indexX, indexY);
    c->content = val->content;
    c->flaged = val->flaged;
    c->reveal = val->reveal;
}

void AddCase(ListCase* list, Case val)
{
    Case *c = malloc(sizeof(*c));
    c->next = list->first;
    c->content = 0;
    c->reveal = 0;
    c->flaged = 0;
    list->first = c;
}

Case* GetAtIndex(ListCase *list, int indexX, int indexY)
{
    Case *actual = list->first;
    int i;
    for (i = 0; i < indexY * list->X + indexX; i++)
    {
        actual = actual->next;
    }
    return actual;
}

//Game
void revealCase(ListCase *list, int posX, int posY);
void printTable(ListCase *list);
void checkEndGame(int* finish, ListCase* list);
void endGame(int condition, int* finish, ListCase* list);

void app()
{
    int x = -1;
    int y = -1;
    int difficulty = -1;
    printf("Choose a size with the format x/y : ");
    while (x < 0 || y < 0)
    {
        scanf("%d/%d", &x, &y);
    }
    system("cls");
    printf("Choose a difficulty between 0 and 5 (0 is the most easy, and 5 the most difficult) : ");
    while (difficulty < 0 || difficulty > 5)
    {
        scanf("%d", &difficulty);
    }
    system("cls");

    ListCase list = Create(x, y, difficulty);

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
    ClearList(list);

    int ask = -1;
    switch (condition)
    {
    case 0:
        printf("You losed ! Try Again ! \n Type 1 to play again and 0 to exit : ");
        break;
    case 1:
        printf("Well played ! You Won ! \n Type 1 to play again and 0 to exit : ");
        break;
    }
    while (ask != 0 && ask != 1)
    {
        scanf("%d", &ask);
    }
    switch (ask)
    {
    case 0:
        *finish = 0;
        break;
    case 1:
        int x = -1;
        int y = -1;
        int difficulty = -1;
        printf("Choose a size with the format x/y : ");
        while (x < 0 || y < 0)
        {
            scanf("%d/%d", &x, &y);
        }
        system("cls");
        printf("Choose a difficulty between 0 and 5 (0 is the most easy, and 5 the most difficult) : ");
        while (difficulty < 0 || difficulty > 5)
        {
            scanf("%d", &difficulty);
        }
        system("cls");

        *list = Create(x, y, difficulty);
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
