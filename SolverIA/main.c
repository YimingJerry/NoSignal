#include "Opti_Tree.c"
#include <stdio.h>
#include <stdlib.h>




int main()
{
    /*float mat[2][4] = {
        {1,1,1,1},
        {1,1,1,1}
    };


    int x = (sizeof(mat) / sizeof(mat[0]));
    printf("ligne = %d ", x);
    printf("\n");
    printf("column = %d ", ((sizeof(mat)) / sizeof(float))/x);*/

   
    char** val =  GetTextInfo("Grid.txt");
   
    char* grid[3] =
    {
        "LIL",
        "XUV",
        "WTM"
    };

    char* words = "LX";
    Place res = solve(grid,words);

    return 0;
   
}



