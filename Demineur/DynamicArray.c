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

DynamicArray* InitDynamicArray(int sizeX, int sizeY, int seed)
{
    int l = sizeX * sizeY;
    DynamicArray* dynamic = (DynamicArray*)malloc(sizeof(DynamicArray));
    dynamic->elm = (ArrayElm*)malloc(sizeof(ArrayElm) * l);
    dynamic->sizeX = sizeX;
    dynamic->sizeY = sizeY;
    dynamic->selectX = sizeX / 2;
    dynamic->selectY = sizeY / 2;
    dynamic->length = l;
    dynamic->seed = seed;
    dynamic->bombs = 0;
    for (int i = 0; i < dynamic->sizeX; i++)
    {
        for (int j = 0; j < dynamic->sizeY; j++)
        {
            int index = convertCoordToLen(i, j, sizeX);
            dynamic->elm[index].val = (Case*)malloc(sizeof(Case));
            dynamic->elm[index].X = i;
            dynamic->elm[index].Y = j;
        }
    }
    return dynamic;
}

void Add(DynamicArray *dynamic, int posX, int posY, Case *c)
{
    ArrayElm newElm;
    newElm.X = posX;
    newElm.Y = posY;
    newElm.val = c;

    void* ptr = (DynamicArray*)realloc(dynamic, (sizeof(dynamic) + 1) * sizeof(DynamicArray));
    if (ptr == NULL) return;
    dynamic = ptr;
    
    dynamic->elm[sizeof(dynamic)] = newElm;
}

DynamicArray* DeleteAt(DynamicArray *dynamic, int index)
{
    DynamicArray* newDynamic = InitDynamicArray(dynamic->length - 1, 1, dynamic->seed);
    int offset = 0;
    for (int i = 0; i < newDynamic->length; i++)
    {
        if (i == index)
        {
            offset = 1;
        }
        newDynamic->elm[i] = dynamic->elm[i + offset];
    }
    //Free(dynamic);
    return newDynamic;
}

void Free(DynamicArray* dynamic)
{
    for (int i = 0; i < dynamic->length; i++)
    {
        free(dynamic->elm[i].val);
    }
    free(dynamic->elm);
    free(dynamic);
}