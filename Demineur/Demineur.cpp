#include <stdio.h>

typedef struct Case
{
    int content;
    int reveal;
}Case;

int main()
{
    /*
    int x, y;
    scanf("%d %d", &x, &y);
    */

    Case array[3][3];
    int a, b;
    Case oDefaultCase;
    int seed = 201;

    for (a = 0; a < 3; a++)
    {
        for (b = 0; b < 3; b++)
        {
            Case oCase;
            int r = (seed * 20 / 15 + 12 - 6) % 2;
            if (r == 1)
            {
                oCase.content = -1;
            }
            else
            {
                oCase.content = 0;
            }
            oCase.reveal = 0;
            array[a][b] = oCase;
        }
    }
    /*
    for (a = 0; a < 3; a++)
    {
        for (b = 0; b < 3; b++)
        {
            if (array[a][b].content == -1) 
            {
                if (a != 0 && array[a - 1][b].content != -1)
                {
                    array[a - 1][b].content += 1;
                }
                if (a != 3 && array[a + 1][b].content != -1)
                {
                    array[a + 1][b].content += 1;
                }
                if (b != 0 && array[a][b - 1].content != -1)
                {
                    array[a][b - 1].content += 1;
                }
                if (b != 3 && array[a][b + 1].content != -1)
                {
                    array[a][b + 1].content += 1;
                }
                if (a != 0 && b != 0 && array[a - 1][b - 1].content != -1)
                {
                    array[a - 1][b - 1].content += 1;
                }
                if (a != 0 && b != 0 && array[a - 1][b].content != -1)
                {
                    array[a - 1][b].content += 1;
                }
                if (a != 0 && array[a - 1][b].content != -1)
                {
                    array[a - 1][b].content += 1;
                }
                if (a != 0 && array[a - 1][b].content != -1)
                {
                    array[a - 1][b].content += 1;
                }
            }
        }
    }
    */
    return(0);
}