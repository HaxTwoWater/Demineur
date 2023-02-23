#include <stdlib.h>
#include <stdio.h>

typedef struct Case Case;
struct Case
{
    int content;
    int reveal;
    int flaged;

    Case* next;
};

typedef struct ListCase
{
    Case* first;
    int X;
    int Y;
    int selectX;
    int selectY;
} ListCase;

ListCase Create();
void AddCase(ListCase* list, Case val);
void ClearList(ListCase* list);
Case* GetAtIndex(ListCase* list, int indexX, int indexY);
void SetAtIndex(ListCase* list, Case* val, int indexX, int indexY);

ListCase Create()
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
    Case* c = GetAtIndex(list, indexX, indexY);
    c->content = val->content;
    c->flaged = val->flaged;
    c->reveal = val->reveal;
}

void AddCase(ListCase* list, Case val)
{
    Case* c = malloc(sizeof(*c));
    c->next = list->first;
    c->content = 0;
    c->reveal = 0;
    c->flaged = 0;
    list->first = c;
}

Case* GetAtIndex(ListCase* list, int indexX, int indexY)
{
    Case* actual = list->first;
    int i;
    for (i = 0; i < indexY * list->X + indexX; i++)
    {
        actual = actual->next;
    }
    return actual;
}