#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char letter;
    struct Node* children[26]; // Tableau pour stocker les enfants
    int isWordEnd; // Indique si le nœud est la fin d'un mot
} Node;

// Fonction pour créer un nouveau nœud
Node* newNode(char letter) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->letter = letter;
    for (int i = 0; i < 26; i++) {
        node->children[i] = NULL;
    }
    node->isWordEnd = 0;
    return node;
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