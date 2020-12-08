//
// Created by Noa Moalem on 8.6.2020.
//
#include <cmath>
#include "math.h"
#include "Activation.h"

/**
 * The constructor, initialize new ActivationType object.
 * @param actType given type.
 */
Activation::Activation(ActivationType actType) : type(actType)
{
}

/**
 * getter.
 * @return the activation type.
 */
ActivationType Activation::getActivationType() const
{
    return type;
}

/**
 * Applies activation function on input.
 * @param m The matrix to preform the activation on.
 * @return The matrix after the activation.
 */
Matrix Activation::operator()(const Matrix &m) const
{
    if (type == Relu)
    {
        return _reluFunc(m);
    }
    else
    {
        return _softMaxFunc(m);
    }
}

/**
 * The relu activation function.
 * @return the matrix after the activation.
 */
Matrix Activation::_reluFunc(const Matrix &m) const
{
    Matrix toRet = Matrix(m);
    for (int i = 0; i < m.getRows() * m.getCols(); i++)
    {
        if (toRet[i] < ZERO)
        {
            toRet[i] = ZERO;
        }
    }
    return toRet;
}

/**
 * The softmax activation function.
 * @return  the matrix after the activation.
 */
Matrix Activation::_softMaxFunc(const Matrix &m) const
{
    float sum = ZERO;
    Matrix toRet = Matrix(m);
    for (int i = 0; i < m.getRows() * m.getCols(); i++)
    {
        toRet[i] = std::exp(toRet[i]);
        sum += toRet[i];
    }
    float c = (1 / sum);
    return operator*(c, toRet);
}

