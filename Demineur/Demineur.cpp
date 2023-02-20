#include <stdio.h>

int main()
{
    int array[3][3];
    int a, b, i;

    i = 0;
    for (a = 0; a < 3; a++)
    {
        for (b = 0; b < 3; b++)
        {
            array[a][b] = i++;
        }
    }
    for (a = 0; a < 3; a++)
    {
        for (b = 0; b < 3; b++)
        {
            printf("%d ", array[a][b]);
        }
        printf("\n");
    }

    return(0);
}