#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct 
{
    float first;
    float second;
}CoupleOfFloat;

typedef struct 
{
    float** W;
    float** b;
}CoupleOfWAndb;


typedef struct 
{
    char* key;
    float** value;
}WorB; // Dictionnaire

typedef struct 
{
    WorB paraW;
    WorB paraB;
}Dico; // Dictionnaire W et B

float** Transpose(float* X[])
{

}

float** BroadCast(float y)
{
    
}

float** dot(float* X[], float* B[])
{
    size_t n = sizeof(X[0]);
    size_t m = sizeof(X) / sizeof(X[0]);
    size_t o =sizeof(B[0]);
    float result[m][o];

    for (size_t i = 0; i < m; i++)
    {
        for (size_t j = 0; j < o; j++)
        {
            result[i][j] = 0;
            for(size_t k = 0; k < n; k++)
            {
                result[i][j] += X[i][k] * B[k][j];
            }
        }
    }
    return result;

}


float** Addition(float* X[], float* B[]) // Somme de 2 matrices
{
    size_t n = sizeof(X[0]);
    size_t m = sizeof(X) / sizeof(X[0]);
    size_t o =sizeof(B[0]);
    float result[m][o];

    for (size_t i = 0; i < m; i++)
    {
        for (size_t j = 0; j < o; j++)
        {
            result[i][j] = 0;
            for(size_t k = 0; k < n; k++)
            {
                result[i][j] += X[i][k] + B[k][j];
            }
        }
    }
    return result;

}

float** Sum(float* A[], int axis)
{
    size_t x = sizeof(A) / sizeof(A[0]);
    size_t y = sizeof(A[0]);

    if(axis)
    {
        x = sizeof(A[0]);
        y = sizeof(A) / sizeof(A[0]);
    }

    float result[x];
    for(size_t i = 0; i < x; i++)
    {
        float sum = 0;
        for (size_t j = 0; j < y; j++)
        {
            sum += A[i][j];
        }
        result[i] = sum;
    }

    return result;
}

float** CreateMatrice(float dim1, float dim2) // créer une matrice random
{

}

Dico** Initialisation(float* X) // X -> c'est une liste
{
    Dico* Wb;
    size_t C = sizeof(X);

    for(size_t i = 1; i < C; i++)
    {
        Wb[i].paraW.key = 'W' + (char*)i;
        Wb[i].paraW.value = CreateMatrice(X[i], X[i-1]);
        Wb[i].paraB.key = 'b' + (char*)i;
        Wb[i].paraB.value = CreateMatrice(X[i],1);
    }
    return Wb;
}

WorB* ForwardPropagation(float* X, Dico** Wb)
{
    WorB* act;
    act->key = 'A0';
    act->value = X;
    size_t lengthOfAct = 1;
    size_t len = sizeof(Wb) / sizeof(Wb[0]);

    size_t C = sizeof(Wb) / 2;
    for(size_t i = 1; i < C+1; i++)
    {
        float** val = Wb[i]->paraW.value;
        float** b = Wb[i]->paraB.value;
        float** A = act[i-1].value;

        float** Z = Addition(dot(val, A), b);

        size_t lengthOfZ = sizeof(Z) / sizeof(Z[0]);
        size_t WeidthOfZ = sizeof(Z[0]);
        for (size_t i = 0; i < lengthOfZ; i++)
        {
            for(size_t j = 0; j < WeidthOfZ; j++)
            {
                Z[i][j] = 1 / (1 + expf(-Z[i][j]));
            }
        }
        
        act[lengthOfAct].key = 'A' + (char*)i;
        act[lengthOfAct].value = Z;
        lengthOfAct++;
    }

    return act;
}

Dico** BackPropagation(float** y, WorB* act, Dico** Wb)
{
    size_t m  = sizeof(y[0]);
    size_t C = sizeof(Wb) / 2;

    float** dZ = act[C].value - y;
    Dico* Gradients;

    for(size_t i = C; C > 0; i--)
    {
        Gradients[i].paraW.key = 'dW' + (char*)(i);
        Gradients[i].paraW.value = (dot(dZ, Transpose(act[i-1].value)));

        size_t lengthOfWValue = sizeof(Gradients[i].paraW.value) / sizeof(Gradients[i].paraW.value[0]);
        size_t WeidthOfWValue = sizeof(Gradients[i].paraW.value[0]);
        for(size_t j = 0; j < lengthOfWValue; j++)
        {
            for(size_t k = 0; k < WeidthOfWValue; k++)
            {
                Gradients[i].paraW.value[j][k] *= 1/m;
            }
        }

        Gradients[i].paraB.key = 'db' + (char*)i;
        Gradients[i].paraB.value = Sum(dZ, 1);

        size_t lengthOfBValue = sizeof(Gradients[i].paraB.value) / sizeof(Gradients[i].paraB.value[0]);
        size_t WeidthOfBValue = sizeof(Gradients[i].paraB.value[0]);
        for(size_t j = 0; j < lengthOfBValue; j++)
        {
            for(size_t k = 0; k < WeidthOfBValue; k++)
            {
                Gradients[i].paraB.value[j][k] *= 1/m;
            }
        }

        if (i > 1)
        {
            dZ = dot(dot(Transpose(Wb[i]->paraW.value), dZ), act[i-1].value);
            float** this = act[i-1].value;
            size_t lengthOfthis = sizeof(this) / sizeof(this[0]);
            size_t WeidthOfthis = sizeof(this[0]);
            for (size_t j = 0; j < lengthOfthis; j++)
            {
                for (size_t k = 0; k < WeidthOfthis; k++)
                {
                    this[i][j] = (1 - this[i][j]);
                }
            }
            dZ = dot(dZ, this);
        }
    } 

    return Gradients;

}




Dico** Update(Dico** gradiants, Dico* Wb, float learning_rate)
{
    size_t C = sizeof(Wb) / 2;

    for(size_t i = 1; i < C+1; i++)
    {
        size_t lengthOfGra = sizeof(gradiants[i]->paraW.value) / sizeof(gradiants[i]->paraW.value[0]);
        size_t WeidthOfGra =  sizeof(gradiants[i]->paraW.value[0]);
        for (size_t j = 0; j < lengthOfGra; j++)
        {
            for(size_t k = 0; k < WeidthOfGra; k++)
            {
                gradiants[i]->paraW.value[j][k] *= learning_rate;
            }
        }
        Wb[i].paraW.value = Wb[i].paraW.value - gradiants[i]->paraW.value;
        
        lengthOfGra = sizeof(gradiants[i]->paraB.value) / sizeof(gradiants[i]->paraB.value[0]);
        WeidthOfGra =  sizeof(gradiants[i]->paraB.value[0]);
        for (size_t j = 0; j < lengthOfGra; j++)
        {
            for(size_t k = 0; k < WeidthOfGra; k++)
            {
                gradiants[i]->paraB.value[j][k] *= learning_rate;
            }
        }

        Wb[i].paraB.value = Wb[i].paraB.value - gradiants[i]->paraB.value;
    }
    return Wb;
}

int Predict(float* X, Dico* parametre)
{
    WorB* activation = ForwardPropagation(X, parametre);
    size_t C = sizeof(parametre) / 2;
    float Af = **(activation[C].value);
    
    if(Af >= 0.5)
    {
        return 1;
    }
    return 0;
}
