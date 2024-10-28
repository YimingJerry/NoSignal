#include "Opti_Tree.c"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    char* grid[3] = 
    {
        "LOL",
        "XUV",
        "WTM"
    };

    char* words[2] = {"XU","LX"};

    //printf("%d",sizeof(grid)/sizeof(grid[0])); it works
    //printf("%d",sizeof(grid[0])); it works

    /*printf("\n");
    printf("%c\n",grid[0][1]); // idea for the placement of the letters*/

    //printf("%d\n",(sizeof(words)/sizeof(words[0])));

    //printf("%d\n", WordStartWith(words, "L")); //it works

    // printf("%d\n", WordStartWithLetter(words, 'L')); // it works
    
    /*Delete(words, "LOL");
    for(size_t i = 0; i < sizeof(words)/sizeof(words[0]); i++)
    {
        printf("%s\n", words[i]);
    }*/

    /*printf("\n");
    Place moves[2]; 
    check(grid,words,1,1,-1,0,moves,0); i
    printf("\n");*/
    
    /*check(grid,words,0,0,0,1,moves,0); // right direction;
    printf("\n");*/

    Place* res = solve(grid,words);
    
    return 0;
}