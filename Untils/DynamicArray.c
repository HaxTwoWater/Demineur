#include <stdlib.h>
typedef struct Case
{
    int content;
    int reveal;
    int flaged;
}Case;

typedef struct ArrayElm ArrayElm;
struct ArrayElm
{
    int X;
    int Y;
    Case *val;
};

typedef struct DynamicArray
{
    ArrayElm *elm;
    int selectX;
    int selectY;
    int sizeX;
    int sizeY;
} DynamicArray;

const int SIZE_ELM = sizeof(ArrayElm);


void convertLenToCoord(int len, int sizeX, int coord[2])
{
    coord[0] = len % sizeX;
    coord[1] = (len - coord[0]) / sizeX;
}

int convertCoordToLen(int x, int y, int sizeX)
{
    return (y * sizeX + x);
}

void Add(DynamicArray *dynamic, int posX, int posY, Case *c)
{
    ArrayElm newElm;
    newElm.X = posX;
    newElm.Y = posY;
    newElm.val = c;

    dynamic->elm = (ArrayElm*) realloc(dynamic->elm, sizeof(dynamic->elm) + SIZE_ELM);
    dynamic->elm[sizeof(dynamic)] = newElm;
}

void DeleteAt(DynamicArray *dynamic, int index)
{
    for (int i = index; i < sizeof(dynamic->elm) - 1; i++)
    {
        dynamic->elm[i] = dynamic->elm[i + 1];
    }
    dynamic->elm = (ArrayElm*)realloc(dynamic->elm, sizeof(dynamic->elm) - SIZE_ELM);
}
