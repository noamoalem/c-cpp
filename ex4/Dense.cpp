//
// Created by Noa Moalem on 9.6.2020.
//

#include "Dense.h"

/**
 * The constructor, initialize a new layer with given parameters.
 */
Dense::Dense(Matrix &w, Matrix &bias, ActivationType acType) : w(w), bias(bias), type(acType)
{

}

/**
 * getter.
 * @return the weights matrix of this layer.
 */
Matrix Dense::getWeights() const
{
    return w;
}

/**
 * getter.
 * @return the bias matrix of this layer.
 */
Matrix Dense::getBias() const
{
    return bias;
}

/**
 * getter.
 * @return the activation type of this layer.
 */
Activation Dense::getActivation() const
{
    Activation toRet = Activation(type);
    return toRet;
}

/**
 * Applies the layer on input and returns output matrix. preform (w*input) + b.
 * @param input given matrix.
 * @return the matrix after preforming (w*input) + b.
 */
Matrix Dense::operator()(const Matrix &input) const
{
    Matrix temp = (w * input);
    temp += bias;
    Activation activation(type);
    temp = activation(temp);
    Matrix toRet = Matrix(temp);
    return toRet;
}
