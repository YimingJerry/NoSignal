#include <stdio.h>
#include <stdlib.h>
#include "Neuron.h"
// need fonction add pour grid ou liste de mots.
float neurone_artificiel(float* X[],float y,float learning_rate,size_t n_iter) // le retourn A 
{
    CoupleOfWAndb Wb = Initialisation(X);

    float* Loss;

    for(size_t i = 0; i < n_iter; i++)
    {
        float A = model(X, Wb.W, Wb.b);
        Loss[i] = LogLoss(A,y);
        CoupleOfFloat gra = Gradients(A, X, y);
        Wb = Update(gra, Wb.W, Wb.b, learning_rate);
    }
}

