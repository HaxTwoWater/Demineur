#ifndef DYNAMIC_ARRAY
#define DYNAMIC_ARRAY

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
    Case* val;
};

typedef struct DynamicArray
{
    ArrayElm* elm;
    int selectX;
    int selectY;
    int sizeX;
    int sizeY;
    int length;
} DynamicArray;

void convertLenToCoord(int len, int sizeX, int coord[2]);
int convertCoordToLen(int x, int y, int sizeX);
DynamicArray* InitDynamicArray(int sizeX, int sizeY);
void Add(DynamicArray* dynamic, int posX, int posY, Case* c);
void DeleteAt(DynamicArray* dynamic, int index);
void Free(DynamicArray* dynamic);
#endif