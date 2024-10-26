#include "Opti.Tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Node* Opti_Tree(Node* Tree, char** word_list)
{
    
    size_t nbr_ligne = 0;
    while( *(word_list + nbr_ligne) != NULL) /*calculer le nombre de lignes de word_list pour le parcourir*/
    {
        nbr_ligne += 1;
    }

   Node* optitree = newNode('\0');
    Node* optitree2 = optitree;
    /*parcourir chaque mot de word_list pour utliser chaques lettre des mots*/

    for(size_t i = 0; i < nbr_ligne; i++) /*parcours sur le nombre de ligne*/
    {
        size_t index_children = 0;
        size_t verif_augmentation_index = index_children;
        optitree = optitree2; /*on repart sur le noeud NULL*/
        for(size_t j = 0; j < strlen(word_list[i]); j++) /*parcours sur les colonnes de chaque liste*/
        {
            if(index_children > verif_augmentation_index) /*si on a changer de branche (changer de branche: la lettre et 
            le contenu du noeud sont différents)*/
            {
                for(size_t j2 = j; j < strlen(word_list[i]); j2++) /*si on change de branche, on veut directement insérer le
                reste des lettres à la suite*/
                {
                    optitree->children[index_children] =  newNode(word_list[i][j2]);
                    optitree =  optitree->children[index_children];
                    if(j2 == strlen(word_list[i]) - 1)/*si on est sur le dernier carctère, on le spécifie en tant que fin de mot*/
                    {
                        optitree->isWordEnd = 1;
                    } 
                    j == strlen(word_list[i])-1;/*Pour passer directement au prochain mot en sorti du if*/
                
                }
            }

            /*rajouter un cas si optitree->children[index_children] == NULL alors mettre le reste du mot sur la même
             branche (exemple concret expliqué ligne 148: BELL et BELLONG)*/
            else if(optitree->children[index_children] == NULL)
            {
                for(size_t k = j; k < strlen(word_list[i]); k++)
                {
                    optitree->children[0] =  newNode(word_list[i][k]);
                    optitree =  optitree->children[0];
                    if(k == strlen(word_list[i]) - 1)/*si on est sur le dernier carctère, on le spécifie en tant que fin de mot*/
                    {
                        optitree->isWordEnd = 1;
                    } 
                    j == strlen(word_list[i])-1;
                
                }
            }

            else if( *((word_list[i])+j) != optitree->children[index_children] )/*vérifier si on doit changer de branche, c'est-à-dire si
            la lettre du mot et le noeud auquel on la compare sont différents*/
            {
                    index_children += 1;
                    optitree->children[index_children] =  newNode(word_list[i][j]);
                    optitree =  optitree->children[index_children];
                    if(j == strlen(word_list[i]) - 1)/*si on est sur le dernier carctère, on le spécifie en tant que fin de mot*/
                    {
                        optitree->isWordEnd = 1;
                    } 
            }

            else
            {
                optitree->children[index_children] =  newNode(word_list[i][j]);
                optitree =  optitree->children[index_children];
                if(j == strlen(word_list[i]) - 1)/*si on est sur le dernier carctère, on le spécifie en tant que fin de mot*/
                {
                    optitree->isWordEnd = 1;
                } 
            }

        }
    }

    optitree = optitree2; /*on revient au noeud racine NULL(le tout premier noeud)*/
    Tree = optitree; /*On donne le Tree optimisé au Tree non-opti*/
    return NULL;
}

void Affichage(Node* Tree)
{
    printf("%c", Tree->letter);
    for(int i = 0; i < 26; i++)
    {
        if(Tree->children[i] != NULL)
        {
            Tree = Tree->children[i];
            while(Tree->isWordEnd = 0)
            {
                printf("%c", Tree->letter);
                Tree = Tree->children[0];
            }
        }
    }

}

int main()
{
    Node* Tree_non_opti = newNode('\0');
    Node* racine_null = Tree_non_opti;

    Tree_non_opti->children[0] = newNode('B');
    Tree_non_opti = Tree_non_opti->children[0];

    Tree_non_opti->children[0] = newNode('E');
    Tree_non_opti = Tree_non_opti->children[0];

    Tree_non_opti->children[0] = newNode('L');
    Tree_non_opti = Tree_non_opti->children[0];

    Tree_non_opti->children[0] = newNode('L');
    Tree_non_opti = Tree_non_opti->children[0];
    Tree_non_opti->isWordEnd = 1;

    /*deuxieme mot*/
    Tree_non_opti = racine_null;
    Tree_non_opti->children[1] = newNode('B');
    Tree_non_opti = Tree_non_opti->children[0];

    Tree_non_opti->children[0] = newNode('E');
    Tree_non_opti = Tree_non_opti->children[0];

    Tree_non_opti->children[0] = newNode('I');
    Tree_non_opti = Tree_non_opti->children[0];

    Tree_non_opti->children[0] = newNode('N');
    Tree_non_opti = Tree_non_opti->children[0];
    Tree_non_opti->isWordEnd = 1;

    Tree_non_opti = racine_null;

    char* list[] = { "BELL","BEIN" };
    Affichage(Tree_non_opti);
    Affichage(Opti_Tree(Tree_non_opti,list));


}



/*Je pense que le problème est que nous ne traitons pas la première liste séparement. Dans la fonction le premier fils
sera vide puisque quand on compare la première de la première liste au fils à la position 0 du noeud NULL on tombe sur 
une valeur forcément différente de la lettre et donc on va cosntruire la première liste sur le fils 1 au lieu du fils 0.*/



/*Explication:
Si on a le mot BELL qui est déjà implémenté dans l'arbre alors on voudrait que les lettres O,N,G de BELLONG soit implementé sur 
la même branche c'est-à-dire le fils 0 du dernier L. Donc si le fils du noeud est NULL, c'est forcément que je suis à la fin
du mot donc je mets le reste du mot sur le fils 0 de chaque noeud.*/