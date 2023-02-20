#include <stdio.h>

typedef struct Case
{
    int content;
    int reveal;
}Case;

int main()
{
    Case array[3][3];
    int a, b;
    Case oDefaultCase;
    oDefaultCase.content = 0;
    oDefaultCase.reveal = 0;

    for (a = 0; a < 3; a++)
    {
        for (b = 0; b < 3; b++)
        {
            array[a][b] = oDefaultCase;
        }
    }

    return(0);
}