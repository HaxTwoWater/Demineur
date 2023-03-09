#ifndef DYNAMIC_ARRAY
#define DYNAMIC_ARRAY

typedef struct DynamicArray
{
    int selectX;
    int selectY;
    int sizeX;
    int sizeY;
    int length;
    int seed;
    int bombs;
    int generated;

    int capacity;
    int elmSize;
    void** elm;
} DynamicArray;

void convertLenToCoord(int len, int sizeX, int coord[2]);
int convertCoordToLen(int x, int y, int sizeX);
DynamicArray* InitDynamicArray(int sizeX, int sizeY, int seed, int elmSize);
void DeleteAt(DynamicArray* dynamic, int index);
DynamicArray* AddTo(DynamicArray* dynamic, void* element);
void Free(DynamicArray* dynamic);
#endif