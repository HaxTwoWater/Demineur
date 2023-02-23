#include <stdlib.h>
#include <stdio.h>
#include "DynamicArray.h"

void convertLenToCoord(int len, int sizeX, int coord[2])
{
    coord[0] = len % sizeX;
    coord[1] = (len - coord[0]) / sizeX;
}

int convertCoordToLen(int x, int y, int sizeX)
{
    return (y * sizeX + x);
}

DynamicArray* InitDynamicArray(int sizeX, int sizeY)
{
    DynamicArray* dynamic = (DynamicArray*)malloc(sizeof(DynamicArray));
    dynamic->elm = (ArrayElm*)malloc(sizeof(ArrayElm));
    dynamic->sizeX = sizeX;
    dynamic->sizeY = sizeY;
    dynamic->selectX = sizeX / 2;
    dynamic->selectY = sizeY / 2;
    return dynamic;
}

void Add(DynamicArray *dynamic, int posX, int posY, Case *c)
{
    ArrayElm newElm;
    newElm.X = posX;
    newElm.Y = posY;
    newElm.val = c;

    void* ptr = (ArrayElm*)realloc(dynamic->elm, sizeof(dynamic->elm) + sizeof(ArrayElm));
    if (dynamic->elm == NULL) return;
    dynamic->elm = ptr;
    
    dynamic->elm[sizeof(dynamic)] = newElm;
}

void DeleteAt(DynamicArray *dynamic, int index)
{
    for (int i = index; i < sizeof(dynamic->elm) - 1; i++)
    {
        dynamic->elm[i] = dynamic->elm[i + 1];
    }
    void* ptr = (ArrayElm*)realloc(dynamic->elm, sizeof(dynamic->elm) - sizeof(ArrayElm));
    if (dynamic->elm == NULL) return;
    dynamic->elm = ptr;
}

void Free(DynamicArray* dynamic)
{
    for (int i = 0; i < sizeof(dynamic->elm); i++)
    {
        free(&dynamic->elm[i].val);
    }
    free(dynamic->elm);
    free(dynamic);
}