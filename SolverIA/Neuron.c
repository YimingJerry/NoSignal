#include <stdio.h>
#include <stdlib.h>
#include "Neuron.h"
// need fonction add pour grid ou liste de mots.
int neurone_artificiel(float* X,float** y, size_t nbCouche, float n,float learning_rate, size_t n_iter) // le retourn A 
{
    float* hiddenLayer;
    for(size_t i = 1; i < nbCouche+1; i++)
    {
        hiddenLayer[i] = n;
    }

    hiddenLayer[0] = sizeof(X);
    hiddenLayer[nbCouche+1] = sizeof(y) / sizeof(y[0]);
    Dico** parametre = Initialisation(hiddenLayer);

    for(size_t i = 0; i < n_iter; i++)
    {
        WorB* activation = ForwardPropagation(X, parametre);
        Dico* Gradients = BackPropagation(y,activation,parametre);
        parametre = Update(Gradients, parametre, learning_rate);
    }

    return Predict(X, parametre);
}
