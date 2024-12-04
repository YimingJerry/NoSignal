#include "Opti_Tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


Place solve(char** grid, char* words)
{
    //char** grid = GetTextInfo(filename);
    int directions[8][2] = {{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1},{-1,0},{-1,1}};
    Place moves;
    //printf("%d\n", (sizeof(grid)/sizeof(grid[0]) + 1));
    size_t len = (sizeof(grid)/sizeof(grid[0])) + 1;
    size_t width = sizeof(grid)/len;
    for(size_t i =0; i <= len; i++)
    {
        //printf("%d\n",(sizeof(grid)/sizeof(grid[0])) + 1);
        //printf("%d\n", sizeof(grid)/len);
        for(size_t j = 0; j < width ; j++)
        {
            //printf("%d + %c\n", WordStartWithLetter(words, grid[i][j]), grid[i][j]);
            if(WordStartWith(words, *grid,0))
            {
                for(size_t x = 0; x < 8; x++)
                {
                    check(grid, words, i, j, directions[x][0], directions[x][1], moves);
                }
            }
        }
    }


    return moves;
}




/*
Node* Opti_Tree(Node* Tree, char** word_list)
{
   
    size_t nbr_ligne = 0;
    while( *(word_list + nbr_ligne) != NULL) //calculer le nombre de lignes de word_list pour le parcourir
    {
=======
/*Node* Opti_Tree(Node* Tree, char** word_list)
{
   
    size_t nbr_ligne = 0;
    while( *(word_list + nbr_ligne) != NULL) /*calculer le nombre de lignes de word_list pour le parcourir*/
    /*{
>>>>>>> 0f9ce7f64bbb2bddb8ba59f52d5dd7e15ea0a0ac
        nbr_ligne += 1;
    }


   Node* optitree = newNode('\0');
    Node* optitree2 = optitree;
    //parcourir chaque mot de word_list pour utliser chaques lettre des mots


<<<<<<< HEAD
    for(size_t i = 0; i < nbr_ligne; i++) //parcours sur le nombre de ligne
    {
        size_t index_children = 0;
        size_t verif_augmentation_index = index_children;
        optitree = optitree2; //on repart sur le noeud NULL
        for(size_t j = 0; j < strlen(word_list); j++) //parcours sur les colonnes de chaque liste
        {
            if(index_children > verif_augmentation_index) //si on a changer de branche (changer de branche: la lettre et le contenu du noeud sont différents)
            {
                for(size_t j2 = j; j2 < strlen(word_list[i]); j2++) //si on change de branche, on veut directement insérer le reste des lettres à la suite
                {
                    optitree->children[index_children] =  newNode(word_list[i][j2]);
                    optitree =  optitree->children[index_children];
                    if(j2 == strlen(word_list[i]) - 1) //si on est sur le dernier carctère, on le spécifie en tant que fin de mot
                    {
=======
    /*for(size_t i = 0; i < nbr_ligne; i++) /*parcours sur le nombre de ligne*/
    /*{
        size_t index_children = 0;
        size_t verif_augmentation_index = index_children;
        optitree = optitree2; /*on repart sur le noeud NULL*/
       /* for(size_t j = 0; j < strlen(word_list[i]); j++) /*parcours sur les colonnes de chaque liste*/
        /*{
            if(index_children > verif_augmentation_index) /*si on a changer de branche (changer de branche: la lettre et
            le contenu du noeud sont différents)*/
            /*{
                for(size_t j2 = j; j < strlen(word_list[i]); j2++) /*si on change de branche, on veut directement insérer le
                reste des lettres à la suite*/
                /*{
                    optitree->children[index_children] =  newNode(word_list[i][j2]);
                    optitree =  optitree->children[index_children];
                    if(j2 == strlen(word_list[i]) - 1)/*si on est sur le dernier carctère, on le spécifie en tant que fin de mot*/
                    /*{
>>>>>>> 0f9ce7f64bbb2bddb8ba59f52d5dd7e15ea0a0ac
                        optitree->isWordEnd = 1;
                    }
                    j == strlen(word_list[i])-1;//Pour passer directement au prochain mot en sorti du if
               
                /*}
            }


<<<<<<< HEAD
            //rajouter un cas si optitree->children[index_children] == NULL alors mettre le reste du mot sur la même branche (exemple concret expliqué ligne 148: BELL et BELLONG)
            else if(optitree->children[index_children] == NULL)
=======
            /*rajouter un cas si optitree->children[index_children] == NULL alors mettre le reste du mot sur la même
             branche (exemple concret expliqué ligne 148: BELL et BELLONG)*/
            /*else if(optitree->children[index_children] == NULL)
>>>>>>> 0f9ce7f64bbb2bddb8ba59f52d5dd7e15ea0a0ac
            {
                for(size_t k = j; k < strlen(word_list[i]); k++)
                {
                    optitree->children[0] =  newNode(word_list[i][k]);
                    optitree =  optitree->children[0];
<<<<<<< HEAD
                    if(k == strlen(word_list[i]) - 1)//si on est sur le dernier carctère, on le spécifie en tant que fin de mot
                    {
=======
                    if(k == strlen(word_list[i]) - 1)/*si on est sur le dernier carctère, on le spécifie en tant que fin de mot*/
                    /*{
>>>>>>> 0f9ce7f64bbb2bddb8ba59f52d5dd7e15ea0a0ac
                        optitree->isWordEnd = 1;
                    }
                    j == strlen(word_list[i])-1;
               
                }
            }
<<<<<<< HEAD
           
            else if( *((word_list[i])+j) != optitree->children[index_children] )//vérifier si on doit changer de branche, c'est-à-dire si la lettre du mot et le noeud auquel on la compare sont différents
            {
                    index_children += 1;
                    optitree->children[index_children] =  newNode(word_list[i][j]);
                    optitree =  optitree->children[index_children];
                    if(j == strlen(word_list[i]) - 1)//si on est sur le dernier carctère, on le spécifie en tant que fin de mot
                    {
                        optitree->isWordEnd = 1;
                    }
            }
           
=======


            else if( *((word_list[i])+j) != optitree->children[index_children]->letter )/*vérifier si on doit changer de branche, c'est-à-dire si
            la lettre du mot et le noeud auquel on la compare sont différents*/
            /*{
                    index_children += 1;
                    optitree->children[index_children] =  newNode(word_list[i][j]);
                    optitree =  optitree->children[index_children];
                    if(j == strlen(word_list[i]) - 1)/*si on est sur le dernier carctère, on le spécifie en tant que fin de mot*/
                    /*{
                        optitree->isWordEnd = 1;
                    }
            /*}


>>>>>>> 0f9ce7f64bbb2bddb8ba59f52d5dd7e15ea0a0ac
            else
            {
                optitree->children[index_children] =  newNode(word_list[i][j]);
                optitree =  optitree->children[index_children];
<<<<<<< HEAD
                if(j == strlen(word_list[i]) - 1)//si on est sur le dernier carctère, on le spécifie en tant que fin de mot
                {
=======
                if(j == strlen(word_list[i]) - 1)/*si on est sur le dernier carctère, on le spécifie en tant que fin de mot*/
                /*{
>>>>>>> 0f9ce7f64bbb2bddb8ba59f52d5dd7e15ea0a0ac
                    optitree->isWordEnd = 1;
                }
            }


        }
    }








<<<<<<< HEAD
    optitree = optitree2; //on revient au noeud racine NULL(le tout premier noeud)
    Tree = optitree; //On donne le Tree optimisé au Tree non-opti
    return NULL;
=======
    optitree = optitree2; /*on revient au noeud racine NULL(le tout premier noeud)*/
    /*Tree = optitree; /*On donne le Tree optimisé au Tree non-opti*/
    /*return NULL;
}*/
/*
Node* newNode(char letter)
{
    Node* node = (Node*)malloc(sizeof(Node));
    node->letter = letter;
    for (int i = 0; i < 26; i++) {
        node->children[i] = NULL;
    }
    node->isWordEnd = 0;
    return node;
>>>>>>> 0f9ce7f64bbb2bddb8ba59f52d5dd7e15ea0a0ac
}


// Fonction pour insérer un mot dans l'arbre
void insertWord(Node* root, char* word) {
    Node* current = root;
    for (int i = 0; word[i] != '\0'; i++) {
        int index = word[i] - 'A'; // Indice de la lettre dans le tableau
        if (current->children[index] == NULL) {
            current->children[index] = newNode(word[i]);
        }
        current = current->children[index];
    }
    current->isWordEnd = 1; // Marquer la fin du mot
}


//Fonction qui supprime un mot de l'arbre














Node* Opti_Tree(Node* Tree, char** word_list) {
    Node* root = newNode('\0');


    for (size_t i = 0; word_list[i] != NULL; i++) {
        Node* current = root;
        for (size_t j = 0; j < strlen(word_list[i]); j++) {
            int index = word_list[i][j] - 'A'; // Convert letter to index
            if (current->children[index] == NULL) {
                current->children[index] = newNode(word_list[i][j]);
            }
            current = current->children[index];
        }
        current->isWordEnd = 1; // Mark end of the word
    }


<<<<<<< HEAD
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


    //deuxieme mot
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




=======
    return root; // Return the optimized tree
>>>>>>> 0f9ce7f64bbb2bddb8ba59f52d5dd7e15ea0a0ac
}
*/


/*


void Affichage(Node* tree, char* buffer, int depth) {
    if (tree == NULL) {
        return;
    }


    // Débogage : Afficher la lettre actuelle
    printf("Visiting node: %c\n", tree->letter);


    // Ajouter la lettre actuelle au buffer
    buffer[depth] = tree->letter;


    // Si c'est la fin d'un mot, afficher le mot
    if (tree->isWordEnd) {
        buffer[depth + 1] = '\0'; // Terminer la chaîne
        printf("%s\n", buffer); // Afficher le mot
    }


    // Parcourir les enfants
    for (size_t i = 0; i < 26; i++) {
        Affichage(tree->children[i], buffer, depth + 1);
    }
}






int main() {
    char* words[] = { "BELL", "BEIN", "BELLONG", NULL };


    // Création d'un Trie avec Opti_Tree
    Node* optimized_tree = Opti_Tree(NULL, words);


    // Afficher les mots de l'arbre optimisé
    char buffer[100];
    printf("Mots dans l'arbre optimisé :\n");
    Affichage(optimized_tree, buffer, 0);


    // Création d'un Trie avec insertWord
    Node* insert_tree = newNode('\0');
    for (size_t i = 0; words[i] != NULL; i++) {
        insertWord(insert_tree, words[i]);
    }


    // Afficher les mots de l'arbre construit avec insertWord
    printf("\nMots dans l'arbre construit avec insertWord :\n");
    Affichage(insert_tree, buffer, 0);


    return 0;
}
*/
/*Je pense que le problème est que nous ne traitons pas la première liste séparement. Dans la fonction le premier fils
sera vide puisque quand on compare la première de la première liste au fils à la position 0 du noeud NULL on tombe sur
une valeur forcément différente de la lettre et donc on va cosntruire la première liste sur le fils 1 au lieu du fils 0.*/






/*Explication:
Si on a le mot BELL qui est déjà implémenté dans l'arbre alors on voudrait que les lettres O,N,G de BELLONG soit implementé sur
la même branche c'est-à-dire le fils 0 du dernier L. Donc si le fils du noeud est NULL, c'est forcément que je suis à la fin
du mot donc je mets le reste du mot sur le fils 0 de chaque noeud.*/


 

