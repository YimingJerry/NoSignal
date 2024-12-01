#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    int premier;
    int second;
} Directions;

typedef struct
{
    int premier;
    int second;
}Couple;

typedef struct 
{
    Couple begin;
    Couple dest;
}Place;


char** GetTextInfo(const char* filename)
{
    FILE* file = fopen(filename, "r");
    if(file == NULL)
    {
        //err(EXIT_FAILURE, "File doesn't exist or filename incorrect.");
        return NULL;
    }

    // contenu et longueur du fichier texte
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    rewind(file);
    char* Buffer[fileSize];
    fclose(file);

    // avoir la longueur d'une ligne
    size_t lineSize = 0;
    while(Buffer[lineSize] != '\n')
    {
        lineSize++;
    }

    char* result[lineSize];
    size_t Pos = 0;
    
    while(Pos < fileSize)
    {
        size_t i = 0;
        while(i < lineSize)
        {
            result[i] = Buffer[Pos];
            printf("%c", Buffer[Pos]);
            i++;
            Pos++;
        }
        *result += 1;
        printf("\n");
        Pos++;
    }

    return result;
}


int CheckWord(char* first, char* second)
{
    size_t len = strlen(first);
    for(size_t i = 0; i < len; i++)
    {
        if (first[i] != second[i])
        {
            return 0;
        }
    }

    return 1;
}

int WordStartWith(char* words, char* part, size_t size)
{
    size_t len = strlen(words);
    if(size == 0)
    {
        return 1;
    }
    
    int l = 0;
    for (size_t j = 0; j < size; j++)
    {
        if(words[j] != part[j])
        {
            break;
        }
        else
        {
            l = j;
        }
    }

    if (l + 1 == size)
    {
        return 1;
    }

    return 0;
}

int GetTheWord(char* words, char* sub, size_t size)
{
    if(size == 0)
    {
        return 0;
    }
        
    size_t l = strlen(words);
    int fault = 0;
    for (size_t j = 0; j < l; j++)
    {
        if(words[j] != sub[j])
        {
            fault = 0;
            break;
        }
        else
        {
            fault = 1;
        }
    }

    if (fault == 1)
    {
        return 1;
    }

    return 0;
}



void check(char* grid[], char* words, size_t i, size_t j, int direct1, int direct2, Place moves)
{
    size_t n = sizeof(grid)/sizeof(grid[0]);
    size_t m = strlen(grid[0]);
    size_t start_i = i;
    size_t start_j = j;
    size_t len = strlen(words);
    char* subString = (char*)malloc(m * sizeof(char));
    size_t subSize = 0;
    while(0<= i && 0 <= j && i <= n + 1 &&  j < m && WordStartWith(words, subString,subSize))
    {
        subString[subSize] = grid[i][j];
        if(WordStartWith(words,subString, len))
        {
            moves.begin.premier = start_i; 
            moves.begin.second = start_j;
            moves.dest.premier = i;
            moves.dest.second = j;
            printf("%d %d %d %d\n",start_i, start_j, i ,j);
            free(subString);
            return;
        }
        i += direct1;
        j += direct2;
        subSize += 1;
        //printf("%d\n",WordStartWith(words, subString,subSize)); 
    }
    free(subString);
}

/*
typedef struct Node {
    char letter;
    struct Node* children[26]; // Tableau pour stocker les enfants
    int isWordEnd; // Indique si le nœud est la fin d'un mot
} Node;


// Fonction pour créer un nouveau nœud
Node* newNode(char letter) 
{
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
}*/