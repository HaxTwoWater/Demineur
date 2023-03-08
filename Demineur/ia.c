#include "DynamicArray.h"
#include <cstddef>
#include <stdarg.h>
#include <stdio.h>

typedef struct Ia
{
	DynamicArray* RevealPlayabled;
	DynamicArray* FlagPlayabled;
	DynamicArray* Groups;
    int withIa;
} Ia;

Ia newIa()
{
	printf("Do you want to play with the IA ? (y/n) > ");
	char ask = 122;
    while (ask != 110 && ask != 121)
    {
        scanf_s("%c", &ask, 1);
        while (getchar() != '\n');
    }
    Clear();
    Ia ia;
    ia.RevealPlayabled = InitDynamicArray(0, 0, 0);
    ia.FlagPlayabled = InitDynamicArray(0, 0, 0);
    ia.Groups = InitDynamicArray(0, 0, 0);
    switch (ask)
    {
    case 110:
        // Le joueur ne souhaite pas avoir une IA (110 = 'n')
        ia.withIa = 0;
        break;
    case 121:
        // Le joueur souhaite avoir une IA (121 = 'y')
        ia.withIa = 1;
        break;
    }
    return ia;
}

void CreateGroup(int NumBombs, int CoordinateX, int CoordinateY, DynamicArray* Table)
{
    int startX = max(0, CoordinateX - 1);
    int endX = min(Table->sizeX, CoordinateX + 2);
    int startY = max(0, CoordinateY - 1);
    int endY = min(Table->sizeY, CoordinateY + 2);

    // Cr�er un groupe de coordon�e
    for (int a = startX; a < endX; a++)
    {
        for (int b = startY; b < endY; b++)
        {
            int index = convertCoordToLen(a, b, Table->sizeX);
            if (Table->elm[index].val->reveal == 0)
            {
                // Ajouter la coordon� dans le groupe de coordon�e
            }
        }
    }
}