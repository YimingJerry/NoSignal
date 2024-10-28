#include <stdio.h>
#include <stdlib.h>
#include "Opti_Tree.h";

int direction[8][2] = { {0,1}, {1,1}, {1,0}, {1,-1}, {0,-1}, {-1,-1}, {-1,0}, {-1,1}};

int isCharInChildren(Node* node, char ch) {
    int index = ch - 'A'; // Convertir le caractère en index (A=0, B=1, ...)
    return (index >= 0 && index < 26 && node->children[index] != NULL);
}


void Check(char* grid[], Node* trie, int i, int j,int i_diff, int j_diff, int direction, int moves[10/*nombre de mots à chercher*/][4],
int moves_index)
{
    int longueur_grid = len(grid);
    int largeur_grid = len(grid[0]);
    int start_i = i;
    int start_j = j;
    char substring[100]; //il faudra mettre la taille adaptée
    int indice_sub = 0;
    Node* node = trie;
    while(0 <= i && i < longueur_grid &&  0 <= j && j < largeur_grid && isCharInChildren(node, grid[i][j]))
    {
        substring[indice_sub] = grid[i][j]; /*correspond à substring += grid[i][j]*/
        indice_sub += 1;
         if (node->isWordEnd)  // Si node.is_end
         {
        // Suppression du mot (à implémenter selon ta logique)
        // trie_delete(trie, substring); // Fonction à définir pour supprimer le mot

            // Ajout de la position de départ et de la position actuelle dans moves
            moves[moves_index][0] = start_i; // Position de départ
            moves[moves_index][1] = start_j; // Position de départ
            moves[moves_index][2] = i; // Position actuelle
            moves[moves_index][3] = j; // Position actuelle
            moves_index++; // Incrémente l'indice de moves
         }

         i += i_diff;
         j += j_diff;
    }
 
}