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

    dynamic->elmSize = elmSize;
    dynamic->elm = malloc(elmSize * l);
    char* val = type;
    for (int i = 0; i < l; i++)
    {
        //*((char*)dynamic->elm + i * dynamic->elmSize) = *(val + i * dynamic->elmSize);
    }

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

//Marche seulement en 1 dimension
DynamicArray* DeleteAt(DynamicArray *dynamic, int index)
{
    DynamicArray* newDynamic = InitDynamicArray(dynamic->length - 1, 1, dynamic->seed, dynamic->elm, dynamic->elmSize);
    char* newElm = newDynamic->elm;
    char* oldElm = dynamic->elm;
    for (int i = index; i < newDynamic->length; i++)
    {
        *(newElm + i * newDynamic->elmSize) = *(oldElm + (i + 1) * dynamic->elmSize);
    }
    Free(dynamic);
    return newDynamic;
}

//Marche seulement en 1 dimension
DynamicArray* AddTo(DynamicArray* dynamic, void* element) 
{
    DynamicArray* newDynamic = InitDynamicArray(dynamic->length + 1, 1, dynamic->seed, dynamic->elm, dynamic->elmSize);
    *((char*)newDynamic->elm + (newDynamic->length - 1) * newDynamic->elmSize) = *((char*)element);

    Free(dynamic);
    return newDynamic;
}

void* GetAt(DynamicArray* dynamic, int i)
{
    return (char*)dynamic->elm + i * dynamic->elmSize;
}

void Free(DynamicArray* dynamic)
{
    /*
    for (int i = 0; i < dynamic->length; i++)
    {
        if (dynamic->elm[i].val != NULL)
        {
            free(dynamic->elm[i].val);
        }        
    }
    */
    free(dynamic->elm);
    free(dynamic);
}