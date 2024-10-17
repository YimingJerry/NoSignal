#include <stdio.h>
#include <stdlib.h>

int direction[8][2] = { {0,1}, {1,1}, {1,0}, {1,-1}, {0,-1}, {-1,-1}, {-1,0}, {-1,1}};


void Check(char* grid[], char word_list[][]/*le type de word_list sera un arbre*/, int i, int j,int i_diff, int j_diff, int direction, int moves[][])
{
    int longueur_grid = len(grid);
    int largeur_grid = len(grid[0]);
    int start_i = i;
    int start_j = j;
    char substring[] = {}; //il faudra mettre la taille adaptée
    int indice_sub = 0;
    /*noeud node = Trie()*/
    while(0 <= i && i < longueur_grid &&  0 <= j && j < largeur_grid /*&& grid[i][j] in node.children*/)
    {
        substring[indice_sub] = grid[i][j]; /*correspond à substring += grid[i][j]*/
        indice_sub += 1;
        /*if node.is_end: /*si on est sur une feuille
            trie.delete(substring)
            moves.append((start_i), (start_j), (i, j)
        i += i_diif
        j += j_diff
        */
    }
 
}