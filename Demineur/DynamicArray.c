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
    dynamic->generated = 1;
    dynamic->capacity = l;
    return dynamic;
}

//Marche seulement en 1 dimension
void DeleteAt(DynamicArray *dynamic, int index)
{
    dynamic->length--;
    for (int i = index; i < dynamic->length; i++)
    {
        printf("%d ", ((Case*)dynamic->elm)[i].X);

        //dynamic->elm[i * dynamic->elmSize] = dynamic->elm[(i + 1) * dynamic->elmSize];
        ((Case*)dynamic->elm)[i] = ((Case*)dynamic->elm)[(i + 1)];

        printf("%d ", ((Case*)dynamic->elm)[i].X);
        printf("%d \n", ((Case*)dynamic->elm)[i + 1].X);
    }
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