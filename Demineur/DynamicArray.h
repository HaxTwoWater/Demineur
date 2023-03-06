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
    void* elm;
    int elmSize;
    int selectX;
    int selectY;
    int sizeX;
    int sizeY;
    int length;
    int seed;
    int bombs;
    int generated;
} DynamicArray;

void convertLenToCoord(int len, int sizeX, int coord[2]);
int convertCoordToLen(int x, int y, int sizeX);
DynamicArray* InitDynamicArray(int sizeX, int sizeY, int seed, void* type, int elmSize);
DynamicArray* DeleteAt(DynamicArray* dynamic, int index);
DynamicArray* AddTo(DynamicArray* dynamic, int index);
void Free(DynamicArray* dynamic);
void Print(DynamicArray* dynamic);
#endif