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
    int l = sizeX * sizeY;
    DynamicArray* dynamic = (DynamicArray*)malloc(l * sizeof(DynamicArray));
    dynamic->elm = (ArrayElm*)malloc(sizeof(ArrayElm));
    dynamic->sizeX = sizeX;
    dynamic->sizeY = sizeY;
    dynamic->selectX = sizeX / 2;
    dynamic->selectY = sizeY / 2;
    dynamic->length = l;
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

void DeleteAt(DynamicArray *dynamic, int index)
{
    DynamicArray lastArray[100];
    lastArray->sizeX = dynamic->sizeX;
    lastArray->sizeY = dynamic->sizeY;
    lastArray->selectX = dynamic->selectX;
    lastArray->selectY = dynamic->selectY;
    lastArray->length = dynamic->length;
    for (int i = 0; i < dynamic->length; i++)
    {
        lastArray[i].elm = dynamic[i].elm;
    }
    void* ptr = (DynamicArray*)realloc(dynamic, (dynamic->length - 1) * sizeof(DynamicArray));
    if (ptr == NULL) return;
    dynamic = ptr;
    dynamic->sizeX = lastArray->sizeX;
    dynamic->sizeY = lastArray->sizeY;
    dynamic->selectX = lastArray->selectX;
    dynamic->selectY = lastArray->selectY;
    dynamic->length = lastArray->length;
    dynamic->length--;
    int offset = 0;
    for (int i = 0; i < dynamic->length; i++)
    {
        if (i == index)
        {
            offset = 1;
        }
        dynamic[i].elm = lastArray[i + offset].elm;
    }

}

void Free(DynamicArray* dynamic)
{
    for (int i = 0; i < sizeof(dynamic); i++)
    {
        free(dynamic[i].elm->val);
        free(dynamic[i].elm);
    }
    free(dynamic);
}