//
// Created by Noa Moalem on 9.6.2020.
//

#include "MlpNetwork.h"
#include "Dense.h"

/**
 * The constructor, initialize new network.
 * @param weights given array of weights matrix.
 * @param biases given array of biases matrix.
 */
MlpNetwork::MlpNetwork(Matrix *weights, Matrix *biases) : weights(weights), biases(biases),
all_layers
{
    Dense(weights[0], biases[0], Relu), Dense(weights[1], biases[1], Relu),
           Dense(weights[2], biases[2], Relu), Dense(weights[3], biases[3], Softmax)
}
{
}

/**
 * Applies the entire network on input.
 * @return digit struct.
 */
Digit MlpNetwork::operator()(Matrix &input) const
{

    Matrix currMatrix = Matrix(input);
    for (Dense currLayer : all_layers)
    {
        currMatrix = currLayer(currMatrix);
    }
    float currBest[2] = {FIRST, FIRST}; // [index,value]
    for (int i = 0; i < currMatrix.getRows(); i++)
    {
        if (currMatrix[i] > currBest[1])
        {
            currBest[0] = i;
            currBest[1] = currMatrix[i];
        }
    }
    Digit toRet = {(unsigned int) currBest[0], currBest[1]};
    return toRet;
}

