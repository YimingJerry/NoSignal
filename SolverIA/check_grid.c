#include <stdio.h>
#include <stdlib.h>

int direction[8][2] = { {0,1}, {1,1}, {1,0}, {1,-1}, {0,-1}, {-1,-1}, {-1,0}, {-1,1}};


void Check(int grid[][], char word_list[][], int i, int j, int direction, int moves[][])
{
    int longeur_grid = len(grid);
    int largeur_grid = len(*grid);
    int start_i = i;
    int start_j = j;
    char word_to_find[] = {}; //il faudra mettre la taille adaptée
    

}