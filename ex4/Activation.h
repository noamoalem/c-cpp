//Activation.h
#ifndef ACTIVATION_H
#define ACTIVATION_H
#define ZERO 0

#include "Matrix.h"

/**
 * @enum ActivationType
 * @brief Indicator of activation function.
 */
enum ActivationType
{
    Relu,
    Softmax
};

/**
 * The Activation class.
 */
class Activation
{
private:
    ActivationType type;

    /**
     * The relu activation function.
     * @return the matrix after the activation.
     */
    Matrix _reluFunc(const Matrix &) const;

    /**
     * The softmax activation function.
     * @return  the matrix after the activation.
     */
    Matrix _softMaxFunc(const Matrix &) const;

public:
    /**
     * The constructor, initialize new ActivationType object.
     * @param actType given type.
     */
    Activation(ActivationType actType);

    /**
     * getter.
     * @return the activation type.
     */
    ActivationType getActivationType() const;

    /**
     * Applies activation function on input.
     * @param m The matrix to preform the activation on.
     * @return The matrix after the activation.
     */
    Matrix operator()(const Matrix &m) const;
};

#endif //ACTIVATION_H