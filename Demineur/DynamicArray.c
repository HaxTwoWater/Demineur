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

DynamicArray* InitDynamicArray(int sizeX, int sizeY, int seed, void* type, int elmSize)
{
    int l = sizeX * sizeY;
    DynamicArray* dynamic = (DynamicArray*)malloc(sizeof(DynamicArray));
    dynamic->elm = type;
    dynamic->elmSize = elmSize;
    dynamic->sizeX = sizeX;
    dynamic->sizeY = sizeY;
    dynamic->selectX = sizeX / 2;
    dynamic->selectY = sizeY / 2;
    dynamic->length = l;
    dynamic->seed = seed;
    dynamic->bombs = 0;
    dynamic->generated = 0;
    /*
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
    */
    return dynamic;
}

DynamicArray* DeleteAt(DynamicArray *dynamic, int index)
{
    DynamicArray* newDynamic = InitDynamicArray(dynamic->length - 1, 1, dynamic->seed, dynamic->elm, dynamic->elmSize);
    char* newElm = newDynamic->elm;
    char* oldElm = dynamic->elm;
    for (int i = index; i < newDynamic->length; i++)
    {
        *(newElm + i * newDynamic->elmSize) = *(oldElm + (i + 1) * dynamic->elmSize);
    }
    //free(dynamic->elm);
    //free(dynamic);
    return newDynamic;
}

/*
DynamicArray* AddTo(DynamicArray* dynamic, void* elm) 
{
    DynamicArray* newDynamic = InitDynamicArray(dynamic->length - 1, 1, dynamic->seed, dynamic->elm, dynamic->elmSize);
    newDynamic->elm[newDynamic->length] = *elm;
    free(dynamic->elm);
    free(dynamic);
    return newDynamic;
}

void Free(DynamicArray* dynamic)
{
    for (int i = 0; i < dynamic->length; i++)
    {
        if (dynamic->elm[i].val != NULL)
        {
            free(dynamic->elm[i].val);
        }        
    }
    free(dynamic->elm);
    free(dynamic);
}

void Print(DynamicArray* dynamic)
{
    for (int i = 0; i < dynamic->length; i++)
    {
        printf("%d\n", dynamic->elm[i].val->content);
    }
}
*/