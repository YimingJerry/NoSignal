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




float** CreateMatrice(float row, float column) // créer une matrice composé de 1
{
    float matrix[(size_t)row][(size_t)column];


    for (int i = 0; i < (int)row; i++)
    {
        for (int j = 0; j < (int)column; j++)
        {
            matrix[i][j] = 1.0f;
        }
    }


    return (float**) matrix;
}


float** Transpose(float* X[], int row, int col)
{
    float transposed[(size_t)col][(size_t)row];


    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            transposed[j][i] = X[i][j];
        }
    }


    return (float**)transposed;
}


float** dot(float* X[], float* B[])
{
    size_t m = sizeof(X) / sizeof(X[0]);        
    size_t n = (sizeof(X) / sizeof(float)) / m;    
    size_t o = (sizeof(B) / sizeof(float)) / m;
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
    return (float**)result;


}




float** Addition(float* X[], float* B[]) // Somme de 2 matrices
{
    size_t m = sizeof(X) / sizeof(X[0]);        
    size_t n = (sizeof(X) / sizeof(float)) / m;    
    size_t o = (sizeof(B) / sizeof(float)) / m;
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
    return (float**)result;


}


float** Sum(float* A[], int axis)
{
    size_t x = (sizeof(A) / sizeof(A[0]));
    size_t y = (sizeof(A[0]) / sizeof(float))/x;


    if(axis)
    {
        x = (sizeof(A[0]) / sizeof(float)) / x;
        y = (sizeof(A) / sizeof(A[0]));
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


    return (float**)result;
}


Dico** Initialisation(float* X) // X -> c'est une liste
{
    Dico* Wb;
    size_t C = sizeof(X) / sizeof(float);


    for(size_t i = 1; i < C; i++)
    {
        Wb[i].paraW.key = 'W' + (char*)i;
        Wb[i].paraW.value = CreateMatrice(X[i], X[i-1]);
        Wb[i].paraB.key = 'b' + (char*)i;
        Wb[i].paraB.value = CreateMatrice(X[i],1);
    }
    return &Wb;
}


WorB* ForwardPropagation(float* X, Dico** Wb)
{
    size_t C = sizeof(Wb) / 2;
    WorB act[C+1] ;
    act[0].key = (char*)"A0";
    act[0].value = (float**)X;
    size_t lengthOfAct = 1;
    //size_t len = (sizeof(Wb) / sizeof(Wb[0])) ;


    for(size_t i = 1; i < C+1; i++)
    {
        float** val = Wb[i]->paraW.value;
        float** b = Wb[i]->paraB.value;
        float** A = (float**) act[i-1].value;


        float** Z = Addition(dot(val, A), b);


        size_t lengthOfZ = (sizeof(Z) / sizeof(Z[0]));
        size_t WeidthOfZ = (sizeof(Z) / sizeof(float)) / lengthOfZ;
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
    size_t rowY = sizeof(y)/  sizeof(y[0]);
    size_t m  = (sizeof(y) / sizeof(float)) / rowY;
    size_t C = (sizeof(Wb) / sizeof(Wb[0])) / 2;


    float** dZ = (float**) (act[C].value - y);
    Dico* Gradients;


    for(size_t i = C; C > 0; i--)
    {
        Gradients[i].paraW.key = 'dW' + (char*)(i);
        size_t x = sizeof(act[i-1].value) / sizeof(act[i-1].value[0]);
        size_t y = sizeof(act[i-1].value) / sizeof(float) / x;
        Gradients[i].paraW.value = (dot(dZ, Transpose(act[i-1].value, x, y)));


        size_t lengthOfWValue = sizeof(Gradients[i].paraW.value) / sizeof(Gradients[i].paraW.value[0]);
        size_t WeidthOfWValue = (sizeof(Gradients[i].paraW.value) / sizeof(float)) / lengthOfWValue;
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
        size_t WeidthOfBValue = (sizeof(Gradients[i].paraB.value) / sizeof(char)) / sizeof(lengthOfBValue);
        for(size_t j = 0; j < lengthOfBValue; j++)
        {
            for(size_t k = 0; k < WeidthOfBValue; k++)
            {
                Gradients[i].paraB.value[j][k] *= 1/m;
            }
        }


        if (i > 1)
        {
            size_t x2 = sizeof(Wb[i]->paraW.value) / sizeof(Wb[i]->paraW.value[0]);
            size_t y2 = sizeof(Wb[i]->paraW.value) / sizeof(float) / x2;
            dZ = dot(dot(Transpose(Wb[i]->paraW.value, x2, y2), dZ), act[i-1].value);
            float** this = act[i-1].value;
            size_t lengthOfthis = sizeof(this) / sizeof(this[0]);
            size_t WeidthOfthis = (sizeof(this) / sizeof(float)) / lengthOfthis;
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


    return (Dico**)Gradients;


}




Dico** Update(Dico** gradiants, Dico* Wb, float learning_rate)
{
    size_t C = sizeof(Wb) / 2;


    for(size_t i = 1; i < C+1; i++)
    {
        size_t lengthOfGra = sizeof(gradiants[i]->paraW.value) / sizeof(gradiants[i]->paraW.value[0]);
        size_t WeidthOfGra =  (sizeof(gradiants[i]->paraW.value) / sizeof(float)) / lengthOfGra;
        for (size_t j = 0; j < lengthOfGra; j++)
        {
            for(size_t k = 0; k < WeidthOfGra; k++)
            {
                gradiants[i]->paraW.value[j][k] *= learning_rate;
            }
        }
        Wb[i].paraW.value = (float**) (Wb[i].paraW.value - gradiants[i]->paraW.value);
       
        lengthOfGra = sizeof(gradiants[i]->paraB.value) / sizeof(gradiants[i]->paraB.value[0]);
        WeidthOfGra =  (sizeof(gradiants[i]->paraB.value) / sizeof(float)) / lengthOfGra;
        for (size_t j = 0; j < lengthOfGra; j++)
        {
            for(size_t k = 0; k < WeidthOfGra; k++)
            {
                gradiants[i]->paraB.value[j][k] *= learning_rate;
            }
        }


        Wb[i].paraB.value = (float**)(Wb[i].paraB.value - gradiants[i]->paraB.value);
    }


    return (Dico**) Wb;
}


int Predict(float* X, Dico* parametre)
{
    WorB* activation = ForwardPropagation(X, (Dico**)parametre);
    size_t C = sizeof(parametre) / sizeof(parametre[0]) / 2;
    float Af = **(activation[C].value);
   
    if(Af >= 0.5)
    {
        return 1;
    }
    return 0;
}



