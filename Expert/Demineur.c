#include <stdio.h>
#define numBombs 10

int min(int a, int b) { return (a > b) ? b : a; }
int max(int a, int b) { return (a < b) ? b : a; }

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
} ListCase;


//Util
ListCase Create(int sizeX, int sizeY);
void AddCase(ListCase *list, Case val);
void ClearList(ListCase *list);
Case* GetAtIndex(ListCase* list, int indexX, int indexY);
void SetAtIndex(ListCase* list, Case *val, int indexX, int indexY);

ListCase Create(int sizeX, int sizeY) 
{
    int a, b;
    int seed = 201;
    ListCase list;
    list.X = sizeX;
    list.Y = sizeY;

    Case oEmptyCase;
    oEmptyCase.content = 0;
    oEmptyCase.reveal = 0;
    oEmptyCase.flaged = 0;

    for (a = 0; a < list.X; a++)
    {
        for (b = 0; b < list.Y; b++)
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

        for (a = max(0, posXBomb - 1); a <= min(list.X, posXBomb + 1); a++)
        {
            for (b = max(0, posYBomb - 1); b <= min(list.Y, posYBomb + 1); b++)
            {
                if (GetAtIndex(&list, a, b)->content != -1)
                {
                    GetAtIndex(&list, a, b)->content++;
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

void app()
{
    int x;
    int y;
    printf("Choose a size with the format x/y :");
    scanf("%d/%d", &x, &y);

    ListCase list = Create(x, y);

    while (1)
    {
        printTable(&list);

        char play = ' ';
        int playX = -1;
        int playY = -1;
        printf("\nformat:  \"[type = \'f\' for flag or \'n\' for nothing] x/y\"\nQue voulez vous jouer ? : ");
        while ((playX < 0 || playX > list.X) || (playY < 0 || playY > list.Y) || (play != 'f' && play != 'n') || (GetAtIndex(&list, playX, playY)->reveal == 1))
        {
            scanf("%s %d/%d", &play, &playY, &playX);
        }
        printf("\n====================\n");

        if (play == 'n')
        {
            revealCase(&list, playX, playY);
        }
        else
        {
            GetAtIndex(&list, playX, playY)->flaged = 1;
        }
    }
    ClearList(&list);
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
                if (GetAtIndex(list, posX, posY)->reveal == 0)
                {
                    revealCase(list, a, b);
                }
            }
        }
    }
}

void printTable(ListCase *list)
{
    printf("\n   ");
    for (int i = 0; i < list->Y; i++)
    {
        printf("%d ", i);
    }
    printf("\n\n");
    for (int a = 0; a < list->X; a++)
    {
        printf("%d  ", a);
        for (int b = 0; b < list->Y; b++)
        {
            if (GetAtIndex(list, a, b)->flaged == 1)
            {
                printf("F ");
            }
            else if (GetAtIndex(list, a, b)->reveal == 0)
            {
                printf("? ");
            }
            else if (GetAtIndex(list, a, b)->content == -1)
            {
                printf("* ");
            }
            else
            {
                printf("%d ", GetAtIndex(list, a, b)->content);
            }
        }
        printf("  %d\n", a);
    }
    printf("\n   ");
    for (int i = 0; i < list->Y; i++)
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
