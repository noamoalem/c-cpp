//MlpNetwork.h


#ifndef MLPNETWORK_H
#define MLPNETWORK_H

#include "Dense.h"
#include "Digit.h"

#define MLP_SIZE 4
#define FIRST 0

const MatrixDims imgDims = {28, 28};
const MatrixDims weightsDims[] = {{128, 784},
                                  {64,  128},
                                  {20,  64},
                                  {10,  20}};
const MatrixDims biasDims[] = {{128, 1},
                               {64,  1},
                               {20,  1},
                               {10,  1}};

// Insert MlpNetwork class here...
/**
 * The MlpNetwork class.
 */
class MlpNetwork
{
private:
    Matrix *weights;
    Matrix *biases;
    Dense all_layers[MLP_SIZE];
public:
    /**
     * The constructor, initialize new network.
     * @param weights given array of weights matrix.
     * @param biases given array of biases matrix.
     */
    MlpNetwork(Matrix weights[], Matrix biases[]);

    /**
     * Applies the entire network on input.
     * @return digit struct.
     */
    Digit operator()(Matrix &) const;
};

#endif // MLPNETWORK_H
