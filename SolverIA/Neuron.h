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
    float b;
}CoupleOfWAndb;

float** Transposed(float* X[])
{

}

float** BroadCast(float y)
{
    
}

float dot(float* X[], float* B[])
{
    float result = 0;
    size_t length = sizeof(X[0]);
    size_t m = sizeof(X) / sizeof(X[0]);
    size_t n =sizeof(B[0]);
    for (size_t i = 0; i < m; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            for(size_t k = 0; k < length; k++)
            {
                result += X[i][k] + B[k][j];
            }
        }
    }
    return result;

}

CoupleOfWAndb Initialisation(float* X[])
{
    float** W; // W = np.random.randn(X.shape[1],1)
    float b = 0; // np.random.randn(1)
    CoupleOfWAndb result;
    result.W = W;
    result.b = b;
}

float model(float* X[], float* W[], float b)
{
    float Z = dot(X,W) + b;
    return 1 / (1 + expf(-Z));
}

float LogLoss(float A,float y) 
{
    return - 1 / (sizeof(y)) * (y * logf(A) - (1 - y) * logf(1-A)); 
}

CoupleOfFloat Gradients(float A,float* X[],float y) 
{
    float dW = 1 / (sizeof(y)) * (dot(Transposed(X), BroadCast(A - y))); 
    float db = 1 / (sizeof(y)) * (A - y); 
    CoupleOfFloat result;
    result.first = dW;
    result.second  = db;
    return result;
}

CoupleOfWAndb Update(CoupleOfFloat d, float* W[], float b, float learning_rate)
{
    W = 0; // W - learning_rate * d.first
    b = b - learning_rate * d.second;
    CoupleOfWAndb result;
    result.W = W;
    result.b = b;
    return result;
}