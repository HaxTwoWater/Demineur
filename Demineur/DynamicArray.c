#include <stdlib.h>
#include <stdio.h>
#include "DynamicArray.h"
#include "MySDL.h"
#include "Demineur.h"

void convertLenToCoord(int len, int sizeX, int coord[2])
{
    coord[0] = len % sizeX;
    coord[1] = (len - coord[0]) / sizeX;
}

int convertCoordToLen(int x, int y, int sizeX)
{
    return (y * sizeX + x);
}

DynamicArray* InitDynamicArray(int sizeX, int sizeY, int seed, int elmSize)
{
    int l = sizeX * sizeY;
    DynamicArray* dynamic = (DynamicArray*)malloc(sizeof(DynamicArray));

    dynamic->elmSize = elmSize;
    dynamic->elm = malloc(l * elmSize);
    dynamic->sizeX = sizeX;
    dynamic->sizeY = sizeY;
    dynamic->selectX = sizeX / 2;
    dynamic->selectY = sizeY / 2;
    dynamic->length = l;
    dynamic->seed = seed;
    dynamic->bombs = 0;
    dynamic->generated = 0;
    return dynamic;
}

//Marche seulement en 1 dimension
DynamicArray* DeleteAt(DynamicArray *dynamic, int index)
{
    DynamicArray* newDynamic = InitDynamicArray(dynamic->length - 1, 1, dynamic->seed, dynamic->elmSize);
    int offset = 0;
    for (int i = 0; i < newDynamic->length; i++)
    {
        if (i == index) offset = 1;
        newDynamic->elm[i] = dynamic->elm[i + offset];
    }
    Free(dynamic);
    return newDynamic;
}

//Marche seulement en 1 dimension
DynamicArray* AddTo(DynamicArray* dynamic, void* element)
{
    DynamicArray* newDynamic = InitDynamicArray(dynamic->length + 1, 1, dynamic->seed, dynamic->elmSize);
    for (int i = 0; i < newDynamic->length - 1; i++)
    {
        newDynamic->elm[i] = dynamic->elm[i];
    }
    newDynamic->elm[newDynamic->length - 1] = element;

    Free(dynamic);
    return newDynamic;
}

void Free(DynamicArray* dynamic)
{
    free(dynamic->elm);
    free(dynamic);
}