//
// Created by Noa Moalem on 9.6.2020.
//

#ifndef EX1_DENSE_H
#define EX1_DENSE_H

#include "Activation.h"

/**
 * The dense class.
 */
class Dense
{
private:
    Matrix w;
    Matrix bias;
    ActivationType type;
public:
    /**
     * The constructor, initialize a new layer with given parameters.
     */
    Dense(Matrix &, Matrix &, ActivationType);

    /**
     * getter.
     * @return the weights matrix of this layer.
     */
    Matrix getWeights() const;

    /**
     * getter.
     * @return the bias matrix of this layer.
     */
    Matrix getBias() const;

    /**
     * getter.
     * @return the activation type of this layer.
     */
    Activation getActivation() const;

    /**
     * Applies the layer on input and returns output matrix. preform (w*input) + b.
     * @param input given matrix.
     * @return the matrix after preforming (w*input) + b.
     */
    Matrix operator()(const Matrix &input) const;
};


#endif //EX1_DENSE_H
